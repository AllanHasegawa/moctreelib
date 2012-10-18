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
  GenerateCornersAsVectors();
  GenerateUniqueTemplates();
  GenerateTemplates();
}

MarchingCubes::~MarchingCubes() {
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
  for (int z = 0; z < 2; z++) {
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

void MarchingCubes::GenerateUniqueTemplates() {
  Triangle tri1, tri2, tri3, tri4, tri5, tri6;
  int index;
  /*
   * s Template 1
   */
  index = CornersToIndex(1, 0, 0, 0, 0, 0, 0, 0);
  MCTemplate* t = new MCTemplate(1, index);

  // s tri1
  tri1.vertices_[0].x_ = 0.5f;
  tri1.vertices_[0].y_ = 0.0f;
  tri1.vertices_[0].z_ = 0.0f;

  tri1.vertices_[1].x_ = 0.0f;
  tri1.vertices_[1].y_ = 0.0f;
  tri1.vertices_[1].z_ = -0.5f;

  tri1.vertices_[2].x_ = 0.0f;
  tri1.vertices_[2].y_ = 0.5f;
  tri1.vertices_[2].z_ = 0.0f;
  tri1.CalculateNormal();
  t->triangles_[0] = tri1;

  uniques_[index] = t;
  templates_[index] = t;
  // e tri1
  /*
   * e Template 1
   */
}

void MarchingCubes::GenerateTemplates() {
  //http://www.euclideanspace.com/maths/geometry/rotations/euler/examples/index.htm
  const int n_unique_templates_ = 1;
  for (int i = 0; i < n_unique_templates_; i++) {
    MCTemplate* u_t = uniques_[i];
    for (int rotx = 0; rotx <= 270; rotx += 90) {
      for (int roty = 0; roty <= 270; roty += 90) {
        for (int rotz = 0; rotz <= 270; rotz += 90) {
          int new_index = IndexRotateX(u_t->index_, rotx);

        }
      }
    }
  }
}

int MarchingCubes::IndexRotateX(const int index, const int degrees) {
  if (degrees == 0 || degrees % 360 == 0) {
    return index;
  }

  if (degrees % 90) {
    return -1;
  }

  int new_index = 0;
  for (int i = 0; i < 8; i++) {
    const int single_index = index & (1u << i);
    if (single_index) {
      Vector3 v = corners_as_vectors_[i];
      v.Translate(-0.5f, -0.5f, -0.5f)->RotateX(degrees)->Translate(0.5f, 0.5f,
                                                                    0.5f);
      new_index = new_index | (1u << ConvertVectorToCorner(v));
    }
  }

  return new_index;
}

int MarchingCubes::IndexRotateY(const int index, const int degrees) {
  if (degrees == 0 || degrees % 360 == 0) {
    return index;
  }

  if (degrees % 90) {
    return -1;
  }

  int new_index = 0;
  for (int i = 0; i < 8; i++) {
    const int single_index = index & (1u << i);
    if (single_index) {
      Vector3 v = corners_as_vectors_[i];
      v.Translate(-0.5f, -0.5f, -0.5f)->RotateY(degrees)->Translate(0.5f, 0.5f,
                                                                    0.5f);
      new_index = new_index | (1u << ConvertVectorToCorner(v));
    }
  }

  return new_index;
}

int MarchingCubes::IndexRotateZ(const int index, const int degrees) {
  if (degrees == 0 || degrees % 360 == 0) {
    return index;
  }

  if (degrees % 90) {
    return -1;
  }

  int new_index = 0;
  for (int i = 0; i < 8; i++) {
    const int single_index = index & (1u << i);
    if (single_index) {
      Vector3 v = corners_as_vectors_[i];
      v.Translate(-0.5f, -0.5f, -0.5f)->RotateZ(degrees)->Translate(0.5f, 0.5f,
                                                                    0.5f);
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

  printf("FUUUU: %f, %f, %f\n", v.x_, v.y_, v.z_);
  return -1;
}
