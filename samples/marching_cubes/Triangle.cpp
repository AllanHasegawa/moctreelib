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

#include <Triangle.h>

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
void Triangle::CalculateNormal() {
  Vector3 u = vertices_[1].Subtract(vertices_[0]);
  Vector3 v = vertices_[2].Subtract(vertices_[0]);
  normal_ = v.CrossProduct(u);
}

void Triangle::Render() {
  glBegin(GL_POLYGON);
  glColor3f(1, 0, 0);
  glNormal3f(normal_.x_, normal_.y_, normal_.z_);
  glVertex3f(vertices_[0].x_, vertices_[0].y_, vertices_[0].z_);
  glColor3f(0, 1, 0);
  glNormal3f(normal_.x_, normal_.y_, normal_.z_);
  glVertex3f(vertices_[1].x_, vertices_[1].y_, vertices_[1].z_);
  glColor3f(0, 0, 1);
  //glNormal3f(normal_.x_, normal_.y_, normal_.z_);
  glVertex3f(vertices_[2].x_, vertices_[2].y_, vertices_[2].z_);
  glEnd();
}

Triangle* Triangle::RotateX(const double degrees) {
  for (int i = 0; i < 3; i++) {
    vertices_[i].RotateX(degrees);
  }
  normal_.RotateX(degrees);
  return this;
}

Triangle* Triangle::RotateY(const double degrees) {
  for (int i = 0; i < 3; i++) {
    vertices_[i].RotateY(degrees);
  }
  normal_.RotateY(degrees);
  return this;
}

Triangle* Triangle::RotateZ(const double degrees) {
  for (int i = 0; i < 3; i++) {
    vertices_[i].RotateZ(degrees);
  }
  normal_.RotateZ(degrees);
  return this;
}

Triangle* Triangle::Translate(const double x, const double y, const double z) {
  for (int i = 0; i < 3; i++) {
    vertices_[i].Translate(x, y, z);
  }
  return this;
}

Triangle* Triangle::MirrorX() {
  for (int i = 0; i < 3; i++) {
    vertices_[i].MirrorX();
  }
  normal_.MirrorX();
  return this;
}

Triangle* Triangle::MirrorY() {
  for (int i = 0; i < 3; i++) {
    vertices_[i].MirrorY();
  }
  normal_.MirrorY();
  return this;
}
Triangle* Triangle::MirrorZ() {
  for (int i = 0; i < 3; i++) {
    vertices_[i].MirrorZ();
  }
  normal_.MirrorZ();
  return this;
}
