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

#include "MarchingCubes.h"

#include <iostream>

MarchingCubes* MarchingCubes::instance_ = NULL;

MarchingCubes::MarchingCubes() {

  for (int i = 0; i < 256; i++) {
    templates_[i] = NULL;
  }
  for (int i = 0; i < 14; i++) {
    uniques_[i] = NULL;
  }
  GenerateCornersAsVectors();
  GenerateUniqueTemplates();
  GenerateTemplates();
}

MarchingCubes::~MarchingCubes() {
  for (int i = 0; i < 256; i++) {
    if (templates_[i] != NULL) {
      delete templates_[i];
    }
  }
  delete[] templates_;

  for (int i = 0; i < 14; i++) {
    if (uniques_[i] != NULL) {
      delete uniques_[i];
    }
  }
  delete[] uniques_;
}

MarchingCubes* MarchingCubes::CreateMarchingCubes() {
  if (instance_ == NULL) {
    instance_ = new MarchingCubes();
  }
  return instance_;
}

MCTemplate* MarchingCubes::GetTemplate(const int index) {
  return templates_[index];
}

MCTemplate* MarchingCubes::GetTemplate(const bool v0, const bool v1,
                                       const bool v2, const bool v3,
                                       const bool v4, const bool v5,
                                       const bool v6, const bool v7) {
  return templates_[CornersToIndex(v0, v1, v2, v3, v4, v5, v6, v7)];
}

void MarchingCubes::GenerateCornersAsVectors() {
  int counter = 0;
  for (int z = 0; z > -2; z--) {
    for (int y = 0; y < 2; y++) {
      for (int x = 0; x < 2; x++) {
        corners_as_vectors_[counter].x_ = x;
        corners_as_vectors_[counter].y_ = y;
        corners_as_vectors_[counter].z_ = z;
        counter++;
      }
    }
  }
}

void MarchingCubes::GenerateTemplates() {

  // empty template
  templates_[0] = new MCTemplate(0, 0);

  /*
   * All the cubes rotations at:
   * http://www.euclideanspace.com/maths/geometry/rotations/euler/examples/index.htm
   */
  const int n_unique_templates_ = 13;
  for (int i = 0; i < n_unique_templates_; i++) {
    MCTemplate* u_t = uniques_[i];

    for (int rotx = 0; rotx <= 270; rotx += 90) {
      for (int roty = 0; roty <= 270; roty += 90) {
        // Normal combination
        uint8_t new_index = IndexRotateX(u_t->index_, rotx);
        new_index = IndexRotateY(new_index, roty);
        if (templates_[new_index] == NULL) {
          MCTemplate* t = new MCTemplate(u_t->n_triangles_, new_index);
          t->CopyTriangles(*u_t);
          t->RotateX(rotx)->RotateY(roty);
          templates_[new_index] = t;
        }
        // Complement combination
        new_index = ~new_index;
        if (templates_[new_index] == NULL) {
          MCTemplate* t = new MCTemplate(u_t->n_triangles_, new_index);
          t->CopyTriangles(*u_t);
          t->RotateX(rotx)->RotateY(roty);
          t->set_complement(true);
          templates_[new_index] = t;
        }
      }
    }
    for (int rotz = 90; rotz <= 180; rotz += 90) {  // z only rotates twice
      for (int roty = 0; roty <= 270; roty += 90) {
        uint8_t new_index = IndexRotateZ(u_t->index_, rotz);
        new_index = IndexRotateY(new_index, roty);
        if (templates_[new_index] == NULL) {
          MCTemplate* t = new MCTemplate(u_t->n_triangles_, new_index);
          t->CopyTriangles(*u_t);
          t->RotateZ(rotz)->RotateY(roty);
          templates_[new_index] = t;
        }
        // Complement combination
        new_index = ~new_index;
        if (templates_[new_index] == NULL) {
          MCTemplate* t = new MCTemplate(u_t->n_triangles_, new_index);
          t->CopyTriangles(*u_t);
          t->RotateZ(rotz)->RotateY(roty);
          t->set_complement(true);
          templates_[new_index] = t;
        }
      }
    }
  }
}

uint8_t MarchingCubes::IndexRotateX(const uint8_t index, const int degrees) {
  if (degrees == 0 || degrees % 360 == 0) {
    return index;
  }

  if (degrees % 90) {
    return -1;
  }

  uint8_t new_index = 0;
  for (int i = 0; i < 8; i++) {
    const uint8_t single_index = index & (1u << i);
    if (single_index) {

      Vector3 v = corners_as_vectors_[i];
      v.Translate(-0.5f, -0.5f, 0.5f)->RotateX(degrees)->Translate(0.5f, 0.5f,
                                                                   -0.5f);
      new_index = new_index | (1u << ConvertVectorToCorner(v));
    }
  }

  return new_index;
}

uint8_t MarchingCubes::IndexRotateY(const uint8_t index, const int degrees) {
  if (degrees == 0 || degrees % 360 == 0) {
    return index;
  }

  if (degrees % 90) {
    return -1;
  }

  uint8_t new_index = 0;
  for (int i = 0; i < 8; i++) {
    const uint8_t single_index = index & (1u << i);
    if (single_index) {
      Vector3 v = corners_as_vectors_[i];
      v.Translate(-0.5f, -0.5f, 0.5f)->RotateY(degrees)->Translate(0.5f, 0.5f,
                                                                   -0.5f);
      new_index = new_index | (1u << ConvertVectorToCorner(v));
    }
  }

  return new_index;
}

uint8_t MarchingCubes::IndexRotateZ(const uint8_t index, const int degrees) {
  if (degrees == 0 || degrees % 360 == 0) {
    return index;
  }

  if (degrees % 90) {
    return -1;
  }

  uint8_t new_index = 0;
  for (int i = 0; i < 8; i++) {
    const uint8_t single_index = index & (1u << i);
    if (single_index) {
      Vector3 v = corners_as_vectors_[i];
      v.Translate(-0.5f, -0.5f, 0.5f)->RotateZ(degrees)->Translate(0.5f, 0.5f,
                                                                   -0.5f);
      new_index = new_index | (1u << ConvertVectorToCorner(v));
    }
  }

  return new_index;
}

int MarchingCubes::ConvertVectorToCorner(const Vector3& v) {
  for (int i = 0; i < 8; i++) {
    if ((int) corners_as_vectors_[i].x_ == (int) v.x_
        && (int) corners_as_vectors_[i].y_ == (int) v.y_
        && (int) corners_as_vectors_[i].z_ == (int) v.z_) {
      return i;
    }
  }

  printf("ERROR ConvertVectorToCorner: %f, %f, %f\n", v.x_, v.y_, v.z_);
  return -1;
}
