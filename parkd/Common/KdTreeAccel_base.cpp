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

#include <fstream>
#include <iterator>
#include <algorithm>
#include <set>
#include <functional>

#include "KdTreeAccel_base.h"

using namespace std;

unsigned int KdTreeAccel_base::bigKDTrees = 0;

KdTreeAccel_base::KdTreeAccel_base(TriangleMesh *mesh, 
                                   uint numThreads, uint maxDepth, 
                                   float Ct, float Ci, float emptyBonus) 
  : m_mesh(mesh), m_numThreads(numThreads), m_maxDepth(maxDepth),
    sah(Ct, Ci, emptyBonus) {

  // Sanity checks
  assert(m_mesh);
  assert(m_numThreads > 0);
  assert(m_maxDepth > 0);
}

bool KdTreeAccel_base::writeToFile(const std::string  filename) {
  // fill in item list and node list by traversing the tree
  vector<int> itemList;
  vector<MantaKDTreeNode> nodeList;
  nodeList.push_back(MantaKDTreeNode());
  this->packNodesAndItems(this->m_root, 0, itemList, nodeList);
  
  // write item list and node lists to file
  ofstream out(filename.c_str(), ios::out | ios::binary);
  if (!out) return false;
  
  const unsigned int itemList_size = itemList.size();
  const unsigned int nodeList_size = nodeList.size();
  out.write((char*) &itemList_size, sizeof(itemList_size));
  out.write((char*) &itemList[0], sizeof(itemList[0])*itemList_size);
  out.write((char*) &nodeList_size, sizeof(nodeList_size));
  out.write((char*) &nodeList[0], sizeof(nodeList[0])*nodeList_size);
  out.close();
  return true;
}

void KdTreeAccel_base::packNodesAndItems(KdTreeNode * nodePtr, 
                                         const int nodeIdx, 
                                         vector<int> & itemList, 
                                         vector<MantaKDTreeNode> & nodeList) {
  MantaKDTreeNode & node = nodeList[nodeIdx];
  // 	node.isLeaf = nodePtr == NULL || (nodePtr->left == NULL && nodePtr->right == NULL);
  if (nodePtr == NULL) { // empty leaf node
    node.isLeaf = true;
    node.numPrimitives = 0;
    node.childIdx = itemList.size();
  } else if (nodePtr->left == NULL && nodePtr->right == NULL) { // leaf
    node.isLeaf = true;
    node.numPrimitives = nodePtr->triangleIndices->size();
    node.childIdx = itemList.size();
    for (int i = 0; i < nodePtr->triangleIndices->size(); i++)
      itemList.push_back((*nodePtr->triangleIndices)[i]);
  } else {
    node.planePos = nodePtr->splitEdge->t;
    node.planeDim = nodePtr->splitEdge->axis;
    node.childIdx = nodeList.size();
    nodeList.push_back(MantaKDTreeNode());	// left child
    nodeList.push_back(MantaKDTreeNode());	// right child
    packNodesAndItems(nodePtr->left, nodeList[nodeIdx].childIdx, itemList, nodeList);
    packNodesAndItems(nodePtr->right, nodeList[nodeIdx].childIdx+1, itemList, nodeList);
  }
}

bool KdTreeAccel_base::writeToAttilaFile(unsigned int meshId, const std::string  filename, unsigned int numGPUs, bool quiet) {
  set<unsigned int> frames_set;
  map<unsigned int, set<unsigned int> > frame2batches_set;

  vector<unsigned int> frames;
  frame2batches_t frame2batches;
  vIndices_t vIndices;
  nodeExtents_t nodeExtents;
  vector<BoundingBox> nodeScreenBounds;

  unsigned int totTrianglesInKDTree = 0;
  vector<Triangle>::const_iterator triIt;
  map<unsigned int, unsigned int> fragmentsPerBatch;
  map<unsigned int, bool> forcedFrameDup;
  map<unsigned int, bool> forcedSplit;
  map<unsigned int, bool> zFighted;
  for (unsigned int b = 0; b != m_mesh->triangleListPerBatch.size(); b++) {
      //if (!m_mesh->zFighted[b])
          totTrianglesInKDTree += m_mesh->triangleListPerBatch[b].size();
      for (triIt = m_mesh->triangleListPerBatch[b].begin(); triIt != m_mesh->triangleListPerBatch[b].end(); triIt++) {
          frames_set.insert(triIt->frameCounter);
          frame2batches_set[triIt->frameCounter].insert(triIt->batchCounter);
          if (vIndices.count(batchId_t(triIt->frameCounter, triIt->batchCounter)) == 0) {
              vIndices[batchId_t(triIt->frameCounter, triIt->batchCounter)] = vector<vector<unsigned int> >();
	      fragmentsPerBatch[triIt->batchCounter] = m_mesh->fragmentsPerBatch[b];
	      forcedFrameDup[triIt->batchCounter] = m_mesh->forcedFrameDup[b];
	      forcedSplit[triIt->batchCounter] = m_mesh->forcedSplit[b];
	      zFighted[triIt->batchCounter] = m_mesh->zFighted[b];
	  }
      }
  }

  set<unsigned int>::iterator frameSetIt;
  set<unsigned int>::iterator batchSetIt;
  for (frameSetIt = frames_set.begin(); frameSetIt != frames_set.end(); frameSetIt++) {
      frames.push_back(*frameSetIt);
      for (batchSetIt = frame2batches_set[*frameSetIt].begin(); batchSetIt != frame2batches_set[*frameSetIt].end(); batchSetIt++) {
          frame2batches[*frameSetIt].push_back(*batchSetIt);
      }
  }
  
  sort(frames.begin(), frames.end());
  vector<unsigned int>::iterator frameIt;
  for (frameIt = frames.begin(); frameIt != frames.end(); frameIt++) {
      sort(frame2batches[*frameIt].begin(), frame2batches[*frameIt].end());
  }

  unsigned int nodeIdx = 0;
  //packVertexIndices(this->m_root, nodeIdx, vIndices, nodeExtents, nodeScreenBounds, quiet);
  evenlySplitVertexIndices(totTrianglesInKDTree, numGPUs, vIndices, nodeExtents, quiet);

  vector<unsigned int>::iterator batchIt;
  vector<vector<unsigned int> >::iterator leafIt;
  vector<BoundingBox>::iterator boundIt;
  unsigned int numFragments;
  //if (totTrianglesInKDTree > 2048) bigKDTrees++;
  bool anyBatchBlend = m_mesh->anyBatchBlend;
  bool anyBatchCWrite = m_mesh->anyBatchCWrite;
  bool anyBatchZTest = m_mesh->anyBatchZTest;
  unsigned int numDraws = m_mesh->triangleListPerBatch.size();
  ofstream out(filename.c_str(), ios::out | ios::binary | ios::app);
  int i = 0;
  for (frameIt = frames.begin(); frameIt != frames.end(); frameIt++) {
    for (batchIt = frame2batches[*frameIt].begin(); batchIt != frame2batches[*frameIt].end(); batchIt++) {
      out.write((char*)&(meshId), sizeof(unsigned int));
      out.write((char*)&(*frameIt), sizeof(unsigned int));
      out.write((char*)&(*batchIt), sizeof(unsigned int));
      out.write((char*)&(anyBatchBlend), sizeof(bool));
      out.write((char*)&(anyBatchCWrite), sizeof(bool));
      out.write((char*)&(anyBatchZTest), sizeof(bool));
      out.write((char*)&(totTrianglesInKDTree), sizeof(unsigned int));
      out.write((char*)&(numDraws), sizeof(unsigned int));
      numFragments = fragmentsPerBatch[*batchIt];
      out.write((char*)&(numFragments), sizeof(unsigned int));
      out.write((char*)&(forcedFrameDup[*batchIt]), sizeof(bool));
      out.write((char*)&(forcedSplit[*batchIt]), sizeof(bool));
      out.write((char*)&(zFighted[*batchIt]), sizeof(bool));
      if (!quiet)
	cout << (*frameIt) << " " << (*batchIt) << " totTris " << totTrianglesInKDTree
	     << " numTris " << (m_mesh->triangleListPerBatch[i].size()) << " [";
      i++;
      for (leafIt = vIndices[batchId_t(*frameIt, *batchIt)].begin(), boundIt = nodeExtents[batchId_t(*frameIt, *batchIt)].begin();
	   leafIt != vIndices[batchId_t(*frameIt, *batchIt)].end(); leafIt++, boundIt++) {
        unsigned int numIndices = leafIt->size();
        if (!quiet)
	  cout << numIndices << " ";
	boundIt->serialize(out);
        out.write((char*)&numIndices, sizeof(unsigned int));
        if (numIndices > 0)
          out.write((char*)&(*leafIt)[0], sizeof((*leafIt)[0])*numIndices); 
      }
      if (vIndices[batchId_t(*frameIt, *batchIt)].size() < numGPUs) {
        for (unsigned int gpuIndex = vIndices[batchId_t(*frameIt, *batchIt)].size(); gpuIndex < numGPUs; gpuIndex++) {
          unsigned int numIndices = 0;
          if (!quiet)
	    cout << numIndices << " ";
	  BoundingBox().serialize(out);
	  out.write((char*)&numIndices, sizeof(unsigned int));
	}
      }
      if (!quiet)
        cout << "]"<< endl;
    }
  }
  out.close();

  return true;
}

void KdTreeAccel_base::evenlySplitVertexIndices(unsigned int totTris, unsigned int numGPUs, vIndices_t &vIndices,
		                                nodeExtents_t &nodeExtents, bool quiet)
{
    if (!quiet)
	cout << "Begin to split a KDTree" << endl;

    vector<unsigned int> trisPerGPU;
    trisPerGPU.resize(numGPUs, totTris/numGPUs);
    if (totTris % numGPUs != 0) {
	for (unsigned int i = 0; i < totTris % numGPUs; i++)
	    trisPerGPU[i]++;
    }

    unsigned int currGPUId = 0;
    for (unsigned int currBatch = 0; currBatch < m_mesh->triangleListPerBatch.size(); currBatch++) {
        for (unsigned int currTri = 0; currTri < m_mesh->triangleListPerBatch[currBatch].size(); currTri++) {
	    Triangle tri = m_mesh->triangleListPerBatch[currBatch][currTri];
	    unsigned frameCounter = tri.frameCounter;
	    unsigned batchCounter = tri.batchCounter;
	    if (vIndices[batchId_t(frameCounter, batchCounter)].size() == 0)
		vIndices[batchId_t(frameCounter, batchCounter)].resize(numGPUs, vector<unsigned int>());
	    if (nodeExtents.count(batchId_t(frameCounter, batchCounter)) == 0)
		nodeExtents[batchId_t(frameCounter, batchCounter)].resize(numGPUs, BoundingBox());

            if (trisPerGPU[currGPUId] == 0)
                currGPUId++;
	    assert(currGPUId < numGPUs);
            for (unsigned int i = 0; i < 3; i++)
                vIndices[batchId_t(frameCounter, batchCounter)][currGPUId].push_back(tri.index[i]);
    
            trisPerGPU[currGPUId]--;
        }
    }
}

void KdTreeAccel_base::packVertexIndices(KdTreeNode *nodePtr, unsigned int &nodeIdx,
		                         vIndices_t &vIndices, nodeExtents_t &nodeExtents,
		                         vector<BoundingBox> &nodeScreenBounds, bool quiet) {
    vector<int>::iterator batchIt;
    vIndices_t::iterator vIdxIt;
    vector<Triangle>::const_iterator triIt;

    if (nodePtr == NULL) { // empty leaf node
	nodeIdx++;
        for (vIdxIt = vIndices.begin(); vIdxIt != vIndices.end(); vIdxIt++) {
            vIndices[vIdxIt->first].push_back(vector<unsigned int>());
	    nodeExtents[vIdxIt->first].push_back(BoundingBox());
        }
	nodeScreenBounds.push_back(BoundingBox());
    } else if (nodePtr->left == NULL && nodePtr->right == NULL) { // leaf
	nodeIdx++;
	
        for (vIdxIt = vIndices.begin(); vIdxIt != vIndices.end(); vIdxIt++) {
            vIndices[vIdxIt->first].push_back(vector<unsigned int>());
	    nodeExtents[vIdxIt->first].push_back(nodePtr->extent);
        }
        nodeScreenBounds.push_back(BoundingBox());	
        
	sort(nodePtr->triangleIndices->begin(), nodePtr->triangleIndices->end());

	unsigned int unclipps = 0;
	unsigned int totTris = 0;
	for (batchIt = nodePtr->triangleIndices->begin(); batchIt != nodePtr->triangleIndices->end(); batchIt++) {
	    totTris += (m_mesh->triangleListPerBatch)[*batchIt].size();
	    for (triIt = (m_mesh->triangleListPerBatch)[*batchIt].begin(); triIt != (m_mesh->triangleListPerBatch)[*batchIt].end(); triIt++) {
                Triangle triangle = (*triIt);
	        if (triangle.clipped == false) {
	            nodeScreenBounds[nodeIdx - 1] += triangle.screenBound;
		    unclipps++;
	        }
	        for (unsigned int i = 0; i < 3; i++)
  	            vIndices[batchId_t(triangle.frameCounter, triangle.batchCounter)][nodeIdx - 1].push_back(triangle.index[i]);
	    }
	}
        
        if (!quiet) {	
	    cout << "Node: " << (nodeIdx - 1) << " Tris " << totTris << " unclipps " << unclipps << endl;
	    nodePtr->extent.print(cout);
	    nodeScreenBounds[nodeIdx - 1].print(cout);
	}
    } else {
        packVertexIndices(nodePtr->left, nodeIdx, vIndices, nodeExtents, nodeScreenBounds, quiet);
        packVertexIndices(nodePtr->right, nodeIdx, vIndices, nodeExtents, nodeScreenBounds, quiet);
    }
}

void KdTreeAccel_base::printGraphviz(unsigned int batchSize, unsigned int meshId) const {
  char outFile[128];
  sprintf(outFile, "output_%d_%d.dot", batchSize, meshId);
  ofstream out(outFile);
  out << "digraph g {" << endl;
  out << "ratio=compress; fontsize=8; colorscheme=paired12;" << endl;
  out << "node [shape = record,height=.1];" << endl;
  out << "\"" << (void*)m_root << "\"";
  out << "[label = \"";
  if (m_root->triangleIndices) {
    out << "root:" << m_root->triangleIndices->size();
  } else {
    out << "root: 0";
  }
  out << "\"];" << endl;
  printGraphvizHelper(m_root, out, 1);
  out << "}" << endl;
  out.close();
}

void KdTreeAccel_base::printGraphvizAccm(unsigned int batchSize, unsigned int meshId) const {
  char outFile[128];
  sprintf(outFile, "output_%d_%d.dot", batchSize, meshId);
  ofstream out(outFile);
  out << "digraph g {" << endl;
  out << "ratio=compress; fontsize=8; colorscheme=paired12;" << endl;
  out << "node [shape = record,height=.1];" << endl;
  out << "\"" << (void*)m_root << "\"";
  out << "[label = \"";
  if (m_root->triangleIndices) {
    out << "root:" << m_root->triangleIndices->size();
  } else {
    out << "root: 0";
  }
  out << "\"];" << endl;
  printGraphvizHelper(m_root, out, 1, m_root->triangleIndices->size());
  out << "}" << endl;
  out.close();
}

void KdTreeAccel_base::printTreeHelper(KdTreeNode *node) const
{
  if (node->triangleIndices) {
    // prefix traversal
    sort(node->triangleIndices->begin(), node->triangleIndices->end());
    copy(node->triangleIndices->begin(), node->triangleIndices->end(),
         ostream_iterator<int>(cout, " "));
    cout << endl;
  }

  if (node->left != NULL)
    printTreeHelper(node->left);
  if (node->right != NULL)
    printTreeHelper(node->right);
}

// { pointer to task, color id }
std::map<long,int> colors;
const int color_limit = 12;
int color_i = 0;

int getNextColor() {
  return (color_i++)%color_limit + 1;
}

void KdTreeAccel_base::printGraphvizHelper(KdTreeNode *node, ostream &out,
                                           unsigned int level) const {
  if (node->left) {
    out << "\"" << (void*)node->left << "\""
        << "[label=\"" << level << ": ";
    if (node->left->triangleIndices) {
      out << node->left->triangleIndices->size();
    } else {
      out << 0;
    }
    out << "\"];";
    out << "\"" << (void*)node << "\"";
    out << " -> ";
    out << "\"" << (void*)node->left << "\"";
    out << ";" << endl;
  }

  if (node->right) {
    out << "\"" << (void*)node->right << "\""
        << "[label=\"" << level << ": ";
    if (node->right->triangleIndices) {
      out << node->right->triangleIndices->size();
    } else {
      out << 0;
    }
    out << "\"];";
    out << "\"" << (void*)node << "\"";
    out << " -> ";
    out << "\"" << (void*)node->right << "\"";
    out << ";" << endl;
  }
  if (node->left) {
    printGraphvizHelper(node->left, out, level+1);
  }
  if (node->right) {
    printGraphvizHelper(node->right, out, level+1);
  }
}

void KdTreeAccel_base::printGraphvizHelper(KdTreeNode *node, ostream &out,
                                           unsigned int level, uint accm) const {
  accm += node->triangleIndices->size();
  if (node->left) {
    out << "\"" << (void*)node->left << "\""
        << "[label=\"" << level << ": ";
    if (node->left->triangleIndices) {
      out << accm+node->left->triangleIndices->size();
    } else {
      out << accm;
    }
    out << "\"];";
    out << "\"" << (void*)node << "\"";
    out << " -> ";
    out << "\"" << (void*)node->left << "\"";
    out << ";" << endl;
  }
  if (node->right) {
    out << "\"" << (void*)node->right << "\""
        << "[label=\"" << level << ": ";
    if (node->right->triangleIndices) {
      out << accm+node->right->triangleIndices->size();
    } else {
      out << accm;
    }
    out << "\"];";
    out << "\"" << (void*)node << "\"";
    out << " -> ";
    out << "\"" << (void*)node->right << "\"";
    out << ";" << endl;
  }
  if (node->left) {
    printGraphvizHelper(node->left, out, level+1, accm);
  }
  if (node->right) {
    printGraphvizHelper(node->right, out, level+1, accm);
  }
}
