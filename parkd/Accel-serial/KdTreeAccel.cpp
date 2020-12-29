/*
   Copyright (c) 2010 University of Illinois
   All rights reserved.

   Developed by:           DeNovo group, Graphis@Illinois
                           University of Illinois
                           http://denovo.cs.illinois.edu
                           http://graphics.cs.illinois.edu

   Permission is hereby granted, free of charge, to any person obtaining a
   copy of this software and associated documentation files (the
   "Software"), to deal with the Software without restriction, including
   without limitation the rights to use, copy, modify, merge, publish,
   distribute, sublicense, and/or sell copies of the Software, and to
   permit persons to whom the Software is furnished to do so, subject to
   the following conditions:

    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimers.

    * Redistributions in binary form must reproduce the above
      copyright notice, this list of conditions and the following disclaimers
      in the documentation and/or other materials provided with the
      distribution.

    * Neither the names of DeNovo group, Graphics@Illinois, 
      University of Illinois, nor the names of its contributors may be used to 
      endorse or promote products derived from this Software without specific 
      prior written permission.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
   OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
   MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
   IN NO EVENT SHALL THE CONTRIBUTORS OR COPYRIGHT HOLDERS BE LIABLE FOR
   ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
   TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
   SOFTWARE OR THE USE OR OTHER DEALINGS WITH THE SOFTWARE.
*/

#include <sstream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <limits>
#include <cmath>
#include <set>

#include "KdTreeAccel.h"
#include "timers.h"
#include "TriangleMesh.h"
#include "BoundingBox.h"

using namespace std;

int grain_size = -1;
bool verbose_level0 = false;

#define level(code) if (verbose_level0 && level==0) { code ; }

string stats[6];

KdTreeAccel::KdTreeAccel(TriangleMesh * mesh, unsigned int numThreads,
                         unsigned int maxDepth) 
  : KdTreeAccel_base(mesh, numThreads, maxDepth) {
  // this is a serial version (numThread > 1 is an error)
  if (numThreads > 1) {
    cerr << "Accel-serial is a serial version; n=1 only is allowed." << endl;
    cerr << " Will run with 1 thread." << endl;
  }
}

string KdTreeAccel::impl_string() {
  return string("Serial version");
}

void KdTreeAccel::build() {
  // root node
  m_root = new KdTreeNode();
  // bounding box for the root node
  BoundingBox &nodeExtent = *new BoundingBox(m_mesh->screenBoundingBox);

  // list of boxedges
  vv_BoxEdge boxEdgeList(3);

  // construct list of triangle indices (0...n-1),
  // where n is number of triangles
  //vector<int, tbb::scalable_allocator<int> > triangleIndices;
  //for (int i = 0; i < (int)(m_mesh->triangleList.size()); i++) {
  //    triangleIndices.push_back(i);
  //}
  vector<int, tbb::scalable_allocator<int> > drawIndices;
  for (int i = 0; i < (int)(m_mesh->screenBoundingBoxesPerBatch.size()); i++) {
      drawIndices.push_back(i);
  }

  //unsigned int n = triangleIndices.size();
  //for (unsigned int i=0;i<3;i++) {
  //    boxEdgeList[i].resize(2*n);
  //}
  unsigned int n = drawIndices.size();
  for (unsigned int i=0;i<3;i++) {
      boxEdgeList[i].resize(2*n);
  }

  // init boxedge lists
  for (unsigned int i = 0; i < 3; i++) {
    for (unsigned int j = 0; j < n; j++) {
      //boxEdgeList[i][j*2] = BoxEdge(m_mesh->triangleList[triangleIndices[j]].screenBound.min[i], triangleIndices[j], START, i);
      //boxEdgeList[i][j*2+1] = BoxEdge(m_mesh->triangleList[triangleIndices[j]].screenBound.max[i], triangleIndices[j], END, i);
      boxEdgeList[i][j*2] = BoxEdge(m_mesh->screenBoundingBoxesPerBatch[drawIndices[j]].min[i], drawIndices[j], START, i);
      boxEdgeList[i][j*2+1] = BoxEdge(m_mesh->screenBoundingBoxesPerBatch[drawIndices[j]].max[i], drawIndices[j], END, i);
    }
  }

  nodeExtent.min[2] = 0;
  nodeExtent.max[2] = n;
  for (unsigned int j = 0; j < 2*n; j++) {
    if (boxEdgeList[2][j].edgeType == START)
      boxEdgeList[2][j].t = boxEdgeList[2][j].triangleIndex;
    else
      boxEdgeList[2][j].t = boxEdgeList[2][j].triangleIndex + 1;
  }

  // sort the boxedges
  sort(boxEdgeList[0].begin(), boxEdgeList[0].end());
  sort(boxEdgeList[1].begin(), boxEdgeList[1].end());
  sort(boxEdgeList[2].begin(), boxEdgeList[2].end());

  // serial tree construction using box-edges
  m_root = buildTree_boxEdges(nodeExtent, boxEdgeList, m_maxDepth);
}

KdTreeNode *KdTreeAccel::buildTree_boxEdges(const BoundingBox& nodeExtent,
                                            vv_BoxEdge& boxEdgeList,
                                            int maxDepth) {
  KdTreeNode * newNode = new KdTreeNode();
  unsigned int triangles = boxEdgeList[0].size()/2;
    
  if (maxDepth == 0 || triangles == 0) {
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->extent = nodeExtent;
    newNode->triangleIndices = new vector<int>();

    for (v_BoxEdge::const_iterator I=boxEdgeList[0].begin(),
        E=boxEdgeList[0].end(); I!=E; I++) {
      if ((*I).edgeType == START) {
        newNode->triangleIndices->push_back((*I).triangleIndex);
      }
    }
    return newNode;
  } else {
    BoxEdge *bestEdge = NULL;
    BoxEdge edge;
    BoundingBox screenBound;
    int numTriangles, unclippedTris, fragments;

    float left_min = 0, right_max = 0, bottom_min = 0, top_max = 0;
    int hRes, vRes;
    
    vector<vector<float> > fragments_left(3), fragments_right(3);
    vector<vector<int> > tris_left(3), tris_right(3);

    bool anyBatchBlend = m_mesh->anyBatchBlend;
    unsigned int end_dim = (anyBatchBlend ? 3 : 2);

    /*for (unsigned int i = 0; i < end_dim; i++) {
      fragments_left[i].resize(boxEdgeList[i].size(), 0);
      tris_left[i].resize(boxEdgeList[i].size(), 0);
      for (int j = 0; j < boxEdgeList[i].size(); j++) {
        edge = boxEdgeList[i][j];
        unclippedTris = m_mesh->unclippedTrisPerBatch[edge.triangleIndex];

	if (edge.edgeType == START && unclippedTris > 0) {
	  //screenBound = m_mesh->screenBoundingBoxesPerBatch[edge.triangleIndex];
          //left_min = screenBound.min[0] < -1 ? -1 : (screenBound.min[0] > 1 ? 1 : screenBound.min[0]);
          //right_max = screenBound.max[0] > 1 ? 1 : (screenBound.max[0] < -1 ? -1 : screenBound.max[0]);
          //bottom_min = screenBound.min[1] < -1 ? -1 : (screenBound.min[1] > 1 ? 1 : screenBound.min[1]);
          //top_max = screenBound.max[1] > 1 ? 1 : (screenBound.max[1] < -1 ? -1 : screenBound.max[1]);
	  //hRes = m_mesh->hResPerBatch[edge.triangleIndex];
	  //vRes = m_mesh->vResPerBatch[edge.triangleIndex];
	  fragments = m_mesh->fragmentsPerBatch[edge.triangleIndex];
          numTriangles = m_mesh->triangleListPerBatch[edge.triangleIndex].size();
          
          if (j > 0) {
            //fragments_left[i][j] = fragments_left[i][j - 1] + (right_max - left_min)*(top_max - bottom_min)*hRes*vRes/4;
            fragments_left[i][j] = fragments_left[i][j - 1] + fragments;
	    tris_left[i][j] = tris_left[i][j - 1] + numTriangles;
	  } else {
            fragments_left[i][j] = fragments;
	    tris_left[i][j] = numTriangles;
	  }
        } else if (j > 0) {
            fragments_left[i][j] = fragments_left[i][j-1];
            tris_left[i][j] = tris_left[i][j-1];
        }
      }

      fragments_right[i].resize(boxEdgeList[i].size(), 0);
      tris_right[i].resize(boxEdgeList[i].size(), 0);
      for (int j = (boxEdgeList[i].size() - 1); j >= 0; j--) {
        edge = boxEdgeList[i][j];
        unclippedTris = m_mesh->unclippedTrisPerBatch[edge.triangleIndex];
        
	if (edge.edgeType == END && unclippedTris > 0) {
          //screenBound = m_mesh->unclippedScreenBoundingBoxesPerBatch[edge.triangleIndex];
          //left_min = screenBound.min[0] < -1 ? -1 : (screenBound.min[0] > 1 ? 1 : screenBound.min[0]);
          //right_max = screenBound.max[0] > 1 ? 1 : (screenBound.max[0] < -1 ? -1 : screenBound.max[0]);
          //bottom_min = screenBound.min[1] < -1 ? -1 : (screenBound.min[1] > 1 ? 1 : screenBound.min[1]);
          //top_max = screenBound.max[1] > 1 ? 1 : (screenBound.max[1] < -1 ? -1 : screenBound.max[1]);
	  //hRes = m_mesh->hResPerBatch[edge.triangleIndex];
	  //vRes = m_mesh->vResPerBatch[edge.triangleIndex];
	  fragments = m_mesh->fragmentsPerBatch[edge.triangleIndex];
          numTriangles = m_mesh->triangleListPerBatch[edge.triangleIndex].size();
            
          if (j < (boxEdgeList[i].size() - 1)) {
            //fragments_right[i][j] = fragments_right[i][j + 1] + (right_max - left_min)*(top_max - bottom_min)*hRes*vRes/4;
            fragments_right[i][j] = fragments_right[i][j + 1] + fragments;
	    tris_right[i][j] = tris_right[i][j + 1] + numTriangles;
          } else {
            //fragments_right[i][j] = (right_max - left_min)*(top_max - bottom_min)*hRes*vRes/4;
            fragments_right[i][j] = fragments;
	    tris_right[i][j] = numTriangles;
	  }
	} else if (j < boxEdgeList[i].size() - 1) {
          fragments_right[i][j] = fragments_right[i][j+1];
          tris_right[i][j] = tris_right[i][j+1];
        }
      }
    }

    float workload_left = 0, workload_right = 0;
    float workload_diff = numeric_limits<float>::max();
    float best_workload = numeric_limits<float>::max();
    float best_fragments_left = 0, best_fragments_right = 0, best_tri_left = 0, best_tri_right = 0;
    
    for (unsigned int i = 0; i < end_dim; i++) {
      for (unsigned int j = 0; j < boxEdgeList[i].size(); j++) {
        edge = boxEdgeList[i][j];
        unclippedTris = m_mesh->unclippedTrisPerBatch[edge.triangleIndex];

	if (unclippedTris == 0) continue;
        
	workload_left = fragments_left[i][j] + tris_left[i][j];
        workload_right = fragments_right[i][j] + tris_right[i][j];
	
	if (workload_left < best_workload && workload_right < best_workload) {
	//if (abs(fragments_left[i][j/2] - fragments_right[i][j/2]) + abs(tris_left[i][j/2] - tris_right[i][j/2]) < workload_diff
	//    && workload_left < best_workload && workload_right < best_workload) {
          bestEdge = &(boxEdgeList[i][j]);
          workload_diff = abs(fragments_left[i][j] - fragments_right[i][j]) + abs(tris_left[i][j] - tris_right[i][j]);
	  //workload_diff = abs(workload_left - workload_right);
	  best_workload = workload_left > workload_right ? workload_left : workload_right;
	  best_fragments_left = fragments_left[i][j];
	  best_fragments_right = fragments_right[i][j];
	  best_tri_left = tris_left[i][j];
	  best_tri_right = tris_right[i][j];
	}
      }
    }*/

    for (unsigned int i = 2; i < 3; i++) {
      fragments_left[i].resize(triangles + 1, 0);
      tris_left[i].resize(triangles + 1, 0);
      for (int j = 0; j < triangles; j++) {
        edge = boxEdgeList[i][2*j + 1];
	assert(edge.edgeType == END);
        unclippedTris = m_mesh->unclippedTrisPerBatch[edge.triangleIndex];

	if (unclippedTris > 0) {
	  //screenBound = m_mesh->screenBoundingBoxesPerBatch[edge.triangleIndex];
          //left_min = screenBound.min[0] < -1 ? -1 : (screenBound.min[0] > 1 ? 1 : screenBound.min[0]);
          //right_max = screenBound.max[0] > 1 ? 1 : (screenBound.max[0] < -1 ? -1 : screenBound.max[0]);
          //bottom_min = screenBound.min[1] < -1 ? -1 : (screenBound.min[1] > 1 ? 1 : screenBound.min[1]);
          //top_max = screenBound.max[1] > 1 ? 1 : (screenBound.max[1] < -1 ? -1 : screenBound.max[1]);
	  //hRes = m_mesh->hResPerBatch[edge.triangleIndex];
	  //vRes = m_mesh->vResPerBatch[edge.triangleIndex];
	  fragments = m_mesh->fragmentsPerBatch[edge.triangleIndex];
          numTriangles = m_mesh->triangleListPerBatch[edge.triangleIndex].size();
          
          if (j > 0) {
            //fragments_left[i][j] = fragments_left[i][j - 1] + (right_max - left_min)*(top_max - bottom_min)*hRes*vRes/4;
            fragments_left[i][j + 1] = fragments_left[i][j] + fragments;
	    tris_left[i][j + 1] = tris_left[i][j] + numTriangles;
	  } else {
            fragments_left[i][j + 1] = fragments;
	    tris_left[i][j + 1] = numTriangles;
	  }
        } else if (j > 0) {
            fragments_left[i][j + 1] = fragments_left[i][j];
            tris_left[i][j + 1] = tris_left[i][j];
        }
      }

      fragments_right[i].resize(triangles + 1, 0);
      tris_right[i].resize(triangles + 1, 0);
      for (int j = (triangles - 1); j >= 0; j--) {
        edge = boxEdgeList[i][2*j];
	assert(edge.edgeType == START);
        unclippedTris = m_mesh->unclippedTrisPerBatch[edge.triangleIndex];
       
	if (unclippedTris > 0) {
          //screenBound = m_mesh->unclippedScreenBoundingBoxesPerBatch[edge.triangleIndex];
          //left_min = screenBound.min[0] < -1 ? -1 : (screenBound.min[0] > 1 ? 1 : screenBound.min[0]);
          //right_max = screenBound.max[0] > 1 ? 1 : (screenBound.max[0] < -1 ? -1 : screenBound.max[0]);
          //bottom_min = screenBound.min[1] < -1 ? -1 : (screenBound.min[1] > 1 ? 1 : screenBound.min[1]);
          //top_max = screenBound.max[1] > 1 ? 1 : (screenBound.max[1] < -1 ? -1 : screenBound.max[1]);
	  //hRes = m_mesh->hResPerBatch[edge.triangleIndex];
	  //vRes = m_mesh->vResPerBatch[edge.triangleIndex];
	  fragments = m_mesh->fragmentsPerBatch[edge.triangleIndex];
          numTriangles = m_mesh->triangleListPerBatch[edge.triangleIndex].size();
            
          if (j < triangles - 1) {
            //fragments_right[i][j] = fragments_right[i][j + 1] + (right_max - left_min)*(top_max - bottom_min)*hRes*vRes/4;
            fragments_right[i][j] = fragments_right[i][j + 1] + fragments;
	    tris_right[i][j] = tris_right[i][j + 1] + numTriangles;
          } else {
            //fragments_right[i][j] = (right_max - left_min)*(top_max - bottom_min)*hRes*vRes/4;
            fragments_right[i][j] = fragments;
	    tris_right[i][j] = numTriangles;
	  }
	} else if (j < triangles - 1) {
          fragments_right[i][j] = fragments_right[i][j + 1];
          tris_right[i][j] = tris_right[i][j + 1];
        }
      }
    }
    
    float workload_left = 0, workload_right = 0;
    float workload_diff = numeric_limits<float>::max();
    float best_workload = numeric_limits<float>::max();
    float best_fragments_left = 0, best_fragments_right = 0, best_tri_left = 0, best_tri_right = 0;
    for (unsigned int i = 2; i < 3; i++) {
      for (unsigned int j = 0; j < triangles + 1; j++) {
	workload_left = fragments_left[i][j] + tris_left[i][j];
        workload_right = fragments_right[i][j] + tris_right[i][j];
	
	//cout << "i " << i << " j " << j << " " << fragments_left[i][j] << " " << fragments_right[i][j]
        //     << " " << tris_left[i][j] << " " << tris_right[i][j]
	//     << " " << best_workload
	//     << endl;
	
	//if (workload_left < best_workload && workload_right < best_workload) {
	if (abs(fragments_left[i][j] - fragments_right[i][j]) + abs(tris_left[i][j] - tris_right[i][j]) < workload_diff
	    && workload_left < best_workload && workload_right < best_workload) {
	  if (j == triangles)
            bestEdge = &(boxEdgeList[i][2*j - 1]);
	  else
            bestEdge = &(boxEdgeList[i][2*j]);
          workload_diff = abs(fragments_left[i][j] - fragments_right[i][j]) + abs(tris_left[i][j] - tris_right[i][j]);
	  //workload_diff = abs(workload_left - workload_right);
	  best_workload = workload_left > workload_right ? workload_left : workload_right;
	  best_fragments_left = fragments_left[i][j];
	  best_fragments_right = fragments_right[i][j];
	  best_tri_left = tris_left[i][j];
	  best_tri_right = tris_right[i][j];
	}
      }
    }

    if (!anyBatchBlend) {
      v_BoxEdge z_edges_left, z_edges_right;
      set<unsigned int> left_batches, right_batches;
      workload_left = 0;
      workload_right = 0;
      int tot_fragments_left = 0, tot_fragments_right = 0;
      int tot_triangles_left = 0, tot_triangles_right = 0;
      int fragments_diff_left, fragments_diff_right, triangles_diff_left, triangles_diff_right;
      
      for (int j = 0; j < boxEdgeList[2].size(); j++) {
        edge = boxEdgeList[2][j];
        unclippedTris = m_mesh->unclippedTrisPerBatch[edge.triangleIndex];
        
	if (edge.edgeType == START && unclippedTris > 0) {
	  //screenBound = m_mesh->screenBoundingBoxesPerBatch[edge.triangleIndex];
          //left_min = screenBound.min[0] < -1 ? -1 : (screenBound.min[0] > 1 ? 1 : screenBound.min[0]);
          //right_max = screenBound.max[0] > 1 ? 1 : (screenBound.max[0] < -1 ? -1 : screenBound.max[0]);
          //bottom_min = screenBound.min[1] < -1 ? -1 : (screenBound.min[1] > 1 ? 1 : screenBound.min[1]);
          //top_max = screenBound.max[1] > 1 ? 1 : (screenBound.max[1] < -1 ? -1 : screenBound.max[1]);
	  //hRes = m_mesh->hResPerBatch[edge.triangleIndex];
	  //vRes = m_mesh->vResPerBatch[edge.triangleIndex];
          fragments = m_mesh->fragmentsPerBatch[edge.triangleIndex];
          numTriangles = m_mesh->triangleListPerBatch[edge.triangleIndex].size();
          
	  fragments_diff_left = abs((tot_fragments_left + fragments) - tot_fragments_right);
	  triangles_diff_left = abs((tot_triangles_left + numTriangles) - tot_triangles_right);
	  fragments_diff_right = abs((tot_fragments_right + fragments) - tot_fragments_left);
	  triangles_diff_right = abs((tot_triangles_right + numTriangles) - tot_triangles_left);
	  if ((fragments_diff_left + triangles_diff_left) <= (fragments_diff_right + triangles_diff_right)
	      && (workload_left <= workload_right)) {
            //workload_left += ((right_max - left_min)*(top_max - bottom_min)*hRes*vRes/4 + numTriangles);
            //tot_fragments_left += (right_max - left_min)*(top_max - bottom_min)*hRes*vRes/4;
            workload_left += (fragments + numTriangles);
            tot_fragments_left += fragments;
            tot_triangles_left += numTriangles;
            z_edges_left.push_back(edge);
            left_batches.insert(edge.triangleIndex);
          } else {
            //workload_right += ((right_max - left_min)*(top_max - bottom_min)*hRes*vRes/4 + numTriangles);
            //tot_fragments_right += (right_max - left_min)*(top_max - bottom_min)*hRes*vRes/4;
            workload_right += (fragments + numTriangles);
            tot_fragments_right += fragments;
            tot_triangles_right += numTriangles;
            z_edges_right.push_back(edge);
            right_batches.insert(edge.triangleIndex);
          }
        } else {
          if (left_batches.count(edge.triangleIndex)) {
            z_edges_left.push_back(edge);
          } else {
            z_edges_right.push_back(edge);
          }
        }
      }

      sort(z_edges_left.begin(), z_edges_left.end());
      sort(z_edges_right.begin(), z_edges_right.end());

      //if (workload_left < best_workload && workload_right < best_workload) {
        int j = 0;
        v_BoxEdge::const_iterator edge_iter = z_edges_left.begin();
        for (; edge_iter != z_edges_left.end(); edge_iter++, j++) {
          boxEdgeList[2][j] = *edge_iter;
        }
        edge_iter = z_edges_right.begin();
        for (; edge_iter != z_edges_right.end(); edge_iter++, j++) {
          boxEdgeList[2][j] = *edge_iter;
        }

	if (z_edges_left.size() == 0 || z_edges_right.size() == 0)
          bestEdge = NULL;
        else
          bestEdge = &(boxEdgeList[2][z_edges_left.size() - 1]);

        workload_diff = abs(tot_fragments_left - tot_fragments_right) + abs(tot_triangles_left - tot_triangles_right);
        best_workload = workload_left > workload_right ? workload_left : workload_right;
        best_fragments_left = tot_fragments_left;
        best_fragments_right = tot_fragments_right;
        best_tri_left = tot_triangles_left;
        best_tri_right = tot_triangles_right;
      //}
    }

    //cout << "maxDepth " << maxDepth << " triangles " << triangles
    //     << " best_fragments_left " << best_fragments_left << " best_fragments_right " << best_fragments_right
    //     << " best_tri_left " << best_tri_left << " best_tri_right " << best_tri_right << " best_workload " << best_workload
    //     << endl;

    // not worth splitting
    if (!bestEdge) {
      newNode->right = NULL;
      newNode->left = NULL;
      newNode->extent = nodeExtent;
      newNode->triangleIndices = new vector<int>();

      for (v_BoxEdge::const_iterator I=boxEdgeList[0].begin(),
          E=boxEdgeList[0].end(); I!=E; I++) {
        if ((*I).edgeType == START) {
          newNode->triangleIndices->push_back((*I).triangleIndex);
        }
      }
      return newNode;
    }

    //vector<char> membership(m_mesh->triangleList.size(), 0);
    vector<char> membership(m_mesh->triangleListPerBatch.size(), 0);
    vv_BoxEdge left(3), right(3);
    unsigned int left_s = 0, right_s = 0;
    v_BoxEdge::const_iterator I = boxEdgeList[bestEdge->axis].begin(),
    E = boxEdgeList[bestEdge->axis].end();
    for (; (&(*I)) != bestEdge; I++) {
      BoxEdge edge = *I;
      unclippedTris = m_mesh->unclippedTrisPerBatch[edge.triangleIndex];
      if (edge.edgeType == START && unclippedTris > 0) {
        membership[edge.triangleIndex] += 1;
        left_s++;
      }
    }
    for (++I; I != E; I++) {
      BoxEdge edge = *I;
      unclippedTris = m_mesh->unclippedTrisPerBatch[edge.triangleIndex];
      if (edge.edgeType == END && unclippedTris > 0) {
        membership[edge.triangleIndex] += 2;
        right_s++;
      }
    }

    for (unsigned int i=0;i<3;i++) {
      for(v_BoxEdge::const_iterator I=boxEdgeList[i].begin(),
          E=boxEdgeList[i].end(); I!=E; I++) {
        BoxEdge edge = *I;
        if (membership[edge.triangleIndex] & 1) {
          left[i].push_back(edge);
        }
        if (membership[edge.triangleIndex] & 2) {
          right[i].push_back(edge);
        }
      }
    }

    BoundingBox leftNodeExtent(nodeExtent), rightNodeExtent(nodeExtent);
    leftNodeExtent.max[bestEdge->axis] = bestEdge->t;
    rightNodeExtent.min[bestEdge->axis] = bestEdge->t;

    // recurse..
    newNode->extent = nodeExtent;
    newNode->splitEdge = bestEdge;

    //    if (ver_splitedge) {
//    if (true) {
//      cerr << 8-maxDepth << " "
//           << setprecision(3) << fixed << " [@ " 
//           << bestEdge->t << " "
//           << (char)(bestEdge->axis + 'X') << " "
//           << (bestEdge->edgeType?"END":"STR") << " "
//           << "tri#:" << bestEdge->triangleIndex << " " 
////            <<  memo[i].nA << ":" << memo[i].nB
//           << " = " << SAH_best << " " << endl;
//    }
    
    newNode->left = buildTree_boxEdges(leftNodeExtent, left, maxDepth-1);
    newNode->right = buildTree_boxEdges(rightNodeExtent, right, maxDepth-1);
    return newNode;
  }
}

void impl_usage() {
  // TODO
}

void KdTreeAccel::printTimingStats(ostream &out) {
  // TODO
}

void KdTreeAccel::printTimingStatsCSVHeader(std::ostream &out) {
  cerr << "\n";
}

void KdTreeAccel::printTimingStatsCSV(std::ostream &out) {
  cerr << "\n";

}
