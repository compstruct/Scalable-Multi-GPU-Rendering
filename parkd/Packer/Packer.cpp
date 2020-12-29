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
#include <cstdlib>

#include "TriangleMesh.h"

using namespace std;

void usage() {
  string usage[] = {
    "Usage: ./packer -b batchSize -o output.blob input.obj",
    "==="
  };

  int i=0;
  while(usage[i] != "===") {
      cout << usage[i++] << endl;
  }

  exit(0);
}

int main(int argc, char *argv[]) {
  char *inputVertexes = NULL;
  char *blendInfo = NULL;
  char *ztestInfo = NULL;
  char *zfightingInfo = NULL;
  char *output = NULL;
  unsigned int batchSize = 0;

  for (unsigned int i=1;i<argc;i++) {
    if (!strcmp(argv[i], "-h")) {
      usage();
    } else if (!strcmp(argv[i], "-b")) {
      i++;
      if (argc <= i)
          usage();
      else
          batchSize = atoi(argv[i]);
    } else if (!strcmp(argv[i], "-o")) {
      i++;
      if (argc <= i)
          usage();
      else
          output = argv[i];
    } else {
      inputVertexes = argv[i];
      blendInfo = argv[++i];
      ztestInfo = argv[++i];
      zfightingInfo = argv[++i];
    }
  }

  //ifstream ifs("/dev/stdin", fstream::binary);
  //ofstream ofs("/dev/stdout", fstream::binary);
  ofstream ofs(output, fstream::binary);

  TriangleMeshes meshes;
  meshes.batchSize = batchSize;
  meshes.addTriangles(inputVertexes, blendInfo, ztestInfo, zfightingInfo);
  meshes.serialize(ofs);

  //ifs.close();
  ofs.close();
}
