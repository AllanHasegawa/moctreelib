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

#ifndef MOCTREE_MOCTREECELL_H_
#define MOCTREE_MOCTREECELL_H_

#include <stdint.h>

namespace moctree {

template<class T>
class ClassicOctreeVoxel;

template<class T>
class MOctreeCell {
  friend class ClassicOctreeVoxel<T>;
 public:
  MOctreeCell()
      : x_(0),
        y_(0),
        z_(0),
        data_(NULL) {

  }

  virtual ~MOctreeCell() {

  }

  uint32_t x_;
  uint32_t y_;
  uint32_t z_;
  T* data_;

 private:
  ClassicOctreeVoxel<T>* classic_octree_voxel_;
};

}  // namespace moctree

#endif /* MOCTREE_MOCTREECELL_H_ */
