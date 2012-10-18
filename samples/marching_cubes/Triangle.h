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

#ifndef MOCTREE_TRIANGLE_H_
#define MOCTREE_TRIANGLE_H_

#include <wx/glcanvas.h>

#include <Vector3.h>

class Triangle {
 public:
  Vector3 vertices_[3];
  Vector3 normal_;

  /* Triangle = p1, p2, p3
   *
   * so:
   *
   * U = p2 - p1
   * V = p3 - p1
   *
   * Normal = N = U (CrossProduct) V
   *
   */
  void CalculateNormal() {
    Vector3 u = vertices_[1].Subtract(vertices_[0]);
    Vector3 v = vertices_[2].Subtract(vertices_[0]);
    normal_ = u.CrossProduct(v);
  }

  void Render() {
    glBegin(GL_POLYGON);
    glNormal3f(normal_.x_, normal_.y_, normal_.z_);
    glColor3f(1, 0, 0);
    glVertex3f(vertices_[0].x_, vertices_[0].y_, vertices_[0].z_);
    glColor3f(0, 1, 0);
    glVertex3f(vertices_[1].x_, vertices_[1].y_, vertices_[1].z_);
    glColor3f(0, 0, 1);
    glVertex3f(vertices_[2].x_, vertices_[2].y_, vertices_[2].z_);
    glEnd();
  }
};

#endif /* MOCTREE_TRIANGLE_H_ */
