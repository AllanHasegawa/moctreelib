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

#include "CameraPosition.h"

CameraPosition::CameraPosition() {
  // TODO Auto-generated constructor stub

}

CameraPosition::~CameraPosition() {
  // TODO Auto-generated destructor stub
}

void CameraPosition::Update(const double& delta_time) {
  position_.x_ += moving_.x_ * movement_speed_.x_ * delta_time;
  position_.y_ += moving_.y_ * movement_speed_.y_ * delta_time;
  position_.z_ += moving_.z_ * movement_speed_.z_ * delta_time;
}

void CameraPosition::Reset() {
  position_ = Vector3();
  moving_ = Vector3();
  angle_ = Vector3();
}

const Vector3 CameraPosition::angle() {
  return angle_;
}
const Vector3 CameraPosition::position() {
  return position_;
}

void CameraPosition::SetXMovement(Movement movement) {
  moving_.x_ = movement;
}

void CameraPosition::SetYMovement(Movement movement) {
  moving_.y_ = movement;
}

void CameraPosition::SetZMovement(Movement movement) {
  moving_.z_ = movement;
}

void CameraPosition::SetMovementSpeed(const double x, const double y, const double z) {
  movement_speed_.x_ = x;
  movement_speed_.y_ = y;
  movement_speed_.z_ = z;
}
