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
  MCTemplate(const int n_triangles, const int index);

  virtual ~MCTemplate();

  Triangle* triangles_;
  int n_triangles_;
  uint8_t index_;  // See (Lorensen, 1987)
  bool complement_;

  void Render();

  void CopyTriangles(const MCTemplate& source);
  MCTemplate* RotateX(const double degrees);
  MCTemplate* RotateY(const double degrees);
  MCTemplate* RotateZ(const double degrees);

  void set_complement(const bool complement);
};

#endif /* MOCTREE_MCTEMPLATE_H_ */
