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

#include <iostream>

template<class T>
class ClassicOctreeCell {
 public:
  ClassicOctreeCell(int x, int y, int z, T& data)
      : x_(x),
        y_(y),
        z_(z),
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

  void CreateChildren() {
    if (children_ == NULL) {
      // Lets create the children array
      children_ = new ClassicOctreeCell<T>*[8];

      // then insert it :3
      int counter = 0;
      for (int z = 0; z < 2; z++) {
        for (int y = 0; y < 2; y++) {
          for (int x = 0; x < 2; x++) {
            children_[counter] = new ClassicOctreeCell<T>(x, y, z);
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

  void set_data(T& data) {
    data_ = data;
  }

  void set_father(ClassicOctreeCell<T>& father) {
    father_ = father;
  }

  int x() {
    return x_;
  }

  int y() {
    return y_;
  }

  int z() {
    return z_;
  }

  T& data() {
    return data_;
  }

 private:
  int x_;int y_;int z_;
  T* data_;
  ClassicOctreeCell** children_;
  ClassicOctreeCell* father_;
};

#endif /* MOCTREE_CLASSICOCTREECELL_H_ */
