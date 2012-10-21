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

#ifndef MOCTREE_CAMERA_H_
#define MOCTREE_CAMERA_H_

#include <Vector3.h>

enum Movement {
  FORWARD = 1,
  NONE = 0,
  BACKWARD = -1
};

class Camera {
 public:
  Camera();
  virtual ~Camera();

  void Update(const double& delta_time);
  void Render();
  void Reset();

  const Vector3 angle();
  const Vector3 position();

  void SetXMovement(Movement movement);
  void SetYMovement(Movement movement);
  void SetZMovement(Movement movement);
  void SetMovementSpeed(const double x, const double y, const double z);

  void SetAngleDisplacement(const double x, const double y, const double z);
  void SetAngleSensitivity(const double x, const double y, const double z);

 private:
  Vector3 angle_;
  Vector3 position_;
  Vector3 moving_;
  Vector3 movement_speed_;
  Vector3 angle_sensitivity_;
  Vector3 heading_;

  const double kDegreeToRadians_;
};

#endif /* MOCTREE_CAMERA_H_ */
