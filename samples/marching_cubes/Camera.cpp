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

#include "Camera.h"

#include <math.h>
#include <wx/glcanvas.h>


Camera::Camera()
    : kDegreeToRadians_(0.0174532925f) {
  angle_sensitivity_.x_ = 1;
  angle_sensitivity_.y_ = 1;
  angle_sensitivity_.z_ = 1;

  movement_speed_.x_ = 1;
  movement_speed_.y_ = 1;
  movement_speed_.z_ = 1;
}

Camera::~Camera() {
}

void Camera::Update(const double& delta_time) {
  position_.x_ += sin(angle_.y_ * kDegreeToRadians_) * moving_.x_
      * movement_speed_.x_ * delta_time;
  position_.y_ += moving_.y_ * movement_speed_.y_ * delta_time;
  position_.z_ += cos(angle_.y_ * kDegreeToRadians_) * moving_.z_
      * movement_speed_.z_ * delta_time;
}

void Camera::Render() {
  GLfloat camera_x_trans = -position_.x_;  // Used For Player Translation On The X Axis
  GLfloat camera_z_trans = -position_.z_;  // Used For Player Translation On The Z Axis
  GLfloat camera_y_trans = -position_.y_;  // Used For Bouncing Motion Up And Down

  GLfloat camera_x_rot = 360.0f - angle_.x_;
  GLfloat camera_y_rot = 360.0f - angle_.y_;  // 360 Degree Angle For Player Direction

  glLoadIdentity();

  glRotatef(camera_x_rot, 1.0f, 0, 0);  // Rotate Up And Down To Look Up And Down
  glRotatef(camera_y_rot, 0, 1.0f, 0);  // Rotate Depending On Direction Player Is Facing

  glTranslatef(camera_x_trans, camera_y_trans, camera_z_trans);  // Translate The Scene Based On Player
}

void Camera::Reset() {
  position_ = Vector3();
  moving_ = Vector3();
  angle_ = Vector3();
}

const Vector3 Camera::angle() {
  return angle_;
}
const Vector3 Camera::position() {
  return position_;
}

void Camera::SetXMovement(Movement movement) {
  moving_.x_ = movement;
}

void Camera::SetYMovement(Movement movement) {
  moving_.y_ = movement;
}

void Camera::SetZMovement(Movement movement) {
  moving_.z_ = movement;
}

void Camera::SetMovementSpeed(const double x, const double y, const double z) {
  movement_speed_.x_ = x;
  movement_speed_.y_ = y;
  movement_speed_.z_ = z;
}

void Camera::SetAngleDisplacement(const double x, const double y,
                                  const double z) {
  angle_.x_ += x * angle_sensitivity_.x_;
  angle_.y_ += y * angle_sensitivity_.y_;
  angle_.z_ += z * angle_sensitivity_.z_;

  if (angle_.x_ > 89.) {
    angle_.x_ = 89.;
  } else if (angle_.x_ < -89.) {
    angle_.x_ = -89.;
  }
}

void Camera::SetAngleSensitivity(const double x, const double y,
                                 const double z) {
  angle_sensitivity_.x_ = x;
  angle_sensitivity_.y_ = y;
  angle_sensitivity_.z_ = z;
}

