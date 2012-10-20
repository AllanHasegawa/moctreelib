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

#ifndef MOCTREE_MOCTREE_H_
#define MOCTREE_MOCTREE_H_

#include <stdint.h>
#include <string>
#include <moctree/MOctreeCell.h>

namespace moctree {

template<class T>
class MOctree {
 public:
  virtual ~MOctree() {
  }

  virtual void InsertCell(const uint32_t x, const uint32_t y, const uint32_t z,
                          T* data) = 0;
  virtual void DeleteCell(const uint32_t x, const uint32_t y,
                          const uint32_t z) = 0;
  virtual T* GetData(const uint32_t x, const uint32_t y, const uint32_t z) = 0;

  virtual MOctreeCell<T> GetCell(const uint32_t x, const uint32_t y,
                              const uint32_t z) = 0;
  virtual MOctreeCell<T> GetNeighbor(const MOctreeCell<T>& source, const int32_t x,
                                  const int32_t y, const int32_t z) = 0;
  virtual std::string ToString() = 0;
};

}  // namespace moctree
#endif /* MOCTREE_MOCTREE_H_ */
