#include "HuffmanTree.h"

#include <queue>

using binaryStream::binary;
using binaryStream::buffer;

HuffmanArchiver::HuffmanTree::HuffmanTree(const std::array<int, UCHAR_MAX + 1> &cnt) : cnt(cnt) {
  size_of_encoded_text = 0;
  root = nullptr;

  auto cmp = [](Node *a, Node *b) -> bool { return a->cnt > b->cnt || (a->cnt == b->cnt && a->symbol > b->symbol); };
  std::priority_queue<Node *, std::vector<Node *>, decltype(cmp)> queue(cmp);
  for (std::size_t i = 0; i < cnt.size(); i++)
    if (cnt[i])
      queue.push(new Node(cnt[i], i));
  while (queue.size() > 1) {
    auto zero = queue.top();
    queue.pop();
    auto one = queue.top();
    queue.pop();
    queue.push(new Node(zero, one));
    size_of_encoded_text += zero->cnt + one->cnt;
  }
  if (!queue.empty()) {
    root = NodePtr(queue.top());
    dfsGettingCode(root);
  }
}

std::size_t HuffmanArchiver::HuffmanTree::getTotalSize() const {
  return (size_of_encoded_text + CHAR_BIT - 1) / CHAR_BIT + getAddSize();
}

std::size_t HuffmanArchiver::HuffmanTree::Encode(std::istream &is, std::ostream &os) const {
  for (auto it : cnt)
    os << binary<int>(it);

  unsigned char tmp = 0;
  while (is >> binary<unsigned char>(tmp))
    for (const auto &it : code[tmp])
      os << binary<bool>(it);
  if (!buffer::BufferOutIsEmpty())
    buffer::dropBufferOut(os);

  return (CHAR_BIT - size_of_encoded_text % CHAR_BIT) % CHAR_BIT;
}

std::size_t HuffmanArchiver::HuffmanTree::getAddSize() {
  return (UCHAR_MAX + 1) * sizeof(int);
}

void HuffmanArchiver::HuffmanTree::dfsGettingCode(const HuffmanArchiver::HuffmanTree::NodePtr &v) {
  static std::vector<bool> way;
  if (v->isLeaf()) {
    code[v->symbol] = way;
  } else {
    for (int i = 0; i <= 1; i++) {
      way.push_back(i);
      dfsGettingCode(v->next[i]);
      way.pop_back();
    }
  }
}

std::size_t HuffmanArchiver::HuffmanTree::Decode(std::istream &is, std::ostream &os, std::size_t fict_bits,
                                                 std::size_t size_of_text) {
  std::array<int, UCHAR_MAX + 1> cnt{};
  for (auto &it : cnt) {
    is >> binary<int>(it);
    if (!is)
      throw HuffmanException("invalid text format.");
  }

  std::size_t result_size = 0;
  HuffmanTree t(cnt);
  if (size_of_text + t.getAddSize() != t.getTotalSize())
    throw HuffmanException("invalid text format.");
  const Node *cur = t.root.get();
  if (!cur || cur->isLeaf()) {
    unsigned char symbol = 0;
    for (std::size_t i = 0; i < cnt.size(); i++)
      if (cnt[i])
        symbol = i;
    while (cnt[symbol]--)
      os << binary<unsigned char>(symbol), result_size += 1;
  } else {
    while (size_of_text--) {
      std::size_t end = size_of_text ? CHAR_BIT : (CHAR_BIT - fict_bits);
      while (end--) {
        bool nextBit = false;
        is >> binary<bool>(nextBit);
        if (!is)
          throw HuffmanException("invalid text format.");
        cur = cur->next[nextBit].get();
        if (cur->isLeaf()) {
          os << binary<unsigned char>(cur->symbol);
          result_size += 1;
          cur = t.root.get();
        }
      }
    }
    buffer::cleanBufferIn();
    if (cur != t.root.get())
      throw HuffmanException("invalid text format.");
  }
  return result_size;
}

const std::vector<bool> &HuffmanArchiver::HuffmanTree::getCode(int ind) const {
  return code[ind];
}

size_t HuffmanArchiver::HuffmanTree::getSizeOfEncodedText() const {
  return size_of_encoded_text;
}

HuffmanArchiver::HuffmanTree::Node::Node(int cnt, unsigned char symbol) : cnt(cnt), symbol(symbol),
                                                                          next{nullptr, nullptr} {}

HuffmanArchiver::HuffmanTree::Node::Node(Node *zero, Node *one) :
        cnt(one->cnt + zero->cnt), symbol(zero->symbol + one->symbol), next{NodePtr(zero), NodePtr(one)} {}

bool HuffmanArchiver::HuffmanTree::Node::isLeaf() const {
  return !next[0];
}
