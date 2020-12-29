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

#ifndef _TRIANGLE_MESH_H_
#define _TRIANGLE_MESH_H_

#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <string>

#include "Vec3f.h"
#include "Triangle.h"

#define MAX_RENDER_TARGETS 8

class BlendInfo {
public:
    bool sync;

    unsigned int hRes;
    unsigned int vRes;

    bool logicOperation;
    unsigned int logicOpMode;

    bool anyRtBlend;
    bool anyRtCWrite;
    bool rtEnable[MAX_RENDER_TARGETS];
    bool blend[MAX_RENDER_TARGETS];
    unsigned int blendEquation[MAX_RENDER_TARGETS];
    unsigned int srcRGB[MAX_RENDER_TARGETS];
    unsigned int dstRGB[MAX_RENDER_TARGETS];
    unsigned int srcAlpha[MAX_RENDER_TARGETS];
    unsigned int dstAlpha[MAX_RENDER_TARGETS];
    bool writeR[MAX_RENDER_TARGETS];
    bool writeG[MAX_RENDER_TARGETS];
    bool writeB[MAX_RENDER_TARGETS];
    bool writeA[MAX_RENDER_TARGETS];

    unsigned int fragments;
};

class ZTestInfo {
public:
    bool depthTest;
    unsigned int depthFunc;

    bool stencilTest;
    unsigned int stencilFunc;

    bool depthMask;

    unsigned int stencilUpdateMask;
};

class TriangleMesh {
public:
    bool anyBatchBlend;
    bool anyBatchCWrite;
    bool anyBatchZTest;
    std::vector<Triangle> triangleList;
    BoundingBox boundingBox;
    BoundingBox screenBoundingBox;
    BoundingBox unclippedScreenBoundingBox;
    std::vector<std::vector<Triangle> > triangleListPerBatch;
    std::vector<BoundingBox> boundingBoxesPerBatch;
    std::vector<BoundingBox> screenBoundingBoxesPerBatch;
    std::vector<BoundingBox> unclippedScreenBoundingBoxesPerBatch;
    std::vector<unsigned int> unclippedTrisPerBatch;
    std::vector<unsigned int> fragmentsPerBatch;
    std::vector<unsigned int> hResPerBatch;
    std::vector<unsigned int> vResPerBatch;
    std::vector<bool> forcedFrameDup;
    std::vector<bool> forcedSplit;
    std::vector<bool> zFighted;
};

class TriangleMeshes {
public:
    TriangleMeshes();

    void parseBlendInfo(std::istream &blend);
    void parseZTestInfo(std::istream &ztest);
    void parseZFightingInfo(std::istream &zfighting);
    void annotateZFightingInfo(unsigned currentMesh, unsigned currentBatch);
    void addTriangles(std::istream &vertexes);
    void addTriangles(const std::string &inputVertexesFile, const std::string &blendInfoFile,
		      const std::string &ztestInfoFile, const std::string &zfightingInfoFile);
    
    // Object serialization
    void serialize(std::ostream &out) const;
    void deserialize(std::istream &in);

    unsigned int meshes;
    unsigned int batchSize;
    std::vector<std::vector<BlendInfo> > blendInfos;
    std::vector<std::vector<ZTestInfo> > ztestInfos;
    std::map<unsigned, std::set<unsigned> > zFightedDraws;
    std::vector<TriangleMesh> triangleMeshes;
};

#endif // _TRIANGLE_MESH_H_
