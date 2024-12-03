#pragma once

#include <array>
#include <vector>
#include <iostream>
#include <stdexcept>

template <typename ValueType>
class Image {
  public:
    Image (int xdim, int ydim) :
      m_dim { xdim, ydim }, m_data (xdim*ydim, 0) { }

    Image (int xdim, int ydim, const std::vector<ValueType>& data) :
      m_dim {xdim, ydim }, m_data (data) {
        if (static_cast<int> (m_data.size()) != m_dim[0] * m_dim[1])
          throw std::runtime_error ("dimensions mismatch between image sizes and data vector");
      }

    int width () const { return m_dim[0]; }
    int height () const { return m_dim[1]; }

    const ValueType& operator() (int x, int y) const { return m_data[x + m_dim[0]*y]; }
    ValueType& operator() (int x, int y) { return m_data[x + m_dim[0]*y]; }

  private:
    std::array<int,2> m_dim;
    std::vector<ValueType> m_data;
};



template <class ValueType>
inline std::ostream& operator<< (std::ostream& out, const Image<ValueType>& im)
{
  out << "Image of size " << im.width() << "x" << im.height();
  return out;
}

