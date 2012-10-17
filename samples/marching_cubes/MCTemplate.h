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

#ifndef MOCTREE_MCTEMPLATE_H_
#define MOCTREE_MCTEMPLATE_H_

#include <Triangle.h>

class MCTemplate {
 public:
  MCTemplate(const int n_triangles, const int index)
      : n_triangles_(n_triangles),
        index_(index) {
    triangles_ = new Triangle[n_triangles];
  }

  virtual ~MCTemplate() {
    delete[] triangles_;
  }

  Triangle* triangles_;
  const int n_triangles_;
  const int index_;  // See (Lorensen, 1987)

  static inline int CornersToIndex(const bool v1, const bool v2, const bool v3,
                            const bool v4, const bool v5, const bool v6,
                            const bool v7, const bool v8) {

    return (v1 << 0) | (v2 << 1) | (v3 << 2) | (v4 << 3) | (v5 << 4) | (v6 << 5)
        | (v7 << 6) | (v8 << 7);
  }
};

#endif /* MOCTREE_MCTEMPLATE_H_ */
