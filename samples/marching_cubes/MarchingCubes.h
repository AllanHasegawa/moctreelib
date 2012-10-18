/*
 * Copyright (c) 2012 Allan Yoshio Hasegawa
 * 
 * Permission is hereby granted, free of charge, to any
 * person obtaining a copy of this software and associated
 * documentation files (the "Software"), to deal in the
 * Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute,
 * sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall
 * be included in all copies or substantial portions of the
 * Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY
 * KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 * WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
 * PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS
 * OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
 * OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#ifndef MOCTREE_MARCHINGCUBES_H_
#define MOCTREE_MARCHINGCUBES_H_

#include <MCTemplate.h>

class MarchingCubes {
 public:

  virtual ~MarchingCubes();

  static MarchingCubes* CreateMarchingCubes();

  MCTemplate* GetTemplate(const int index);
  MCTemplate* GetTemplate(const bool v0, const bool v1, const bool v2,
                          const bool v3, const bool v4, const bool v5,
                          const bool v6, const bool v7);

  static inline int CornersToIndex(const bool v0, const bool v1, const bool v2,
                                   const bool v3, const bool v4, const bool v5,
                                   const bool v6, const bool v7) {
    return (v0 << 0) | (v1 << 1) | (v2 << 2) | (v3 << 3) | (v4 << 4) | (v5 << 5)
        | (v6 << 6) | (v7 << 7);
  }

  int IndexRotateX(const int index, const int degrees);
  int IndexRotateY(const int index, const int degrees);
  int IndexRotateZ(const int index, const int degrees);
  int ConvertVectorToCorner(const Vector3& v);

 private:
  static MarchingCubes* instance_;
  MCTemplate* uniques_[14];
  MCTemplate* templates_[256];
  Vector3 corners_as_vectors_[8];


  MarchingCubes();

  void GenerateCornersAsVectors();
  void GenerateUniqueTemplates();
  void GenerateTemplates();
};

#endif /* MOCTREE_MARCHINGCUBES_H_ */
