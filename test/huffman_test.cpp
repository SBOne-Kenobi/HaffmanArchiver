#include "huffman_test.h"

bool checkEqFiles(const std::string &name1, const std::string &name2) {
  std::ifstream f1(name1, std::ifstream::in | std::ifstream::binary);
  std::ifstream f2(name2, std::ifstream::in | std::ifstream::binary);
  bool res = true;
  f1.seekg(0, f1.end);
  f2.seekg(0, f2.end);
  if (f1.tellg() == f2.tellg()) {
    f1.seekg(0);
    f2.seekg(0);
    char tmp1 = 0;
    char tmp2 = 0;
    binaryStream::binary<char> x1(tmp1), x2(tmp2);
    while ((f1 >> x1) && (f2 >> x2) && res) {
      res = (tmp1 == tmp2);
    }
  } else {
    res = false;
  }
  f1.close();
  f2.close();
  return res;
}

bool checkArchiver(const std::string &name_in, const std::string &name_tmp, const std::string &name_out,
                   bool test_huffman = false) {
  std::ifstream is(name_in, std::ifstream::in | std::ifstream::binary);
  std::ofstream os(name_tmp, std::ofstream::out | std::ofstream::binary);
  HuffmanArchiver::encode(is, os, test_huffman);
  is.close();
  os.close();
  is.open(name_tmp, std::ifstream::in | std::ifstream::binary);
  os.open(name_out, std::ofstream::out | std::ofstream::binary);
  HuffmanArchiver::decode(is, os);
  is.close();
  os.close();
  return checkEqFiles(name_in, name_out);
}

TEST_F(TestEmptyFile, test1) {
  EXPECT_TRUE(checkArchiver(name_in, name_tmp, name_out));
}

TEST_F(TestEmptyFile, test2) {
  rename(name_in, "input.bin");
  EXPECT_TRUE(checkArchiver(name_in, name_tmp, name_out));
}

TEST_F(TestEmptyFile, test3) {
  rename(name_out, "output.bin");
  EXPECT_TRUE(checkArchiver(name_in, name_tmp, name_out));
}

TEST_F(TestEmptyFile, test4) {
  rename(name_tmp, "tmp.txt");
  EXPECT_TRUE(checkArchiver(name_in, name_tmp, name_out));
}

TEST_F(TestEmptyFile, test5) {
  rename(name_in, "input.bin");
  rename(name_tmp, "tmp.txt");
  rename(name_out, "output.bin");
  EXPECT_TRUE(checkArchiver(name_in, name_tmp, name_out));
}

TEST_F(TestArchiverOnEqualSeq, test1) {
  fillByChar(12412, '@');
  EXPECT_TRUE(checkArchiver(name_in, name_tmp, name_out));
}

TEST_F(TestArchiverOnEqualSeq, test2) {
  fillByChar(111111, '%');
  EXPECT_TRUE(checkArchiver(name_in, name_tmp, name_out));
}

TEST_F(TestArchiverOnEqualSeq, test3) {
  fillByChar(1, '#');
  EXPECT_TRUE(checkArchiver(name_in, name_tmp, name_out));
}

TEST_F(TestArchiverOnEqualSeq, test4) {
  fillByChar(50, 0);
  EXPECT_TRUE(checkArchiver(name_in, name_tmp, name_out));
}

TEST_F(TestArchiverOnEqualSeq, test5) {
  fillByChar(121, '\n');
  EXPECT_TRUE(checkArchiver(name_in, name_tmp, name_out));
}

TEST_F(TestArchiverOnEqualSeq, testHuffmanOnly1) {
  fillByChar(12412, '@');
  EXPECT_TRUE(checkArchiver(name_in, name_tmp, name_out, true));
}

TEST_F(TestArchiverOnEqualSeq, testHuffmanOnly2) {
  fillByChar(111111, '%');
  EXPECT_TRUE(checkArchiver(name_in, name_tmp, name_out, true));
}

TEST_F(TestArchiverOnEqualSeq, testHuffmanOnly3) {
  fillByChar(1, '#');
  EXPECT_TRUE(checkArchiver(name_in, name_tmp, name_out, true));
}

TEST_F(TestArchiverOnEqualSeq, testHuffmanOnly4) {
  fillByChar(50, 0);
  EXPECT_TRUE(checkArchiver(name_in, name_tmp, name_out, true));
}

TEST_F(TestArchiverOnEqualSeq, testHuffmanOnly5) {
  fillByChar(121, '\n');
  EXPECT_TRUE(checkArchiver(name_in, name_tmp, name_out, true));
}

TEST_F(TestArchiverOnRandSeq, test1) {
  fillByRandStr(10);
  EXPECT_TRUE(checkArchiver(name_in, name_tmp, name_out));
}

TEST_F(TestArchiverOnRandSeq, test2) {
  fillByRandStr(24673);
  EXPECT_TRUE(checkArchiver(name_in, name_tmp, name_out));
}

TEST_F(TestArchiverOnRandSeq, test3) {
  fillByRandStr(102353);
  EXPECT_TRUE(checkArchiver(name_in, name_tmp, name_out));
}

TEST_F(TestArchiverOnRandSeq, test4) {
  fillByRandStr(100000);
  EXPECT_TRUE(checkArchiver(name_in, name_tmp, name_out));
}

TEST_F(TestArchiverOnRandSeq, HARDtest5) {
  fillByRandStr(5242880);
  EXPECT_TRUE(checkArchiver(name_in, name_tmp, name_out));
}

TEST_F(TestHuffmanTree, testConstructor1) {
  checkDeterminism(1000, size);
}

TEST_F(TestHuffmanTree, testConstructor2) {
  checkDeterminism(1000, 100);
}

TEST_F(TestHuffmanTree, testConstructor3) {
  checkDeterminism(1000, 50);
}

TEST_F(TestHuffmanTree, testConstructor4) {
  checkDeterminism(1000, 5);
}

TEST_F(TestHuffmanTree, testConstructor5) {
  checkDeterminism(1000, 1);
}

TEST_F(TestArchiverOnRandSeq, testHuffmanOnly1) {
  fillByRandStr(10);
  EXPECT_TRUE(checkArchiver(name_in, name_tmp, name_out, true));
}

TEST_F(TestArchiverOnRandSeq, testHuffmanOnly2) {
  fillByRandStr(24673);
  EXPECT_TRUE(checkArchiver(name_in, name_tmp, name_out, true));
}

TEST_F(TestArchiverOnRandSeq, testHuffmanOnly3) {
  fillByRandStr(102353);
  EXPECT_TRUE(checkArchiver(name_in, name_tmp, name_out, true));
}

TEST_F(TestArchiverOnRandSeq, testHuffmanOnly4) {
  fillByRandStr(100000);
  EXPECT_TRUE(checkArchiver(name_in, name_tmp, name_out, true));
}

TEST_F(TestArchiverOnRandSeq, HARDtestHuffmanOnly5) {
  fillByRandStr(5242880);
  EXPECT_TRUE(checkArchiver(name_in, name_tmp, name_out, true));
}

TEST_F(TestExceptions, test1) {
  EXPECT_THROW(HuffmanArchiver::decode(is, os), HuffmanException);
}

TEST_F(TestExceptions, test2) {
  is.close();
  std::ofstream out(name_in, std::ofstream::binary | std::ofstream::out);
  out << binaryStream::binary<char>(1);
  for (int i = 0; i < UCHAR_MAX + 1; i++)
    out << binaryStream::binary<int>(1);
  out.close();
  is.open(name_in, std::ifstream::binary | std::ifstream::in);
  EXPECT_THROW(HuffmanArchiver::decode(is, os), HuffmanException);
}

TEST_F(TestExceptions, test3) {
  is.close();
  std::ofstream out(name_in, std::ofstream::binary | std::ofstream::out);
  out << binaryStream::binary<char>(13);
  for (int i = 0; i < UCHAR_MAX + 1; i++)
    out << binaryStream::binary<int>(1);
  for (int i = 0; i < UCHAR_MAX + 1; i++)
    out << binaryStream::binary<unsigned char>(i);
  out.close();
  is.open(name_in, std::ifstream::binary | std::ifstream::in);
  EXPECT_THROW(HuffmanArchiver::decode(is, os), HuffmanException);
}

TEST_F(TestExceptions, test4) {
  is.close();
  std::ofstream out(name_in, std::ofstream::binary | std::ofstream::out);
  out << binaryStream::binary<char>(1);
  for (int i = 0; i < UCHAR_MAX + 1; i++)
    out << binaryStream::binary<int>(1);
  for (int i = 0; i < UCHAR_MAX + 1; i++)
    out << binaryStream::binary<unsigned char>(i);
  out.close();
  is.open(name_in, std::ifstream::binary | std::ifstream::in);
  EXPECT_NO_THROW(HuffmanArchiver::decode(is, os));
}