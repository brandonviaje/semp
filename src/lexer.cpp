#include "../include/lexer.hpp"
#include <fstream>
#include <sstream>

// constructor
semp::Lexer::Lexer(std::string source_code)
    : m_src{std::move(source_code)}, m_current{0}, m_start{0}, m_line{1} {}

// convert characters into tokens
std::vector<semp::Token> semp::Lexer::tokenize() {
  std::vector<semp::Token> tokens;

  // iterate through m_src
  while (peek() != '\0') {
    m_start = m_current;  // mark start of new token
    char c{consume()};

    // whitespace
    if (std::isspace(c)) {
      if (c == '\n') {
        m_line++;
      }
      continue;
    }

    // identifiers/keyword
    if (std::isalpha(c)) {
      // consume char
      while (std::isalnum(peek())) {
        consume();
      }

      std::string_view lexeme =
          std::string_view(m_src).substr(m_start, m_current - m_start);
      TokenType type =
          (lexeme == "ret") ? TokenType::_RETURN : TokenType::_IDENTIFIER;
      tokens.push_back({type, lexeme, m_line});
      continue;
    }

    // int literal
    if (std::isdigit(c)) {
      // consume int lit
      while (std::isdigit(peek())) {
        consume();
      }

      // parse lexeme
      std::string_view lexeme =
          std::string_view(m_src).substr(m_start, m_current - m_start);
      tokens.push_back(
          {TokenType::_INT_LITERAL, lexeme, m_line});  // add to tokens
      continue;
    }

    // str literal
    if (c == '"') {

      // scan str lit
      while (peek() != '"' && peek() != '\0') {
        if (peek() == '\n') {
          m_line++;
        }
        consume();
      }

      // if we hit EOF before finding second quote, throw err
      if (peek() == '\0') {
        throw std::runtime_error("Line " + std::to_string(m_line) +
                                 ": Unterminated string literal");
      }

      consume();  // closing quote

      // parse lexeme
      std::string_view lexeme = std::string_view(m_src).substr(
          m_start + 1, m_current - m_start - 2);  // skip start and end quote
      tokens.push_back({TokenType::_STR_LITERAL, lexeme, m_line});
      continue;
    }

    // punctuation tokens
    switch (c) {
      case ';':
        tokens.push_back({TokenType::_SEMICOLON, ";", m_line});
        break;
      case '{':
        tokens.push_back({TokenType::_LEFT_BRACE, "{", m_line});
        break;
      case '}':
        tokens.push_back({TokenType::_RIGHT_BRACE, "}", m_line});
        break;
      default:
        throw std::runtime_error("Line " + std::to_string(m_line) +
                                 ": Unknown character '" + c + "'");
    }
  }

  // EOF token
  tokens.push_back({TokenType::_EOF, "", m_line});
  return tokens;
}

// return character at current pos + offset
char semp::Lexer::peek(int offset) const {
  // check if reached EOF
  if (m_current + offset >= m_src.size()) {
    return '\0';
  }

  return m_src[m_current + offset];
}

// consumes and returns current character, advance index.
char semp::Lexer::consume() {
  // check if reached EOF
  if (m_current >= m_src.size()) {
    return '\0';
  }

  return m_src[m_current++];  // consume token and inc index
}