#include "HuffmanArchiver.h"

#include <array>

using std::array;
using HuffmanArchiver::HuffmanTree;
using binaryStream::binary;

void HuffmanArchiver::encode(std::istream &is, std::ostream &os, bool only_huffman) {
  array<int, UCHAR_MAX + 1> cnt{};
  unsigned char tmp = 0;
  std::size_t start_size = 0;
  while (is >> binary<unsigned char>(tmp))
    cnt[tmp]++, start_size++;

  std::size_t result_size = 0;
  std::size_t add_size = 0;
  is.clear();
  is.seekg(0);
  HuffmanTree t(cnt);
  if (start_size < t.getTotalSize() && !only_huffman) {
    os << binary<unsigned char>(0);
    add_size += 1;
    result_size += 1;

    while (is >> binary<unsigned char>(tmp))
      os << binary<unsigned char>(tmp);
    result_size += start_size;
  } else {
    result_size += t.getTotalSize();
    add_size += HuffmanTree::getAddSize();

    unsigned char type = 1;
    os << binary<unsigned char>(0);
    add_size += 1;
    result_size += 1;

    std::size_t fict_bits = t.Encode(is, os);
    type += (fict_bits << 1u);
    os.seekp(0);
    os << binary<unsigned char>(type);
  }

  std::cout << start_size << "\n" << result_size << "\n" << add_size << "\n";
}

void HuffmanArchiver::decode(std::istream &is, std::ostream &os) {
  is.seekg(0, is.end);
  std::size_t start_size = is.tellg();
  is.seekg(0);
  unsigned char type = 0;
  is >> binary<unsigned char>(type);
  if (!is)
    throw HuffmanException("invalid text format.");

  std::size_t result_size = 0;
  std::size_t add_size = 1;
  if (type & 1u) {
    type >>= 1u;
    add_size += HuffmanTree::getAddSize();
    result_size += HuffmanTree::Decode(is, os, type, start_size - add_size);
  } else {
    unsigned char tmp = 0;
    while (is >> binary<unsigned char>(tmp)) {
      os << binary<unsigned char>(tmp);
      result_size += 1;
    }
  }

  std::cout << start_size << "\n" << result_size << "\n" << add_size << "\n";
}