#include "huffman_test.h"

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  //перенаправление станартного потока вывода, чтобы не мешался при выводе googletest
  std::stringstream buffer;
  std::streambuf *sbuf = std::cout.rdbuf();
  std::cout.rdbuf(buffer.rdbuf());
  int exit_code = RUN_ALL_TESTS();
  std::cout.rdbuf(sbuf);
  return exit_code;
}