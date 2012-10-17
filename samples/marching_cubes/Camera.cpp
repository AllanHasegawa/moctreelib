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

Camera::Camera() {
  camera_position_.SetMovementSpeed(0.1, 0.1, 0.1);
  camera_position_.SetAngleSensitivity(0.1, 0.1, 0.1);
}

Camera::~Camera() {
}

void Camera::Update(const double& delta_time) {
  camera_position_.Update(delta_time);
}

void Camera::Render() {
  GLfloat camera_x_trans = -camera_position_.position().x_;  // Used For Player Translation On The X Axis
  GLfloat camera_z_trans = -camera_position_.position().z_;  // Used For Player Translation On The Z Axis
  GLfloat camera_y_trans = -camera_position_.position().y_;  // Used For Bouncing Motion Up And Down

  GLfloat camera_x_rot = 360.0f - camera_position_.angle().x_;
  GLfloat camera_y_rot = 360.0f - camera_position_.angle().y_;  // 360 Degree Angle For Player Direction

  glLoadIdentity();

  glRotatef(camera_x_rot, 1.0f, 0, 0);  // Rotate Up And Down To Look Up And Down
  glRotatef(camera_y_rot, 0, 1.0f, 0);  // Rotate Depending On Direction Player Is Facing

  glTranslatef(camera_x_trans, camera_y_trans, camera_z_trans);  // Translate The Scene Based On Player
}

