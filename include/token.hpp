#pragma once
#include <ostream>
#include <string_view>

namespace semp {
enum class TokenType {
  _RETURN,
  _IDENTIFIER,
  _INT_LITERAL,
  _STR_LITERAL,
  _LEFT_BRACE,
  _RIGHT_BRACE,
  _LEFT_PAREN,
  _RIGHT_PAREN,
  _PLUS,
  _STAR,
  _SEMICOLON,
  _EOF
};

struct Token {
  TokenType type;
  std::string_view lexeme;
  int line;
};

inline const char* to_string(TokenType type) {
  switch (type) {
    case TokenType::_IDENTIFIER:
      return "IDENTIFIER";
    case TokenType::_RETURN:
      return "RETURN";
    case TokenType::_INT_LITERAL:
      return "INT_LITERAL";
    case TokenType::_STR_LITERAL:
      return "STR_LITERAL";
    case TokenType::_LEFT_BRACE:
      return "LEFT_BRACE";
    case TokenType::_RIGHT_BRACE:
      return "RIGHT_BRACE";
    case TokenType::_LEFT_PAREN:
      return "LEFT_PAREN";
    case TokenType::_RIGHT_PAREN:
      return "RIGHT_PAREN";
    case TokenType::_PLUS:
      return "PLUS";
    case TokenType::_STAR:
      return "STAR";
    case TokenType::_SEMICOLON:
      return "SEMICOLON";
    case TokenType::_EOF:
      return "EOF";
    default:
      return "UNKNOWN";
  }
}

inline std::ostream& operator<<(std::ostream& os, const Token& token) {
  os << to_string(token.type) << "(" << token.lexeme << ")";
  return os;
}
}  // namespace semp
