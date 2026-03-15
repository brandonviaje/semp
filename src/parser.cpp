#include "parser.hpp"

Parser::Parser(std::vector<semp::Token> tokens) : m_tokens{std::move(tokens)} {}

bool Parser::isAtEnd() const {
  // check if we hit EOF or end of vector
  return m_current >= m_tokens.size() ||
         m_tokens[m_current].type == semp::TokenType::_EOF;
}

semp::Token Parser::peek() const {
  // return current token
  return m_tokens[m_current];
}

semp::Token Parser::previous() const {
  // return prev token
  return m_tokens[m_current - 1];
}

semp::Token Parser::consume() {
  // check if token isnt the end
  if (!isAtEnd()) {
    m_current++;
  }

  return previous();
}

bool Parser::match(semp::TokenType type) {
  if (isAtEnd())
    return false;  // if at end of vector, return false

  // if token type matches desired type consume
  if (peek().type == type) {
    consume();
    return true;
  }

  return false;
}

semp::Token Parser::expect(semp::TokenType type,
                           const std::string& error_message) {
  // check if token type matches
  if (match(type)) {
    return previous();
  }

  throw std::runtime_error(error_message);
}
