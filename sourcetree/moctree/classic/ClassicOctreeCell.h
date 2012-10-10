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

#ifndef MOCTREE_CLASSICOCTREECELL_H_
#define MOCTREE_CLASSICOCTREECELL_H_

#include <stdint.h>
#include <iostream>

namespace moctree {

template<class T>
class ClassicOctreeCell {
 public:
  ClassicOctreeCell(uint32_t x, uint32_t y, uint32_t z, uint32_t size)
      : x_(x),
        y_(y),
        z_(z),
        size_(size),
        data_(NULL),
        children_(NULL),
        father_(NULL) {

  }
  virtual ~ClassicOctreeCell() {
    KillChildren();
  }

  ClassicOctreeCell<T> GetChild(const int N) {
    return children_[N];
  }

  void CreateChildren(ClassicOctreeCell<T>* father) {
    if (children_ == NULL && size_ != 1) {
      const uint32_t size_father = father->size();
      const uint32_t x_father = father->x();
      const uint32_t y_father = father->y();
      const uint32_t z_father = father->z();

      const uint32_t size = size_father / 2;
      const uint32_t mid_size = size / 2;

      // Lets create the children array
      children_ = new ClassicOctreeCell<T>*[8];

      // then insert it :3
      int counter = 0;
      for (int z = 0; z < 2; z++) {
        for (int y = 0; y < 2; y++) {
          for (int x = 0; x < 2; x++) {
            children_[counter] = new ClassicOctreeCell<T>(
                x_father + (x * mid_size), y_father + (y * mid_size),
                z_father + (z * mid_size), size);
            children_[counter]->set_father(father);
            counter++;
          }
        }
      }
    }
  }

  void KillChildren() {
    if (children_ != NULL) {
      // First delete the actual children...
      for (int i = 0; i < 8; i++) {
        delete children_[i];
      }
      // then delete its array :3
      delete[] children_;
      children_ = NULL;
    }
  }

  void InsertCell(const uint32_t x, const uint32_t y, const uint32_t z,
                  T* data) {
    if (size_ == 1) {
      data_ = data;
    } else {
      this->CreateChildren(this);
      this->children_[ConvertXYZToChildNumber(x, y, z)]->InsertCell(x, y, z,
                                                                    data);
    }
  }

  T* GetData(const uint32_t x, const uint32_t y, const uint32_t z) {

    // if there is data BEFORE hitting the bottom of the tree
    if (data_ != NULL) {
      return data_;
    }

    // if is in the actual cell, but no data
    if (size_ == 1) {
      return NULL;
    }

    if (children_ == NULL) {
      return NULL;
    }

    return this->children_[ConvertXYZToChildNumber(x, y, z)]->GetData(x, y, z);
  }

  void set_data(T* data) {
    data_ = data;
  }

  void set_father(ClassicOctreeCell<T>* father) {
    father_ = father;
  }

  uint32_t x() {
    return x_;
  }

  uint32_t y() {
    return y_;
  }

  uint32_t z() {
    return z_;
  }

  uint32_t size() {
    return size_;
  }

  T* data() {
    return data_;
  }

 private:
  uint32_t x_;
  uint32_t y_;
  uint32_t z_;
  uint32_t size_;
  T* data_;
  ClassicOctreeCell<T>** children_;
  ClassicOctreeCell<T>* father_;

  inline int ConvertXYZToChildNumber(const uint32_t x, const uint32_t y,
                                     const uint32_t z) {
    const uint32_t size = size_;
    const uint32_t mid_size = size_ / 2;

    const int bx = x >= mid_size;
    const int by = y >= mid_size;
    const int bz = z >= mid_size;

    int child = 0;
    child += bx;
    child += (by << 1);
    child += (bz << 2);

    return child;
  }
};

}  // namespace moctree

#endif /* MOCTREE_CLASSICOCTREECELL_H_ */
