#include <iostream>
#include <cstring>
#include <string>
#include <fstream>
#include <ctime>

#include "HuffmanException.h"
#include "HuffmanArchiver.h"

int main(int argc, char **argv) {

  std::clock_t start = std::clock();

  try {
    if (argc == 6) {
      int code = 0;
      int decode = 0;
      std::string file;
      std::string output;

      for (int i = 1; i < argc; i++) {
        if (strcmp("-c", argv[i]) == 0)
          code++;
        else if (strcmp("-u", argv[i]) == 0)
          decode++;
        else if (strcmp("-f", argv[i]) == 0 || strcmp("--file", argv[i]) == 0) {
          if (++i < argc && file.empty())
            file = argv[i];
          else
            throw HuffmanException("wrong format of parameters.");
        } else if (strcmp("-o", argv[i]) == 0 || strcmp("--output", argv[i]) == 0) {
          if (++i < argc && output.empty())
            output = argv[i];
          else
            throw HuffmanException("wrong format of parameters.");
        }
      }

      if (decode + code != 1)
        throw HuffmanException("wrong format of parameters.");

      std::ifstream is(file, std::ifstream::in | std::ifstream::binary);
      if (!is.is_open())
        throw HuffmanException("can't open " + file);
      std::ofstream os(output, std::ofstream::out | std::ofstream::binary);
      if (!os.is_open())
        throw HuffmanException("can't open " + output);

      try {
        if (code)
          HuffmanArchiver::encode(is, os);
        else
          HuffmanArchiver::decode(is, os);
      } catch (...) {
        is.close();
        os.close();
        throw;
      }
    } else
      throw HuffmanException("wrong format of parameters.");

  } catch (const HuffmanException &e) {
    std::cout << e.what() << "\n";
  } catch (...) {
    std::cout << "Oops! Something goes wrong.\n";
  }

  clock_t end = clock();
  double seconds = (double) (end - start) / CLOCKS_PER_SEC;
  (void) seconds;
  //printf("The time: %f seconds\n", seconds);

  return 0;
}
