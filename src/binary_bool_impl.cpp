#include "binary.h"

namespace binaryStream{
  unsigned char buffer::buffer_in = 0;
  std::size_t buffer::filled_in = 0;
  unsigned char buffer::buffer_out = 0;
  std::size_t buffer::filled_out = 0;


  void buffer::cleanBufferIn() {
    buffer_in = 0;
    filled_in = 0;
  }

  void buffer::cleanBufferOut() {
    buffer_out = 0;
    filled_out = 0;
  }

  bool buffer::BufferInIsEmpty() {
    return filled_in == 0;
  }

  bool buffer::BufferOutIsEmpty() {
    return filled_out == 0;
  }

  void buffer::dropBufferOut(std::ostream &os) {
    os << binary<unsigned char>(buffer_out);
    cleanBufferOut();
  }

  std::istream &operator>>(std::istream &is, const binary<bool> &x) {
    if (buffer::BufferInIsEmpty()) {
      is >> binary<unsigned char>(buffer::buffer_in);
      buffer::filled_in = CHAR_BIT;
    }
    *const_cast<bool *>(&x.data) = (buffer::buffer_in & 1u);
    buffer::buffer_in >>= 1u;
    buffer::filled_in--;
    return is;
  }

  std::ostream &operator<<(std::ostream &os, const binary<bool> &x) {
    buffer::buffer_out += ((x.data ? 1u : 0u) << buffer::filled_out++);
    if (buffer::filled_out == CHAR_BIT) {
      os << binary<unsigned char>(buffer::buffer_out);
      buffer::cleanBufferOut();
    }
    return os;
  }
}