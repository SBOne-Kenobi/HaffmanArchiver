#ifndef HW_03_HUFFMANEXCEPTION_H
#define HW_03_HUFFMANEXCEPTION_H

#include <stdexcept>
#include <string>

class HuffmanException : public std::logic_error {
private:
  std::string message;
public:
  explicit HuffmanException(const std::string &message);

  const char *what() const noexcept override;
};


#endif
