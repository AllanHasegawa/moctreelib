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

#ifndef MOCTREE_CLASSICOCTREE_H_
#define MOCTREE_CLASSICOCTREE_H_

#include <iostream>
#include <moctree/MOctree.h>
#include <moctree/classic/ClassicOctreeCell.h>

namespace moctree {

template<class T>
class ClassicOctree : public MOctree<T> {
 public:
  ClassicOctree(const uint32_t size)
      : size_(size) {
    root_ = new ClassicOctreeCell<T>(0, 0, 0, size);
  }
  ~ClassicOctree() {

  }

  void InsertCell(const uint32_t x, const uint32_t y, const uint32_t z,
                  T* data) {
    if (x > size_ || y > size_ || z > size_) {
      return;
    }

    root_->InsertCell(x, y, z, data);
  }

  void DeleteCell(const uint32_t x, const uint32_t y, const uint32_t z) {
    if (x > size_ || y > size_ || z > size_) {
      return;
    }
    root_->DeleteCell(x, y, z);
  }

  T* GetData(const uint32_t x, const uint32_t y, const uint32_t z) {
    if (x > size_ || y > size_ || z > size_) {
      return NULL;
    }
    return root_->GetData(x, y, z);
  }

  std::string ToString() {
    return root_->ToStringRecursive(0, 0);
  }

 private:
  ClassicOctreeCell<T>* root_;
  const uint32_t size_;
};

}  // namespace moctree

#endif /* MOCTREE_CLASSICOCTREE_H_ */
