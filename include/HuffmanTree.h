#ifndef HW_03_HUFFMANTREE_H
#define HW_03_HUFFMANTREE_H

#include <array>
#include <memory>
#include <climits>
#include <cstdint>
#include <istream>
#include "binary.h"
#include <ostream>
#include <vector>
#include "HuffmanException.h"

namespace HuffmanArchiver {
  class HuffmanTree {
  protected:
    struct Node {
      int cnt;
      unsigned char symbol;
      std::unique_ptr<Node> next[2];

      explicit Node(int cnt, unsigned char symbol);

      Node(Node *zero, Node *one);

      bool isLeaf() const;
    };

    using NodePtr = std::unique_ptr<Node>;

    std::size_t size_of_encoded_text;
    NodePtr root;
    const std::array<int, UCHAR_MAX + 1> &cnt;

    std::array<std::vector<bool>, UCHAR_MAX + 1> code;

    void dfsGettingCode(const NodePtr &v);

  public:
    explicit HuffmanTree(const std::array<int, UCHAR_MAX + 1> &cnt);

    HuffmanTree(HuffmanTree &) = delete;

    void operator=(HuffmanTree &) = delete;

    std::size_t getTotalSize() const;

    std::size_t Encode(std::istream &is, std::ostream &os) const; //returns number of fictive bits

    static std::size_t Decode(std::istream &is, std::ostream &os, std::size_t fict_bits,
                              std::size_t size_of_text); //returns decoded text size

    static std::size_t getAddSize();

    //for tests

    const std::vector<bool> &getCode(int ind) const;

    size_t getSizeOfEncodedText() const;
  };
}


#endif
