#include "HuffmanException.h"

HuffmanException::HuffmanException(const std::string &message) : logic_error(message),
                                                                 message("ERROR: " + message) {}

const char *HuffmanException::what() const noexcept {
  return message.c_str();
}