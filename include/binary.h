#ifndef HW_03_BINARY_H
#define HW_03_BINARY_H

#include <istream>
#include <ostream>
#include <cstdint>
#include <climits>

namespace binaryStream {
  template<typename T>
  class binary {
  private:
    const T &data;
  public:
    explicit binary(const T &data) : data(data) {}

    template<typename H>
    friend std::istream &operator>>(std::istream &is, const binary<H> &x);

    template<typename H>
    friend std::ostream &operator<<(std::ostream &os, const binary<H> &x);
  };

  template<>
  class binary<bool> {
  private:
    const bool &data;
  public:
    explicit binary(const bool &data) : data(data) {}

    friend std::istream &operator>>(std::istream &is, const binary<bool> &x);

    friend std::ostream &operator<<(std::ostream &os, const binary<bool> &x);
  };

  class buffer {
    static unsigned char buffer_in;
    static std::size_t filled_in;
    static unsigned char buffer_out;
    static std::size_t filled_out;

  public:
    static void cleanBufferIn();

    static void cleanBufferOut();

    static bool BufferInIsEmpty();

    static bool BufferOutIsEmpty();

    static void dropBufferOut(std::ostream &os);

    friend std::istream &operator>>(std::istream &is, const binary<bool> &x);

    friend std::ostream &operator<<(std::ostream &os, const binary<bool> &x);
  };
}

#include "binary_impl.inl"

#endif //HW_03_BINARY_H
