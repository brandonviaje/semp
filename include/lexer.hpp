#pragma once
#include <iostream>
#include <vector>
#include "token.hpp"

namespace semp {
class Lexer {
 public:
  Lexer(std::string source_code);
  std::vector<Token> tokenize();

 private:
  [[nodiscard]] char peek(int offset = 0) const;
  char consume();

  // member variables
  std::string m_src;
  std::size_t m_start;
  std::size_t m_current;
  int m_line;
};
};  // namespace semp
