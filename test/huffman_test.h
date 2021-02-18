#ifndef HW_03_HUFFMAN_TEST_H
#define HW_03_HUFFMAN_TEST_H

#include <gtest/gtest.h>
#include <fstream>
#include "binary.h"
#include "HuffmanArchiver.h"
#include <random>
#include <climits>
#include "HuffmanTree.h"

inline void create(const std::string &name) {
  std::ofstream os(name);
  os.close();
}

inline void rename(std::string &name, const std::string &new_name) {
  remove(name.c_str());
  name = new_name;
  create(name);
}

class TestEmptyFile : public ::testing::Test {
protected:
  std::string name_in;
  std::string name_tmp;
  std::string name_out;

  inline void SetUp() override {
    name_in = "input.txt";
    name_out = "output.txt";
    name_tmp = "tmp.bin";
    create(name_in);
    create(name_tmp);
    create(name_out);
  }

  inline void TearDown() override {
    remove(name_in.c_str());
    remove(name_tmp.c_str());
    remove(name_out.c_str());
  }
};

class TestArchiverOnEqualSeq : public TestEmptyFile {
protected:
  inline void fillByChar(int cnt, char c) {
    std::ofstream os(name_in, std::ofstream::binary | std::ofstream::out);
    while (cnt--)
      os << binaryStream::binary<char>(c);
    os.close();
  }
};

class TestArchiverOnRandSeq : public TestEmptyFile {
protected:
  inline void fillByRandStr(int cnt) {
    std::mt19937 rd(std::random_device().operator()());
    std::uniform_int_distribution<char> distribution(CHAR_MIN, CHAR_MAX);
    std::ofstream os(name_in, std::ofstream::binary | std::ofstream::out);
    while (cnt--)
      os << binaryStream::binary<char>(distribution(rd));
    os.close();
  }
};

class TestHuffmanTree : public ::testing::Test {
protected:
  std::array<int, UCHAR_MAX + 1> cnt;
  HuffmanArchiver::HuffmanTree *t;
  int size;

  inline void genCntForEqualCode(int new_size) {
    new_size = std::min(new_size, UCHAR_MAX + 1);
    int cur = 1;
    while (cur < new_size)
      cur *= 2;
    new_size = cur;

    size = new_size;
    cnt.fill(0);
    while (new_size--) {
      cnt[new_size]++;
    }
    delete t;
    t = new HuffmanArchiver::HuffmanTree(cnt);
  }

  inline void checkDeterminism(int T, int sz) {
    genCntForEqualCode(sz);
    std::vector<std::vector<bool>> buf(size);
    for (int i = 0; i < size; i++) {
      buf[i] = t->getCode(i);
      EXPECT_FLOAT_EQ(log2(size), buf[i].size());
    }

    for (int i = 0; i < size - 1; i++) {
      for (int j = i + 1; j < size; j++) {
        EXPECT_NE(buf[i], buf[j]);
      }
    }

    for (int times = 1; times < T; times++) {
      delete t;
      t = new HuffmanArchiver::HuffmanTree(cnt);
      for (int i = 0; i < size; i++) {
        EXPECT_EQ(buf[i], t->getCode(i));
      }
    }

    EXPECT_FLOAT_EQ(t->getSizeOfEncodedText(), size * log2(size));
  }

  inline void SetUp() override {
    t = nullptr;
    genCntForEqualCode(1024);
  }

  inline void TearDown() override {
    delete t;
  }
};

class TestExceptions : public ::testing::Test {
protected:
  std::string name_in;
  std::string name_out;
  std::ifstream is;
  std::ofstream os;

  inline void SetUp() override {
    name_in = "in.bin";
    name_out = "out.bin";
    create(name_in);
    create(name_out);
    is.open(name_in, std::ifstream::in | std::ifstream::binary);
    os.open(name_out, std::ofstream::out | std::ofstream::binary);
  }

  inline void TearDown() override {
    is.close();
    os.close();
    remove(name_in.c_str());
    remove(name_out.c_str());
  }
};

#endif //HW_03_HUFFMAN_TEST_H
