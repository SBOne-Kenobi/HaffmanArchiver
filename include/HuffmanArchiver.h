#ifndef HW_03_HUFFMANARCHIVER_H
#define HW_03_HUFFMANARCHIVER_H

#include "HuffmanTree.h"
#include "HuffmanException.h"
#include <istream>
#include <ostream>
#include "binary.h"
#include <iostream>
#include <climits>

namespace HuffmanArchiver {
  void encode(std::istream &is, std::ostream &os, bool only_huffman = false); //flag for tests
  void decode(std::istream &is, std::ostream &os);
}

#endif
