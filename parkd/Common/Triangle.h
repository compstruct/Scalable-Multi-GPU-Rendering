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

#ifndef _TRIANGLE_H_
#define _TRIANGLE_H_

#include "BoundingBox.h"
#include "Vec3f.h"

// forward declaration - cyclic dependency
class TriangleMesh;

class Triangle {
public:
  // Default Constructor
  Triangle();
  
  // Constructor with arguments
  Triangle(Vec3f &v0, Vec3f &v1, Vec3f &v2);
  Triangle(unsigned int frame, unsigned int batch, bool clipped,
	   unsigned int index0, unsigned int index1, unsigned int index2,
	   Vec3f v0, Vec3f v1, Vec3f v2,
	   Vec3f screenv0, Vec3f screenv1, Vec3f screenv2);

  // Object serialization
  void serialize(std::ostream &out) const;
  void deserialize(std::istream &in);

  BoundingBox bound;
  BoundingBox screenBound;
  
  unsigned int frameCounter;
  unsigned int batchCounter;
  unsigned int index[3];
  bool clipped;

private:
  Vec3f vertex[3];
  Vec3f screenVertex[3];
  // Computes bounding box of Triangle and stores result in b
  void compute_bound();
  void compute_screen_bound();
};

#endif // _TRIANGLE_H_
