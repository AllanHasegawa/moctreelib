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

#ifndef MOCTREE_VECTOR3_H_
#define MOCTREE_VECTOR3_H_

#include <string>
#include <sstream>
#include <math.h>
#include <stdio.h>

class Vector3 {
 public:

  double x_;
  double y_;
  double z_;

  Vector3()
      : x_(0),
        y_(0),
        z_(0) {

  }

  virtual ~Vector3() {

  }

  std::string ToString() {
    std::stringstream ss;
    ss << "(" << x_ << "," << y_ << "," << z_ << ")";
    return ss.str();
  }

  Vector3* RotateX(const double degree) {
    const double radians = degree * M_PI / 180.0f;
    const double kC = cos(radians);
    const double kS = sin(radians);
    const double oy = y_;
    y_ = (oy * kC) + (z_ * -kS);
    z_ = (oy * kS) + (z_ * kC);
    return this;
  }

  Vector3* RotateY(const double degree) {
    const double radians = degree * M_PI / 180.0f;
    const double kC = cos(radians);
    const double kS = sin(radians);
    const double ox = x_;
    x_ = (ox * kC) + (z_ * kS);
    z_ = (ox * -kS) + (z_ * kC);
    return this;
  }

  Vector3* RotateZ(const double degree) {
    const double radians = degree * M_PI / 180.0f;
    const double kC = cos(radians);
    const double kS = sin(radians);
    const double ox = x_;
    x_ = (ox * kC) + (y_ * -kS);
    y_ = (ox * kS) + (y_ * kC);
    return this;
  }

  Vector3* Translate(const double x, const double y, const double z) {
    x_ += x;
    y_ += y;
    z_ += z;
    return this;
  }

  Vector3 Subtract(const Vector3& v) {
    Vector3 nv;
    nv.x_ = x_ - v.x_;
    nv.y_ = y_ - v.y_;
    nv.z_ = z_ - v.z_;
    return nv;
  }

  Vector3 Add(const Vector3& v) {
    Vector3 nv;
    nv.x_ = x_ + v.x_;
    nv.y_ = y_ + v.y_;
    nv.z_ = z_ + v.z_;
    return nv;
  }

  Vector3 CrossProduct(const Vector3& v) {
    Vector3 nv;
    nv.x_ = (y_ * v.z_) - (z_ * v.y_);
    nv.y_ = (z_ * v.x_) - (x_ * v.z_);
    nv.z_ = (x_ * v.y_) - (y_ * v.x_);
    return nv;
  }

  Vector3* MirrorX() {
    x_ = -x_;
    return this;
  }

  Vector3* MirrorY() {
    y_ = -y_;
    return this;
  }

  Vector3* MirrorZ() {
    z_ = -z_;
    return this;
  }

};

#endif /* MOCTREE_VECTOR3_H_ */
