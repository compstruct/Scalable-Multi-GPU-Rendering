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

#include <vector>
#include <math.h>
#include <stdlib.h>

#include <iostream>
#include <sstream>
#include <fstream>

#include "Triangle.h"
#include "TriangleMesh.h"
#include "BoundingBox.h"

using namespace std;

TriangleMeshes::TriangleMeshes() {
    meshes = 0;
    batchSize = 0;
}

void TriangleMeshes::parseBlendInfo(istream &blend) {
    string first;
    unsigned int frameCounter, batchCounter;
    string logicOperation_str, rtEnable_str, blend_str;
    string writeR_str, writeG_str, writeB_str, writeA_str;
    BlendInfo blendInfo;
    unsigned int rt;

    blendInfo.sync = false;
    blendInfo.anyRtBlend = false;
    blendInfo.anyRtCWrite = false;

    blend >> first;
    while (!blend.eof()) {
	if (first.substr(0, 4) == "sync") {
	    blend >> frameCounter >> batchCounter;
	    blendInfo.sync = true;
	} else if (first == "d") {
	    blend >> frameCounter >> batchCounter >> blendInfo.hRes >> blendInfo.vRes;

	    if (frameCounter == blendInfos.size()) {
	        blendInfos.push_back(vector<BlendInfo>());
	    }

	    blend >> logicOperation_str >> blendInfo.logicOpMode;
	    if (logicOperation_str == std::string("T"))
              blendInfo.logicOperation = true;
            else if (logicOperation_str == std::string("F"))
              blendInfo.logicOperation = false;
            else 
              assert(false);
	} else if (first == "rt") {
	    blend >> rt >> rtEnable_str >> blend_str;
           
	    if (rtEnable_str == std::string("T"))
              blendInfo.rtEnable[rt] = true;
            else if (rtEnable_str == std::string("F"))
              blendInfo.rtEnable[rt] = false;
            else 
              assert(false);

	    if (blend_str == std::string("T"))
              blendInfo.blend[rt] = true;
            else if (blend_str == std::string("F"))
              blendInfo.blend[rt] = false;
            else 
              assert(false);

	    blend >> blendInfo.blendEquation[rt] >> blendInfo.srcRGB[rt] >> blendInfo.dstRGB[rt]
		  >> blendInfo.srcAlpha[rt] >> blendInfo.dstAlpha[rt];

	    blend >> writeR_str >> writeG_str >> writeB_str >> writeA_str;

	    if (writeR_str == std::string("T"))
              blendInfo.writeR[rt] = true;
            else if (writeR_str == std::string("F"))
              blendInfo.writeR[rt] = false;
            else 
              assert(false);

	    if (writeG_str == std::string("T"))
              blendInfo.writeG[rt] = true;
            else if (writeG_str == std::string("F"))
              blendInfo.writeG[rt] = false;
            else 
              assert(false);

	    if (writeB_str == std::string("T"))
              blendInfo.writeB[rt] = true;
            else if (writeB_str == std::string("F"))
              blendInfo.writeB[rt] = false;
            else 
              assert(false);

	    if (writeA_str == std::string("T"))
              blendInfo.writeA[rt] = true;
            else if (writeA_str == std::string("F"))
              blendInfo.writeA[rt] = false;
            else 
              assert(false);

	    bool rtBlend = blendInfo.rtEnable[rt] && blendInfo.blend[rt] &&
		           (blendInfo.dstRGB[rt] != 0 || blendInfo.dstAlpha[rt] != 0) &&
		           (blendInfo.writeR[rt] || blendInfo.writeG[rt] || blendInfo.writeB[rt] || blendInfo.writeA[rt]);
	    blendInfo.anyRtBlend = blendInfo.anyRtBlend || rtBlend;
	    blendInfo.anyRtCWrite = blendInfo.anyRtCWrite || (blendInfo.rtEnable[rt] &&
		                    (blendInfo.writeR[rt] || blendInfo.writeG[rt] || blendInfo.writeB[rt] || blendInfo.writeA[rt]));

            if (rt == MAX_RENDER_TARGETS - 1) {
		blendInfos[frameCounter].push_back(blendInfo);
	        blendInfo.sync = false;
                blendInfo.anyRtBlend = false;
		blendInfo.anyRtCWrite = false;
	    }	
	} else if (first == "fragments") {
	    blend >> frameCounter >> batchCounter;
	    blend >> blendInfos[frameCounter][batchCounter].fragments;
	} else {
	    cout << first << endl;
	    assert(false);
	}

	blend >> first;
    }
}

void TriangleMeshes::parseZTestInfo(istream &ztest) {
    string first;
    unsigned int frameCounter, batchCounter;
    string depthTest_str, stencilTest_str, depthMask_str;
    ZTestInfo ztestInfo;

    ztest >> first;
    while (!ztest.eof()) {
        assert(first == "d");

	ztest >> frameCounter >> batchCounter;

	if (frameCounter == ztestInfos.size()) {
	    ztestInfos.push_back(vector<ZTestInfo>());
	}
       
	ztest >> depthTest_str;
	if (depthTest_str == std::string("T"))
          ztestInfo.depthTest = true;
        else if (depthTest_str == std::string("F"))
          ztestInfo.depthTest = false;
        else 
          assert(false);

	ztest >> ztestInfo.depthFunc;

	ztest >> stencilTest_str;
	if (stencilTest_str == std::string("T"))
          ztestInfo.stencilTest = true;
        else if (stencilTest_str == std::string("F"))
          ztestInfo.stencilTest = false;
        else 
          assert(false);

	ztest >> ztestInfo.stencilFunc;

	ztest >> depthMask_str;
	if (depthMask_str == std::string("T"))
          ztestInfo.depthMask = true;
        else if (depthMask_str == std::string("F"))
          ztestInfo.depthMask = false;
        else 
          assert(false);

	ztest >> std::hex >> ztestInfo.stencilUpdateMask >> std::dec;
	
	ztestInfos[frameCounter].push_back(ztestInfo);
    
	ztest >> first;
    }
}

void TriangleMeshes::parseZFightingInfo(istream &zfighting) {
    unsigned draw, fightedDraw;
    string line;
    while (std::getline(zfighting, line)) {
	istringstream iss(line);
	iss >> draw;
	while (iss >> fightedDraw)
	    zFightedDraws[draw].insert(fightedDraw);
    }
}

void TriangleMeshes::annotateZFightingInfo(unsigned currentMesh, unsigned currentBatch) {
    if (!triangleMeshes[currentMesh - 1].anyBatchCWrite)
	return;

    unsigned numDraws = triangleMeshes[currentMesh - 1].zFighted.size();
    if (numDraws < 2)
	return;

    for (unsigned n = numDraws; n > 0; n--) {
	unsigned draw = currentBatch - n;
	std::set<unsigned>::iterator it;
	if (zFightedDraws.count(draw) > 0) {
	    //for (it = zFightedDraws[draw].begin(); it != zFightedDraws[draw].end(); it++) {
		//if (*it >= currentBatch - numDraws && *it < currentBatch) {
		    triangleMeshes[currentMesh - 1].zFighted[numDraws - n] = true;
		    //std::cout << "set draw " << draw << " index " << (numDraws - n) << " as fighted" << std::endl;
		//}
	    //}
	}
    }
}

void TriangleMeshes::addTriangles(const string &inputVertexesFile, const string &blendInfoFile,
		                  const string &ztestInfoFile, const string &zfightingInfoFile) {
    ifstream blend(blendInfoFile.c_str());
    if (blend.is_open()) {
        parseBlendInfo(blend);
	blend.close();
    }

    ifstream ztest(ztestInfoFile.c_str());
    if (ztest.is_open()) {
        parseZTestInfo(ztest);
	ztest.close();
    }
    
    ifstream zfighting(zfightingInfoFile.c_str());
    if (zfighting.is_open()) {
        parseZFightingInfo(zfighting);
	zfighting.close();
    }

    ifstream vertexes(inputVertexesFile.c_str());
    if (vertexes.is_open()) {
        addTriangles(vertexes);
	vertexes.close();
    }
}

void TriangleMeshes::addTriangles(istream &vertexes) {
  string first;
  unsigned int frameCounter, batchCounter, lastFrameCounter, lastBatchCounter;
  Triangle tri;
  int trii[3];
  string clipped_str; bool clipped;
  string triCoord[3][3];
  string triScreenCoord[3][3];

  bool createNewTriangleMesh = false;
  unsigned int batches = 0;

  bool nonBypassedBatchFound = false;
  unsigned int currenthRes, lasthRes;
  unsigned int currentvRes, lastvRes;
  bool currentLogicOperation, lastLogicOperation;
  unsigned int currentLogicOpMode, lastLogicOpMode;
  bool rtEnable[MAX_RENDER_TARGETS], lastRtEnable[MAX_RENDER_TARGETS];
  unsigned int blend[MAX_RENDER_TARGETS];
  unsigned int currentBlendEquation[MAX_RENDER_TARGETS], lastBlendEquation[MAX_RENDER_TARGETS];
  unsigned int currentSrcRGB[MAX_RENDER_TARGETS], lastSrcRGB[MAX_RENDER_TARGETS];
  unsigned int currentDstRGB[MAX_RENDER_TARGETS], lastDstRGB[MAX_RENDER_TARGETS];
  bool depthTest;
  unsigned int currentDepthFunc, lastDepthFunc;
  bool currentDepthMask, lastDepthMask;

  float left_min = 0, right_max = 0, bottom_min = 0, top_max = 0, screenArea = 0;
  unsigned int unclipps = 0;
  BoundingBox screenBound;
  vector<Triangle>::iterator iter;
  TriangleMesh triangleMesh_buf;

  lastFrameCounter = 0;
  lastBatchCounter = 0;
  lasthRes = blendInfos[0][0].hRes;
  lastvRes = blendInfos[0][0].vRes;
  lastLogicOperation = blendInfos[0][0].logicOperation;
  lastLogicOpMode = blendInfos[0][0].logicOpMode;
  lastDepthFunc = ztestInfos[0][0].depthFunc;
  lastDepthMask = ztestInfos[0][0].depthMask;
 
  triangleMeshes.push_back(TriangleMesh());
  triangleMeshes[meshes].anyBatchBlend = false;
  triangleMeshes[meshes].anyBatchCWrite = false;
  triangleMeshes[meshes].anyBatchZTest = false;
  meshes++;
 
  vertexes >> first; 
  while (!vertexes.eof()) {
    if (first == "d") {
      vertexes >> frameCounter >> batchCounter;

      if (frameCounter != lastFrameCounter) {
        createNewTriangleMesh = true;
      }

      if (batches > 0 && blendInfos[frameCounter][batchCounter].sync) 
        createNewTriangleMesh = true;

      currenthRes = blendInfos[frameCounter][batchCounter].hRes;
      currentvRes = blendInfos[frameCounter][batchCounter].vRes;
      if (currenthRes != lasthRes || currentvRes != lastvRes) {
          createNewTriangleMesh = true;
      }
      lasthRes = currenthRes;
      lastvRes = currentvRes;

      currentLogicOperation = blendInfos[frameCounter][batchCounter].logicOperation;
      currentLogicOpMode = blendInfos[frameCounter][batchCounter].logicOpMode;
      if (currentLogicOperation != lastLogicOperation || currentLogicOpMode != lastLogicOpMode) {
        createNewTriangleMesh = true;
      }
      lastLogicOperation = currentLogicOperation;
      lastLogicOpMode = currentLogicOpMode;

      currentDepthMask = ztestInfos[frameCounter][batchCounter].depthMask;
      if (currentDepthMask != lastDepthMask)
	  createNewTriangleMesh = true;
      lastDepthMask = currentDepthMask;

      depthTest = ztestInfos[frameCounter][batchCounter].depthTest;
      currentDepthFunc = ztestInfos[frameCounter][batchCounter].depthFunc;
      if (!depthTest)
        currentDepthFunc = 1;
      if (batches > 0 && currentDepthMask && currentDepthFunc != lastDepthFunc)
        createNewTriangleMesh = true;
      lastDepthFunc = currentDepthFunc;

      for (unsigned int rt = 0; rt < MAX_RENDER_TARGETS; rt++) {
        rtEnable[rt] = blendInfos[frameCounter][batchCounter].rtEnable[rt];
        blend[rt] = blendInfos[frameCounter][batchCounter].blend[rt];
	currentBlendEquation[rt] = blendInfos[frameCounter][batchCounter].blendEquation[rt];
        currentSrcRGB[rt] = blendInfos[frameCounter][batchCounter].srcRGB[rt];
        currentDstRGB[rt] = blendInfos[frameCounter][batchCounter].dstRGB[rt];
	bool bypassCW = !blendInfos[frameCounter][batchCounter].writeR[rt] && !blendInfos[frameCounter][batchCounter].writeG[rt] &&
	                !blendInfos[frameCounter][batchCounter].writeB[rt] && !blendInfos[frameCounter][batchCounter].writeA[rt];
	if (!blend[rt] && !bypassCW) {
            currentSrcRGB[rt] = 1;
            currentDstRGB[rt] = 0;
	}

	if (batches > 0 && rtEnable[rt] != lastRtEnable[rt])
	    createNewTriangleMesh = true;

	if (batches > 0 && rtEnable[rt] && (currentBlendEquation[rt] != lastBlendEquation[rt]))
	    createNewTriangleMesh = true;

	if (nonBypassedBatchFound && rtEnable[rt] && triangleMeshes[meshes - 1].anyBatchBlend && bypassCW)
	    createNewTriangleMesh = true;

	if (nonBypassedBatchFound && rtEnable[rt] && !bypassCW &&
            (((currentSrcRGB[rt] != lastSrcRGB[rt]) && !((currentSrcRGB[rt] == 1 && lastSrcRGB[rt] == 6) || (currentSrcRGB[rt] == 6 && lastSrcRGB[rt] == 1))) ||
             ((currentDstRGB[rt] != lastDstRGB[rt]) && !((currentDstRGB[rt] == 1 && lastDstRGB[rt] == 8) || (currentDstRGB[rt] == 8 && lastDstRGB[rt] == 1))))
	   ) {
	  createNewTriangleMesh = true;
	}

	lastRtEnable[rt] = rtEnable[rt];
	lastBlendEquation[rt] = currentBlendEquation[rt];
	if (!bypassCW) {
	    lastSrcRGB[rt] = currentSrcRGB[rt];
	    lastDstRGB[rt] = currentDstRGB[rt];
	    nonBypassedBatchFound = true;
	}
      }

      if (batches > 0) {
	if ((triangleMesh_buf.triangleList.size() > 16384) ||
	    (!currentDepthMask && (!ztestInfos[frameCounter][batchCounter - 1].depthTest || ztestInfos[frameCounter][batchCounter - 1].depthFunc == 1) &&
	     screenArea == 4 && blendInfos[frameCounter][batchCounter - 1].anyRtCWrite)) {
	    triangleMeshes.push_back(TriangleMesh());
	    triangleMeshes[meshes].anyBatchBlend = false;
	    triangleMeshes[meshes].anyBatchCWrite = false;
	    triangleMeshes[meshes].anyBatchZTest = false;
	    meshes++;
	    batches = 0;
	    nonBypassedBatchFound = false;
	  
	    annotateZFightingInfo(meshes - 1, lastBatchCounter);
	}

	//std::cout << "batch " << lastBatchCounter << " screenArea " << screenArea << std::endl;

	triangleMeshes[meshes - 1].anyBatchBlend = triangleMeshes[meshes - 1].anyBatchBlend || blendInfos[lastFrameCounter][lastBatchCounter].anyRtBlend;
	triangleMeshes[meshes - 1].anyBatchCWrite = triangleMeshes[meshes - 1].anyBatchCWrite || blendInfos[lastFrameCounter][lastBatchCounter].anyRtCWrite;
	triangleMeshes[meshes - 1].anyBatchZTest = triangleMeshes[meshes - 1].anyBatchZTest || ztestInfos[lastFrameCounter][lastBatchCounter].depthTest;
	triangleMeshes[meshes - 1].triangleListPerBatch.push_back(std::vector<Triangle>());
	for (iter = triangleMesh_buf.triangleList.begin(); iter != triangleMesh_buf.triangleList.end(); iter++) {
	  triangleMeshes[meshes - 1].triangleList.push_back(*iter);
	  triangleMeshes[meshes - 1].triangleListPerBatch[(batches == 0 ? 0 : batches - 1)].push_back(*iter);
	}
	triangleMeshes[meshes - 1].boundingBoxesPerBatch.push_back(triangleMesh_buf.boundingBox);
	triangleMeshes[meshes - 1].screenBoundingBoxesPerBatch.push_back(triangleMesh_buf.screenBoundingBox);
        triangleMeshes[meshes - 1].unclippedScreenBoundingBoxesPerBatch.push_back(triangleMesh_buf.unclippedScreenBoundingBox);
        triangleMeshes[meshes - 1].boundingBox += triangleMesh_buf.boundingBox;
        triangleMeshes[meshes - 1].screenBoundingBox += triangleMesh_buf.screenBoundingBox;
        triangleMeshes[meshes - 1].unclippedScreenBoundingBox += triangleMesh_buf.unclippedScreenBoundingBox;
	triangleMeshes[meshes - 1].unclippedTrisPerBatch.push_back(unclipps);
	triangleMeshes[meshes - 1].fragmentsPerBatch.push_back(blendInfos[lastFrameCounter][lastBatchCounter].fragments);
	triangleMeshes[meshes - 1].hResPerBatch.push_back(blendInfos[lastFrameCounter][lastBatchCounter].hRes);
	triangleMeshes[meshes - 1].vResPerBatch.push_back(blendInfos[lastFrameCounter][lastBatchCounter].vRes);
	//triangleMeshes[meshes - 1].forcedFrameDup.push_back(screenArea > 2);
	//triangleMeshes[meshes - 1].forcedSplit.push_back(triangleMesh_buf.triangleList.size() > 2048);
	triangleMeshes[meshes - 1].forcedFrameDup.push_back(false);
	triangleMeshes[meshes - 1].forcedSplit.push_back(false);
	triangleMeshes[meshes - 1].zFighted.push_back(false);
	lastFrameCounter = frameCounter;
	lastBatchCounter = batchCounter;

        if (createNewTriangleMesh || (triangleMesh_buf.triangleList.size() > 16384) ||
	    (!currentDepthMask && (!ztestInfos[frameCounter][batchCounter - 1].depthTest || ztestInfos[frameCounter][batchCounter - 1].depthFunc == 1) &&
	     screenArea == 4 && blendInfos[frameCounter][batchCounter - 1].anyRtCWrite)) {
	  triangleMeshes.push_back(TriangleMesh());
	  triangleMeshes[meshes].anyBatchBlend = false;
	  triangleMeshes[meshes].anyBatchCWrite = false;
	  triangleMeshes[meshes].anyBatchZTest = false;
	  meshes++;
	  batches = 0;
	  nonBypassedBatchFound = false;

	  annotateZFightingInfo(meshes - 1, batchCounter);

	  createNewTriangleMesh = false;
	}
      }

      triangleMesh_buf.triangleList.clear();
      triangleMesh_buf.boundingBox.reset();
      triangleMesh_buf.screenBoundingBox.reset();
      triangleMesh_buf.unclippedScreenBoundingBox.reset();

      screenBound.reset();
      screenArea = 0;
      unclipps = 0;
      
      if (batchSize > 0 && batches == batchSize) {
        triangleMeshes.push_back(TriangleMesh());
	triangleMeshes[meshes].anyBatchBlend = false;
	triangleMeshes[meshes].anyBatchCWrite = false;
	triangleMeshes[meshes].anyBatchZTest = false;
        meshes++;
        batches = 0;
	nonBypassedBatchFound = false;
      }
      
      batches++;
    } else if (first == "f") {
      vertexes >> trii[0] >> trii[1] >> trii[2]; 

      vertexes >> clipped_str;
      
      vertexes >> triCoord[0][0] >> triCoord[0][1] >> triCoord[0][2]
               >> triCoord[1][0] >> triCoord[1][1] >> triCoord[1][2]
               >> triCoord[2][0] >> triCoord[2][1] >> triCoord[2][2];
      
      vertexes >> triScreenCoord[0][0] >> triScreenCoord[0][1] >> triScreenCoord[0][2]
               >> triScreenCoord[1][0] >> triScreenCoord[1][1] >> triScreenCoord[1][2]
               >> triScreenCoord[2][0] >> triScreenCoord[2][1] >> triScreenCoord[2][2];
      
      if (clipped_str == std::string("T"))
        clipped = true;
      else if (clipped_str == std::string("F"))
        clipped = false;
      else 
        assert(false);
    
      tri = Triangle(frameCounter, batchCounter,
      	             clipped, trii[0], trii[1], trii[2],
      	             Vec3f(atof(triCoord[0][0].c_str()), atof(triCoord[0][1].c_str()), atof(triCoord[0][2].c_str())),
      	             Vec3f(atof(triCoord[1][0].c_str()), atof(triCoord[1][1].c_str()), atof(triCoord[1][2].c_str())),
      	             Vec3f(atof(triCoord[2][0].c_str()), atof(triCoord[2][1].c_str()), atof(triCoord[2][2].c_str())),
      	             Vec3f(atof(triScreenCoord[0][0].c_str()), atof(triScreenCoord[0][1].c_str()), atof(triScreenCoord[0][2].c_str())),
      	             Vec3f(atof(triScreenCoord[1][0].c_str()), atof(triScreenCoord[1][1].c_str()), atof(triScreenCoord[1][2].c_str())),
      	             Vec3f(atof(triScreenCoord[2][0].c_str()), atof(triScreenCoord[2][1].c_str()), atof(triScreenCoord[2][2].c_str())));

      triangleMesh_buf.triangleList.push_back(tri);
      triangleMesh_buf.boundingBox += tri.bound;
      triangleMesh_buf.screenBoundingBox += tri.screenBound;

      if (!clipped) {
        triangleMesh_buf.unclippedScreenBoundingBox += tri.screenBound;
        unclipps++;

	screenBound += tri.screenBound;
        left_min = screenBound.min[0] < -1 ? -1 : (screenBound.min[0] > 1 ? 1 : screenBound.min[0]);
        right_max = screenBound.max[0] > 1 ? 1 : (screenBound.max[0] < -1 ? -1 : screenBound.max[0]);
        bottom_min = screenBound.min[1] < -1 ? -1 : (screenBound.min[1] > 1 ? 1 : screenBound.min[1]);
        top_max = screenBound.max[1] > 1 ? 1 : (screenBound.max[1] < -1 ? -1 : screenBound.max[1]);

	//screenArea = (right_max - left_min)*(top_max - bottom_min);
	screenArea = (screenBound.max[0] - screenBound.min[0]) * (screenBound.max[1] - screenBound.min[1]);
      }
    }
    
    vertexes >> first;
  }
  
  if ((triangleMesh_buf.triangleList.size() > 16384) ||
      (!currentDepthMask && (!ztestInfos[frameCounter][batchCounter - 1].depthTest || ztestInfos[frameCounter][batchCounter - 1].depthFunc == 1) &&
       screenArea == 4 && blendInfos[frameCounter][batchCounter - 1].anyRtCWrite)) {
      triangleMeshes.push_back(TriangleMesh());
      triangleMeshes[meshes].anyBatchBlend = false;
      triangleMeshes[meshes].anyBatchCWrite = false;
      triangleMeshes[meshes].anyBatchZTest = false;
      meshes++;
      batches = 0;
      nonBypassedBatchFound = false;
  
      annotateZFightingInfo(meshes - 1, batchCounter);
  }

  triangleMeshes[meshes - 1].anyBatchBlend = triangleMeshes[meshes - 1].anyBatchBlend || blendInfos[lastFrameCounter][lastBatchCounter].anyRtBlend;
  triangleMeshes[meshes - 1].anyBatchCWrite = triangleMeshes[meshes - 1].anyBatchCWrite || blendInfos[lastFrameCounter][lastBatchCounter].anyRtCWrite;
  triangleMeshes[meshes - 1].anyBatchZTest = triangleMeshes[meshes - 1].anyBatchZTest || ztestInfos[lastFrameCounter][lastBatchCounter].depthTest;
  triangleMeshes[meshes - 1].triangleListPerBatch.push_back(std::vector<Triangle>());
  for (iter = triangleMesh_buf.triangleList.begin(); iter != triangleMesh_buf.triangleList.end(); iter++) {
    triangleMeshes[meshes - 1].triangleList.push_back(*iter);
    triangleMeshes[meshes - 1].triangleListPerBatch[(batches == 0 ? 0 : batches - 1)].push_back(*iter);
  }
  triangleMeshes[meshes - 1].boundingBoxesPerBatch.push_back(triangleMesh_buf.boundingBox);
  triangleMeshes[meshes - 1].screenBoundingBoxesPerBatch.push_back(triangleMesh_buf.screenBoundingBox);
  triangleMeshes[meshes - 1].unclippedScreenBoundingBoxesPerBatch.push_back(triangleMesh_buf.unclippedScreenBoundingBox);
  triangleMeshes[meshes - 1].boundingBox += triangleMesh_buf.boundingBox;
  triangleMeshes[meshes - 1].screenBoundingBox += triangleMesh_buf.screenBoundingBox;
  triangleMeshes[meshes - 1].unclippedScreenBoundingBox += triangleMesh_buf.unclippedScreenBoundingBox;
  triangleMeshes[meshes - 1].unclippedTrisPerBatch.push_back(unclipps);
  triangleMeshes[meshes - 1].fragmentsPerBatch.push_back(blendInfos[lastFrameCounter][lastBatchCounter].fragments);
  triangleMeshes[meshes - 1].hResPerBatch.push_back(blendInfos[lastFrameCounter][lastBatchCounter].hRes);
  triangleMeshes[meshes - 1].vResPerBatch.push_back(blendInfos[lastFrameCounter][lastBatchCounter].vRes);
  //triangleMeshes[meshes - 1].forcedFrameDup.push_back(screenArea > 2);
  //triangleMeshes[meshes - 1].forcedSplit.push_back(triangleMesh_buf.triangleList.size() > 2048);
  triangleMeshes[meshes - 1].forcedFrameDup.push_back(false);
  triangleMeshes[meshes - 1].forcedSplit.push_back(false);
  triangleMeshes[meshes - 1].zFighted.push_back(false);
  lastFrameCounter = frameCounter;
  lastBatchCounter = batchCounter;

  annotateZFightingInfo(meshes, batchCounter + 1);
  
  return;
}

void TriangleMeshes::serialize(std::ostream &out) const {
    int meshes = triangleMeshes.size();
    out.write((char*)&meshes, sizeof(int));

    for (int m = 0; m < meshes; m++) {
	bool anyBatchBlend = triangleMeshes[m].anyBatchBlend;
        out.write((char*)&anyBatchBlend, sizeof(bool));
	bool anyBatchCWrite = triangleMeshes[m].anyBatchCWrite;
        out.write((char*)&anyBatchCWrite, sizeof(bool));
	bool anyBatchZTest = triangleMeshes[m].anyBatchZTest;
        out.write((char*)&anyBatchZTest, sizeof(bool));
        int batches = triangleMeshes[m].triangleListPerBatch.size();
        out.write((char*)&batches, sizeof(int));
	for (int b = 0; b < batches; b++) {
            int size = triangleMeshes[m].triangleListPerBatch[b].size();
            out.write((char*)&size, sizeof(int));

            // Relying on STL vector's guarantee on data layout (continuity)
            out.write((char*)&triangleMeshes[m].triangleListPerBatch[b][0],
		      sizeof(triangleMeshes[m].triangleListPerBatch[b][0])*size);

	    triangleMeshes[m].boundingBoxesPerBatch[b].serialize(out);
	    triangleMeshes[m].screenBoundingBoxesPerBatch[b].serialize(out);
	    triangleMeshes[m].unclippedScreenBoundingBoxesPerBatch[b].serialize(out);
	    
	    int unclipps = triangleMeshes[m].unclippedTrisPerBatch[b];
            out.write((char*)&unclipps, sizeof(int));
	    int fragments = triangleMeshes[m].fragmentsPerBatch[b];
            out.write((char*)&fragments, sizeof(int));
	    int hRes = triangleMeshes[m].hResPerBatch[b];
	    out.write((char*)&hRes, sizeof(int));
	    int vRes = triangleMeshes[m].vResPerBatch[b];
	    out.write((char*)&vRes, sizeof(int));
	    bool frameDup = triangleMeshes[m].forcedFrameDup[b];
	    out.write((char*)&frameDup, sizeof(bool));
	    bool split = triangleMeshes[m].forcedSplit[b];
	    out.write((char*)&split, sizeof(bool));
	    bool zfighted = triangleMeshes[m].zFighted[b];
	    out.write((char*)&zfighted, sizeof(bool));
	}
	
        triangleMeshes[m].boundingBox.serialize(out);
        triangleMeshes[m].screenBoundingBox.serialize(out);
        triangleMeshes[m].unclippedScreenBoundingBox.serialize(out);
    }
}

void TriangleMeshes::deserialize(std::istream &in) {
    int currentMesh = triangleMeshes.size();
    int meshes;
    in.read((char*)&meshes, sizeof(int));

    triangleMeshes.resize(meshes + currentMesh);

    for (int m = 0; m < meshes; m++) {
	bool anyBatchBlend;
        in.read((char*)&anyBatchBlend, sizeof(bool));
	triangleMeshes[m + currentMesh].anyBatchBlend = anyBatchBlend;
	bool anyBatchCWrite;
        in.read((char*)&anyBatchCWrite, sizeof(bool));
	triangleMeshes[m + currentMesh].anyBatchCWrite = anyBatchCWrite;
	bool anyBatchZTest;
        in.read((char*)&anyBatchZTest, sizeof(bool));
	triangleMeshes[m + currentMesh].anyBatchZTest = anyBatchZTest;
        int batches;
        in.read((char*)&batches, sizeof(int));
	triangleMeshes[m + currentMesh].triangleListPerBatch.resize(batches);
        triangleMeshes[m + currentMesh].boundingBoxesPerBatch.resize(batches);
        triangleMeshes[m + currentMesh].screenBoundingBoxesPerBatch.resize(batches);
        triangleMeshes[m + currentMesh].unclippedScreenBoundingBoxesPerBatch.resize(batches);
	triangleMeshes[m + currentMesh].unclippedTrisPerBatch.resize(batches);
	triangleMeshes[m + currentMesh].fragmentsPerBatch.resize(batches);
	triangleMeshes[m + currentMesh].hResPerBatch.resize(batches);
	triangleMeshes[m + currentMesh].vResPerBatch.resize(batches);
	triangleMeshes[m + currentMesh].forcedFrameDup.resize(batches);
	triangleMeshes[m + currentMesh].forcedSplit.resize(batches);
	triangleMeshes[m + currentMesh].zFighted.resize(batches);

	for (int b = 0; b < batches; b++) {
            int size;
            in.read((char*)&size, sizeof(int));
            triangleMeshes[m + currentMesh].triangleListPerBatch[b].resize(size);

            // Relying on STL vector's guarantee on data layout (continuity)
            in.read((char*)&triangleMeshes[m + currentMesh].triangleListPerBatch[b][0],
		    sizeof(triangleMeshes[m + currentMesh].triangleListPerBatch[b][0])*size);

	    triangleMeshes[m + currentMesh].boundingBoxesPerBatch[b].deserialize(in);
	    triangleMeshes[m + currentMesh].screenBoundingBoxesPerBatch[b].deserialize(in);
	    triangleMeshes[m + currentMesh].unclippedScreenBoundingBoxesPerBatch[b].deserialize(in);

	    int unclipps;
            in.read((char*)&unclipps, sizeof(int));
	    triangleMeshes[m + currentMesh].unclippedTrisPerBatch[b] = unclipps;
	    int fragments;
            in.read((char*)&fragments, sizeof(int));
	    triangleMeshes[m + currentMesh].fragmentsPerBatch[b] = fragments;
	    int hRes;
	    in.read((char*)&hRes, sizeof(int));
	    triangleMeshes[m + currentMesh].hResPerBatch[b] = hRes;
	    int vRes;
	    in.read((char*)&vRes, sizeof(int));
	    triangleMeshes[m + currentMesh].vResPerBatch[b] = vRes;
	    bool frameDup;
            in.read((char*)&frameDup, sizeof(bool));
	    triangleMeshes[m + currentMesh].forcedFrameDup[b] = frameDup;
	    bool split;
            in.read((char*)&split, sizeof(bool));
	    triangleMeshes[m + currentMesh].forcedSplit[b] = split;
	    bool zfighted;
            in.read((char*)&zfighted, sizeof(bool));
	    triangleMeshes[m + currentMesh].zFighted[b] = zfighted;
	}

        triangleMeshes[m + currentMesh].boundingBox.deserialize(in);
        triangleMeshes[m + currentMesh].screenBoundingBox.deserialize(in);
        triangleMeshes[m + currentMesh].unclippedScreenBoundingBox.deserialize(in);
    }
}
