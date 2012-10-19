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

#include <MarchingCubes.h>
#include <Triangle.h>
#include <Vector3.h>

void MarchingCubes::GenerateUniqueTemplates() {
  Triangle tri;
  int tric = 0;
  MCTemplate* t;
  int tc = 0;
  uint8_t index;
  /*
   * Reference is the cube center
   *
   * s Template 1 (Numbers follows (Lorensen,1987))
   */
  tric = 0;
  tc = 0;
  index = CornersToIndex(1, 0, 0, 0, 0, 0, 0, 0);
  t = new MCTemplate(1, index);

  // s tri1
  tri.vertices_[tc].x_ = -0.5f;
  tri.vertices_[tc].y_ = 0.0f;
  tri.vertices_[tc].z_ = 0.5f;
  tc++;

  tri.vertices_[tc].x_ = 0.0f;
  tri.vertices_[tc].y_ = -0.5f;
  tri.vertices_[tc].z_ = 0.5f;
  tc++;

  tri.vertices_[tc].x_ = -0.5f;
  tri.vertices_[tc].y_ = -0.5f;
  tri.vertices_[tc].z_ = 0.0f;
  tc++;

  tri.CalculateNormal();
  t->triangles_[tric++] = tri;
  tc = 0;
  // e tri1

  uniques_[0] = t;
  templates_[index] = t;
  /*
   * e Template 1
   */

  /*
   * s Template 2
   */
  tric = 0;
  tc = 0;
  index = CornersToIndex(1, 1, 0, 0, 0, 0, 0, 0);
  t = new MCTemplate(2, index);

  // s tri1
  tri.vertices_[tc].x_ = -0.5f;
  tri.vertices_[tc].y_ = 0.0f;
  tri.vertices_[tc].z_ = 0.5f;
  tc++;

  tri.vertices_[tc].x_ = 0.5f;
  tri.vertices_[tc].y_ = 0.f;
  tri.vertices_[tc].z_ = 0.5f;
  tc++;

  tri.vertices_[tc].x_ = -0.5f;
  tri.vertices_[tc].y_ = -0.5f;
  tri.vertices_[tc].z_ = 0.0f;
  tc++;

  tri.CalculateNormal();

  t->triangles_[tric++] = tri;
  tc = 0;
  // e tri1

  // s tri2
  tri.vertices_[tc].x_ = 0.5f;
  tri.vertices_[tc].y_ = 0.0f;
  tri.vertices_[tc].z_ = 0.5f;
  tc++;

  tri.vertices_[tc].x_ = 0.5f;
  tri.vertices_[tc].y_ = -0.5f;
  tri.vertices_[tc].z_ = 0.0f;
  tc++;

  tri.vertices_[tc].x_ = -0.5f;
  tri.vertices_[tc].y_ = -0.5f;
  tri.vertices_[tc].z_ = 0.0f;
  tc++;

  tri.CalculateNormal();

  t->triangles_[tric++] = tri;
  tc = 0;
  // e tri2

  uniques_[1] = t;
  templates_[index] = t;
  /*
   * e Template 2
   */

  /*
   * s Template 3
   */
  tric = 0;
  tc = 0;
  index = CornersToIndex(1, 0, 0, 1, 0, 0, 0, 0);
  t = new MCTemplate(2, index);

  // s tri1
  tri.vertices_[tc].x_ = -0.5f;
  tri.vertices_[tc].y_ = 0.0f;
  tri.vertices_[tc].z_ = 0.5f;
  tc++;

  tri.vertices_[tc].x_ = 0.f;
  tri.vertices_[tc].y_ = -0.5f;
  tri.vertices_[tc].z_ = 0.5f;
  tc++;

  tri.vertices_[tc].x_ = -0.5f;
  tri.vertices_[tc].y_ = -0.5f;
  tri.vertices_[tc].z_ = 0.0f;
  tc++;

  tri.CalculateNormal();

  t->triangles_[tric++] = tri;
  tc = 0;
  // e tri1

  // s tri2
  tri.vertices_[tc].x_ = 0.f;
  tri.vertices_[tc].y_ = 0.5f;
  tri.vertices_[tc].z_ = 0.5f;
  tc++;

  tri.vertices_[tc].x_ = 0.5f;
  tri.vertices_[tc].y_ = 0.5f;
  tri.vertices_[tc].z_ = 0.0f;
  tc++;

  tri.vertices_[tc].x_ = 0.5f;
  tri.vertices_[tc].y_ = 0.f;
  tri.vertices_[tc].z_ = 0.5f;
  tc++;

  tri.CalculateNormal();

  t->triangles_[tric++] = tri;
  tc = 0;
  // e tri2

  uniques_[2] = t;
  templates_[index] = t;
  /*
   * e Template 3
   */

  /*
   * s Template 4
   */
  tric = 0;
  tc = 0;
  index = CornersToIndex(1, 0, 0, 0, 0, 0, 0, 1);
  t = new MCTemplate(2, index);

  // s tri1
  tri.vertices_[tc].x_ = -0.5f;
  tri.vertices_[tc].y_ = 0.0f;
  tri.vertices_[tc].z_ = 0.5f;
  tc++;

  tri.vertices_[tc].x_ = 0.f;
  tri.vertices_[tc].y_ = -0.5f;
  tri.vertices_[tc].z_ = 0.5f;
  tc++;

  tri.vertices_[tc].x_ = -0.5f;
  tri.vertices_[tc].y_ = -0.5f;
  tri.vertices_[tc].z_ = 0.0f;
  tc++;

  tri.CalculateNormal();

  t->triangles_[tric++] = tri;
  tc = 0;
  // e tri1

  // s tri2
  tri.vertices_[tc].x_ = 0.f;
  tri.vertices_[tc].y_ = 0.5f;
  tri.vertices_[tc].z_ = -0.5f;
  tc++;

  tri.vertices_[tc].x_ = 0.5f;
  tri.vertices_[tc].y_ = 0.f;
  tri.vertices_[tc].z_ = -0.5f;
  tc++;

  tri.vertices_[tc].x_ = 0.5f;
  tri.vertices_[tc].y_ = 0.5f;
  tri.vertices_[tc].z_ = 0.f;
  tc++;

  tri.CalculateNormal();

  t->triangles_[tric++] = tri;
  tc = 0;
  // e tri2

  uniques_[3] = t;
  templates_[index] = t;
  /*
   * e Template 4
   */

  /*
   * s Template 5
   */
  tric = 0;
  tc = 0;
  index = CornersToIndex(0, 1, 0, 0, 1, 1, 0, 0);
  t = new MCTemplate(3, index);

  // s tri1
  tri.vertices_[tc].x_ = 0.f;
  tri.vertices_[tc].y_ = -0.5f;
  tri.vertices_[tc].z_ = 0.5f;
  tc++;

  tri.vertices_[tc].x_ = 0.5f;
  tri.vertices_[tc].y_ = 0.f;
  tri.vertices_[tc].z_ = 0.5f;
  tc++;

  tri.vertices_[tc].x_ = -0.5f;
  tri.vertices_[tc].y_ = -0.5f;
  tri.vertices_[tc].z_ = 0.0f;
  tc++;

  tri.CalculateNormal();

  t->triangles_[tric++] = tri;
  tc = 0;
  // e tri1

  // s tri2
  tri.vertices_[tc].x_ = -0.5f;
  tri.vertices_[tc].y_ = -0.5f;
  tri.vertices_[tc].z_ = 0.0f;
  tc++;

  tri.vertices_[tc].x_ = 0.5f;
  tri.vertices_[tc].y_ = 0.f;
  tri.vertices_[tc].z_ = 0.5f;
  tc++;

  tri.vertices_[tc].x_ = -0.5f;
  tri.vertices_[tc].y_ = 0.f;
  tri.vertices_[tc].z_ = -0.5f;
  tc++;

  tri.CalculateNormal();

  t->triangles_[tric++] = tri;
  tc = 0;
  // e tri2

  // s tri3
  tri.vertices_[tc].x_ = -0.5f;
  tri.vertices_[tc].y_ = 0.f;
  tri.vertices_[tc].z_ = -0.5f;
  tc++;

  tri.vertices_[tc].x_ = 0.5f;
  tri.vertices_[tc].y_ = 0.f;
  tri.vertices_[tc].z_ = 0.5f;
  tc++;

  tri.vertices_[tc].x_ = 0.5f;
  tri.vertices_[tc].y_ = 0.f;
  tri.vertices_[tc].z_ = -0.5f;
  tc++;

  tri.CalculateNormal();

  t->triangles_[tric++] = tri;
  tc = 0;
  // e tri3

  uniques_[4] = t;
  templates_[index] = t;
  /*
   * e Template 5
   */

  /*
   * s Template 6
   */
  tric = 0;
  tc = 0;
  index = CornersToIndex(1, 1, 0, 0, 0, 0, 0, 1);
  t = new MCTemplate(3, index);

  // s tri1
  tri.vertices_[tc].x_ = -0.5f;
  tri.vertices_[tc].y_ = 0.0f;
  tri.vertices_[tc].z_ = 0.5f;
  tc++;

  tri.vertices_[tc].x_ = 0.5f;
  tri.vertices_[tc].y_ = 0.f;
  tri.vertices_[tc].z_ = 0.5f;
  tc++;

  tri.vertices_[tc].x_ = -0.5f;
  tri.vertices_[tc].y_ = -0.5f;
  tri.vertices_[tc].z_ = 0.0f;
  tc++;

  tri.CalculateNormal();

  t->triangles_[tric++] = tri;
  tc = 0;
  // e tri1

  // s tri2
  tri.vertices_[tc].x_ = 0.5f;
  tri.vertices_[tc].y_ = 0.0f;
  tri.vertices_[tc].z_ = 0.5f;
  tc++;

  tri.vertices_[tc].x_ = 0.5f;
  tri.vertices_[tc].y_ = -0.5f;
  tri.vertices_[tc].z_ = 0.0f;
  tc++;

  tri.vertices_[tc].x_ = -0.5f;
  tri.vertices_[tc].y_ = -0.5f;
  tri.vertices_[tc].z_ = 0.0f;
  tc++;

  tri.CalculateNormal();

  t->triangles_[tric++] = tri;
  tc = 0;
  // e tri2

  // s tri3
  tri.vertices_[tc].x_ = 0.f;
  tri.vertices_[tc].y_ = 0.5f;
  tri.vertices_[tc].z_ = -0.5f;
  tc++;

  tri.vertices_[tc].x_ = 0.5f;
  tri.vertices_[tc].y_ = 0.f;
  tri.vertices_[tc].z_ = -0.5f;
  tc++;

  tri.vertices_[tc].x_ = 0.5f;
  tri.vertices_[tc].y_ = 0.5f;
  tri.vertices_[tc].z_ = 0.f;
  tc++;

  tri.CalculateNormal();

  t->triangles_[tric++] = tri;
  tc = 0;
  // e tri3

  uniques_[5] = t;
  templates_[index] = t;
  /*
   * e Template 6
   */

  /*
   * s Template 7
   */
  tric = 0;
  tc = 0;
  index = CornersToIndex(0, 1, 1, 0, 0, 0, 0, 1);
  t = new MCTemplate(3, index);

  // s tri1
  tri.vertices_[tc].x_ = 0.f;
  tri.vertices_[tc].y_ = -0.5f;
  tri.vertices_[tc].z_ = 0.5f;
  tc++;

  tri.vertices_[tc].x_ = 0.5f;
  tri.vertices_[tc].y_ = 0.f;
  tri.vertices_[tc].z_ = 0.5f;
  tc++;

  tri.vertices_[tc].x_ = 0.5f;
  tri.vertices_[tc].y_ = 0.f;
  tri.vertices_[tc].z_ = 0.0f;
  tc++;

  tri.CalculateNormal();

  t->triangles_[tric++] = tri;
  tc = 0;
  // e tri1

  // s tri2
  tri.vertices_[tc].x_ = 0.f;
  tri.vertices_[tc].y_ = 0.5f;
  tri.vertices_[tc].z_ = 0.5f;
  tc++;

  tri.vertices_[tc].x_ = -0.5f;
  tri.vertices_[tc].y_ = 0.f;
  tri.vertices_[tc].z_ = 0.5f;
  tc++;

  tri.vertices_[tc].x_ = -0.5f;
  tri.vertices_[tc].y_ = 0.5f;
  tri.vertices_[tc].z_ = 0.0f;
  tc++;

  tri.CalculateNormal();

  t->triangles_[tric++] = tri;
  tc = 0;
  // e tri2

  // s tri3
  tri.vertices_[tc].x_ = 0.f;
  tri.vertices_[tc].y_ = 0.5f;
  tri.vertices_[tc].z_ = -0.5f;
  tc++;

  tri.vertices_[tc].x_ = 0.5f;
  tri.vertices_[tc].y_ = 0.f;
  tri.vertices_[tc].z_ = -0.5f;
  tc++;

  tri.vertices_[tc].x_ = 0.5f;
  tri.vertices_[tc].y_ = 0.5f;
  tri.vertices_[tc].z_ = 0.f;
  tc++;

  tri.CalculateNormal();

  t->triangles_[tric++] = tri;
  tc = 0;
  // e tri3

  uniques_[6] = t;
  templates_[index] = t;
  /*
   * e Template 7
   */

  /*
   * s Template 8
   */
  tric = 0;
  tc = 0;
  index = CornersToIndex(1, 1, 1, 1, 0, 0, 0, 0);
  t = new MCTemplate(2, index);

  // s tri1
  tri.vertices_[tc].x_ = -0.5f;
  tri.vertices_[tc].y_ = 0.0f;
  tri.vertices_[tc].z_ = 0.5f;
  tc++;

  tri.vertices_[tc].x_ = 0.5f;
  tri.vertices_[tc].y_ = 0.f;
  tri.vertices_[tc].z_ = -0.5f;
  tc++;

  tri.vertices_[tc].x_ = -0.5f;
  tri.vertices_[tc].y_ = 0.f;
  tri.vertices_[tc].z_ = -0.5f;
  tc++;

  tri.CalculateNormal();

  t->triangles_[tric++] = tri;
  tc = 0;
  // e tri1

  // s tri2
  tri.vertices_[tc].x_ = 0.5f;
  tri.vertices_[tc].y_ = 0.0f;
  tri.vertices_[tc].z_ = 0.5f;
  tc++;

  tri.vertices_[tc].x_ = 0.5f;
  tri.vertices_[tc].y_ = 0.f;
  tri.vertices_[tc].z_ = -0.5f;
  tc++;

  tri.vertices_[tc].x_ = -0.5f;
  tri.vertices_[tc].y_ = 0.f;
  tri.vertices_[tc].z_ = 0.5f;
  tc++;

  tri.CalculateNormal();

  t->triangles_[tric++] = tri;
  tc = 0;
  // e tri2

  uniques_[7] = t;
  templates_[index] = t;
  /*
   * e Template 8
   */

  /*
   * s Template 9
   */
  tric = 0;
  tc = 0;
  index = CornersToIndex(1, 0, 0, 0, 1, 1, 1, 0);
  t = new MCTemplate(4, index);

  // s tri1
  tri.vertices_[tc].x_ = -0.5f;
  tri.vertices_[tc].y_ = 0.5f;
  tri.vertices_[tc].z_ = 0.f;
  tc++;

  tri.vertices_[tc].x_ = -0.5f;
  tri.vertices_[tc].y_ = 0.f;
  tri.vertices_[tc].z_ = 0.5f;
  tc++;

  tri.vertices_[tc].x_ = 0.f;
  tri.vertices_[tc].y_ = 0.5f;
  tri.vertices_[tc].z_ = -0.5f;
  tc++;

  tri.CalculateNormal();

  t->triangles_[tric++] = tri;
  tc = 0;
  // e tri1

  // s tri2
  tri.vertices_[tc].x_ = -0.5f;
  tri.vertices_[tc].y_ = 0.f;
  tri.vertices_[tc].z_ = 0.5f;
  tc++;

  tri.vertices_[tc].x_ = 0.f;
  tri.vertices_[tc].y_ = -0.5f;
  tri.vertices_[tc].z_ = 0.5f;
  tc++;

  tri.vertices_[tc].x_ = 0.f;
  tri.vertices_[tc].y_ = 0.5f;
  tri.vertices_[tc].z_ = -0.5f;
  tc++;

  tri.CalculateNormal();

  t->triangles_[tric++] = tri;
  tc = 0;
  // e tri2

  // s tri3
  tri.vertices_[tc].x_ = 0.f;
  tri.vertices_[tc].y_ = 0.5f;
  tri.vertices_[tc].z_ = -0.5f;
  tc++;

  tri.vertices_[tc].x_ = 0.f;
  tri.vertices_[tc].y_ = -0.5f;
  tri.vertices_[tc].z_ = 0.5f;
  tc++;

  tri.vertices_[tc].x_ = 0.5f;
  tri.vertices_[tc].y_ = 0.f;
  tri.vertices_[tc].z_ = -0.5f;
  tc++;

  tri.CalculateNormal();

  t->triangles_[tric++] = tri;
  tc = 0;
  // e tri3

  // s tri4
  tri.vertices_[tc].x_ = 0.f;
  tri.vertices_[tc].y_ = -0.5f;
  tri.vertices_[tc].z_ = 0.5f;
  tc++;

  tri.vertices_[tc].x_ = 0.5f;
  tri.vertices_[tc].y_ = -0.5f;
  tri.vertices_[tc].z_ = 0.f;
  tc++;

  tri.vertices_[tc].x_ = 0.5f;
  tri.vertices_[tc].y_ = 0.f;
  tri.vertices_[tc].z_ = -0.5f;
  tc++;

  tri.CalculateNormal();

  t->triangles_[tric++] = tri;
  tc = 0;
  // e tri4

  uniques_[8] = t;
  templates_[index] = t;
  /*
   * e Template 9
   */

  /*
   * s Template 10
   */
  tric = 0;
  tc = 0;
  index = CornersToIndex(1, 0, 1, 0, 0, 1, 0, 1);
  t = new MCTemplate(4, index);

  // s tri1
  tri.vertices_[tc].x_ = -0.5f;
  tri.vertices_[tc].y_ = 0.5f;
  tri.vertices_[tc].z_ = 0.f;
  tc++;

  tri.vertices_[tc].x_ = 0.f;
  tri.vertices_[tc].y_ = 0.5f;
  tri.vertices_[tc].z_ = 0.5f;
  tc++;

  tri.vertices_[tc].x_ = -0.5f;
  tri.vertices_[tc].y_ = -0.5f;
  tri.vertices_[tc].z_ = 0.f;
  tc++;

  tri.CalculateNormal();

  t->triangles_[tric++] = tri;
  tc = 0;
  // e tri1

  // s tri2
  tri.vertices_[tc].x_ = 0.f;
  tri.vertices_[tc].y_ = 0.5f;
  tri.vertices_[tc].z_ = 0.5f;
  tc++;

  tri.vertices_[tc].x_ = 0.f;
  tri.vertices_[tc].y_ = -0.5f;
  tri.vertices_[tc].z_ = 0.5f;
  tc++;

  tri.vertices_[tc].x_ = -0.5f;
  tri.vertices_[tc].y_ = -0.5f;
  tri.vertices_[tc].z_ = 0.f;
  tc++;

  tri.CalculateNormal();

  t->triangles_[tric++] = tri;
  tc = 0;
  // e tri2

  // s tri3
  tri.vertices_[tc].x_ = 0.f;
  tri.vertices_[tc].y_ = 0.5f;
  tri.vertices_[tc].z_ = -0.5f;
  tc++;

  tri.vertices_[tc].x_ = 0.f;
  tri.vertices_[tc].y_ = -0.5f;
  tri.vertices_[tc].z_ = -0.5f;
  tc++;

  tri.vertices_[tc].x_ = 0.5f;
  tri.vertices_[tc].y_ = 0.5f;
  tri.vertices_[tc].z_ = 0.f;
  tc++;

  tri.CalculateNormal();

  t->triangles_[tric++] = tri;
  tc = 0;
  // e tri3

  // s tri4
  tri.vertices_[tc].x_ = 0.5f;
  tri.vertices_[tc].y_ = 0.5f;
  tri.vertices_[tc].z_ = 0.f;
  tc++;

  tri.vertices_[tc].x_ = 0.f;
  tri.vertices_[tc].y_ = -0.5f;
  tri.vertices_[tc].z_ = -0.5f;
  tc++;

  tri.vertices_[tc].x_ = 0.5f;
  tri.vertices_[tc].y_ = -0.5f;
  tri.vertices_[tc].z_ = 0.f;
  tc++;

  tri.CalculateNormal();

  t->triangles_[tric++] = tri;
  tc = 0;
  // e tri4

  uniques_[9] = t;
  templates_[index] = t;
  /*
   * e Template 10
   */

  /*
   * s Template 11
   */
  tric = 0;
  tc = 0;
  index = CornersToIndex(1, 0, 0, 0, 1, 1, 0, 1);
  t = new MCTemplate(4, index);

  // s tri1
  tri.vertices_[tc].x_ = -0.5f;
  tri.vertices_[tc].y_ = 0.f;
  tri.vertices_[tc].z_ = 0.5f;
  tc++;

  tri.vertices_[tc].x_ = 0.f;
  tri.vertices_[tc].y_ = -0.5f;
  tri.vertices_[tc].z_ = 0.5f;
  tc++;

  tri.vertices_[tc].x_ = -0.5f;
  tri.vertices_[tc].y_ = 0.f;
  tri.vertices_[tc].z_ = -0.5f;
  tc++;

  tri.CalculateNormal();

  t->triangles_[tric++] = tri;
  tc = 0;
  // e tri1

  // s tri2
  tri.vertices_[tc].x_ = -0.5f;
  tri.vertices_[tc].y_ = 0.f;
  tri.vertices_[tc].z_ = -0.5f;
  tc++;

  tri.vertices_[tc].x_ = 0.f;
  tri.vertices_[tc].y_ = -0.5f;
  tri.vertices_[tc].z_ = 0.5f;
  tc++;

  tri.vertices_[tc].x_ = 0.5f;
  tri.vertices_[tc].y_ = 0.5f;
  tri.vertices_[tc].z_ = 0.f;
  tc++;

  tri.CalculateNormal();

  t->triangles_[tric++] = tri;
  tc = 0;
  // e tri2

  // s tri3
  tri.vertices_[tc].x_ = -0.5f;
  tri.vertices_[tc].y_ = 0.f;
  tri.vertices_[tc].z_ = -0.5f;
  tc++;

  tri.vertices_[tc].x_ = 0.5f;
  tri.vertices_[tc].y_ = 0.5f;
  tri.vertices_[tc].z_ = 0.f;
  tc++;

  tri.vertices_[tc].x_ = 0.f;
  tri.vertices_[tc].y_ = 0.5f;
  tri.vertices_[tc].z_ = -0.5f;
  tc++;

  tri.CalculateNormal();

  t->triangles_[tric++] = tri;
  tc = 0;
  // e tri3

  // s tri4
  tri.vertices_[tc].x_ = 0.5f;
  tri.vertices_[tc].y_ = 0.5f;
  tri.vertices_[tc].z_ = 0.f;
  tc++;

  tri.vertices_[tc].x_ = 0.f;
  tri.vertices_[tc].y_ = -0.5f;
  tri.vertices_[tc].z_ = 0.5f;
  tc++;

  tri.vertices_[tc].x_ = 0.5f;
  tri.vertices_[tc].y_ = -0.5f;
  tri.vertices_[tc].z_ = 0.f;
  tc++;

  tri.CalculateNormal();

  t->triangles_[tric++] = tri;
  tc = 0;
  // e tri4

  uniques_[10] = t;
  templates_[index] = t;
  /*
   * e Template 11
   */

  /*
   * s Template 12
   */
  tric = 0;
  tc = 0;
  index = CornersToIndex(0, 1, 1, 0, 1, 1, 0, 0);
  t = new MCTemplate(4, index);

  // s tri1
  tri.vertices_[tc].x_ = 0.f;
  tri.vertices_[tc].y_ = -0.5f;
  tri.vertices_[tc].z_ = 0.5f;
  tc++;

  tri.vertices_[tc].x_ = 0.5f;
  tri.vertices_[tc].y_ = 0.f;
  tri.vertices_[tc].z_ = 0.5f;
  tc++;

  tri.vertices_[tc].x_ = -0.5f;
  tri.vertices_[tc].y_ = -0.5f;
  tri.vertices_[tc].z_ = 0.f;
  tc++;

  tri.CalculateNormal();

  t->triangles_[tric++] = tri;
  tc = 0;
  // e tri1

  // s tri2
  tri.vertices_[tc].x_ = -0.5f;
  tri.vertices_[tc].y_ = -0.5f;
  tri.vertices_[tc].z_ = 0.f;
  tc++;

  tri.vertices_[tc].x_ = 0.5f;
  tri.vertices_[tc].y_ = 0.f;
  tri.vertices_[tc].z_ = 0.5f;
  tc++;

  tri.vertices_[tc].x_ = -0.5f;
  tri.vertices_[tc].y_ = 0.f;
  tri.vertices_[tc].z_ = -0.5f;
  tc++;

  tri.CalculateNormal();

  t->triangles_[tric++] = tri;
  tc = 0;
  // e tri2

  // s tri3
  tri.vertices_[tc].x_ = -0.5f;
  tri.vertices_[tc].y_ = 0.f;
  tri.vertices_[tc].z_ = -0.5f;
  tc++;

  tri.vertices_[tc].x_ = 0.5f;
  tri.vertices_[tc].y_ = 0.f;
  tri.vertices_[tc].z_ = 0.5f;
  tc++;

  tri.vertices_[tc].x_ = 0.5f;
  tri.vertices_[tc].y_ = 0.f;
  tri.vertices_[tc].z_ = -0.5f;
  tc++;

  tri.CalculateNormal();

  t->triangles_[tric++] = tri;
  tc = 0;
  // e tri3

  // s tri4
  tri.vertices_[tc].x_ = 0.f;
  tri.vertices_[tc].y_ = 0.5f;
  tri.vertices_[tc].z_ = 0.5f;
  tc++;

  tri.vertices_[tc].x_ = -0.5f;
  tri.vertices_[tc].y_ = 0.f;
  tri.vertices_[tc].z_ = 0.5f;
  tc++;

  tri.vertices_[tc].x_ = -0.5f;
  tri.vertices_[tc].y_ = 0.5f;
  tri.vertices_[tc].z_ = 0.f;
  tc++;

  tri.CalculateNormal();

  t->triangles_[tric++] = tri;
  tc = 0;
  // e tri4

  uniques_[11] = t;
  templates_[index] = t;
  /*
   * e Template 12
   */

  /*
   * s Template 13
   */
  tric = 0;
  tc = 0;
  index = CornersToIndex(1, 0, 0, 1, 0, 1, 1, 0);
  t = new MCTemplate(4, index);

  // s tri1
  tri.vertices_[tc].x_ = -0.5f;
  tri.vertices_[tc].y_ = 0.5f;
  tri.vertices_[tc].z_ = 0.f;
  tc++;

  tri.vertices_[tc].x_ = -0.5f;
  tri.vertices_[tc].y_ = 0.f;
  tri.vertices_[tc].z_ = -0.5f;
  tc++;

  tri.vertices_[tc].x_ = 0.f;
  tri.vertices_[tc].y_ = 0.5f;
  tri.vertices_[tc].z_ = -0.5f;
  tc++;

  tri.CalculateNormal();

  t->triangles_[tric++] = tri;
  tc = 0;
  // e tri1

  // s tri2
  tri.vertices_[tc].x_ = 0.f;
  tri.vertices_[tc].y_ = 0.5f;
  tri.vertices_[tc].z_ = 0.5f;
  tc++;

  tri.vertices_[tc].x_ = 0.5f;
  tri.vertices_[tc].y_ = 0.5f;
  tri.vertices_[tc].z_ = 0.f;
  tc++;

  tri.vertices_[tc].x_ = 0.5f;
  tri.vertices_[tc].y_ = 0.f;
  tri.vertices_[tc].z_ = 0.5f;
  tc++;

  tri.CalculateNormal();

  t->triangles_[tric++] = tri;
  tc = 0;
  // e tri2

  // s tri3
  tri.vertices_[tc].x_ = 0.5f;
  tri.vertices_[tc].y_ = 0.f;
  tri.vertices_[tc].z_ = -0.5f;
  tc++;

  tri.vertices_[tc].x_ = 0.f;
  tri.vertices_[tc].y_ = -0.5f;
  tri.vertices_[tc].z_ = -0.5f;
  tc++;

  tri.vertices_[tc].x_ = 0.5f;
  tri.vertices_[tc].y_ = -0.5f;
  tri.vertices_[tc].z_ = 0.f;
  tc++;

  tri.CalculateNormal();

  t->triangles_[tric++] = tri;
  tc = 0;
  // e tri3

  // s tri4
  tri.vertices_[tc].x_ = -0.5f;
  tri.vertices_[tc].y_ = 0.f;
  tri.vertices_[tc].z_ = 0.5f;
  tc++;

  tri.vertices_[tc].x_ = 0.f;
  tri.vertices_[tc].y_ = -0.5f;
  tri.vertices_[tc].z_ = 0.5f;
  tc++;

  tri.vertices_[tc].x_ = -0.5f;
  tri.vertices_[tc].y_ = -0.5f;
  tri.vertices_[tc].z_ = 0.f;
  tc++;

  tri.CalculateNormal();

  t->triangles_[tric++] = tri;
  tc = 0;
  // e tri4

  uniques_[12] = t;
  templates_[index] = t;
  /*
   * e Template 13
   */

  /*
   * s Template 14
   */
  tric = 0;
  tc = 0;
  index = CornersToIndex(0, 1, 0, 0, 1, 1, 1, 0);
  t = new MCTemplate(4, index);

  // s tri1
  tri.vertices_[tc].x_ = 0.f;
  tri.vertices_[tc].y_ = -0.5f;
  tri.vertices_[tc].z_ = 0.5f;
  tc++;

  tri.vertices_[tc].x_ = -0.5f;
  tri.vertices_[tc].y_ = 0.5f;
  tri.vertices_[tc].z_ = 0.f;
  tc++;

  tri.vertices_[tc].x_ = -0.5f;
  tri.vertices_[tc].y_ = -0.5f;
  tri.vertices_[tc].z_ = 0.f;
  tc++;

  tri.CalculateNormal();

  t->triangles_[tric++] = tri;
  tc = 0;
  // e tri1

  // s tri2
  tri.vertices_[tc].x_ = -0.5f;
  tri.vertices_[tc].y_ = 0.5f;
  tri.vertices_[tc].z_ = 0.f;
  tc++;

  tri.vertices_[tc].x_ = 0.f;
  tri.vertices_[tc].y_ = -0.5f;
  tri.vertices_[tc].z_ = 0.5f;
  tc++;

  tri.vertices_[tc].x_ = 0.5f;
  tri.vertices_[tc].y_ = 0.f;
  tri.vertices_[tc].z_ = -0.5f;
  tc++;

  tri.CalculateNormal();

  t->triangles_[tric++] = tri;
  tc = 0;
  // e tri2

  // s tri3
  tri.vertices_[tc].x_ = 0.f;
  tri.vertices_[tc].y_ = 0.5f;
  tri.vertices_[tc].z_ = -0.5f;
  tc++;

  tri.vertices_[tc].x_ = -0.5f;
  tri.vertices_[tc].y_ = 0.5f;
  tri.vertices_[tc].z_ = 0.f;
  tc++;

  tri.vertices_[tc].x_ = 0.5f;
  tri.vertices_[tc].y_ = 0.f;
  tri.vertices_[tc].z_ = -0.5f;
  tc++;

  tri.CalculateNormal();

  t->triangles_[tric++] = tri;
  tc = 0;
  // e tri3

  // s tri4
  tri.vertices_[tc].x_ = 0.5f;
  tri.vertices_[tc].y_ = 0.f;
  tri.vertices_[tc].z_ = -0.5f;
  tc++;

  tri.vertices_[tc].x_ = 0.f;
  tri.vertices_[tc].y_ = -0.5f;
  tri.vertices_[tc].z_ = 0.5f;
  tc++;

  tri.vertices_[tc].x_ = 0.5f;
  tri.vertices_[tc].y_ = 0.f;
  tri.vertices_[tc].z_ = 0.5f;
  tc++;

  tri.CalculateNormal();

  t->triangles_[tric++] = tri;
  tc = 0;
  // e tri4

  uniques_[13] = t;
  templates_[index] = t;
  /*
   * e Template 14
   */

}
