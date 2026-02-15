#include "../include/lexer.hpp"
#include <fstream>
#include <sstream>

// convert characters into tokens
std::vector<semp::Token> semp::Lexer::tokenize() {
  std::vector<semp::Token> tokens;
  std::size_t i{};
  int line{1};

  while (i < contents.length()) {
    char c{contents[i]};

    // skip white spaces
    if (std::isspace(c)) {
      if (c == '\n')
        line++;
      i++;
      continue;
    }

    std::size_t start{i};  // mark beginning of the token

    // identifiers/keywords
    if (std::isalpha(c)) {
      while (i < contents.length() && std::isalnum(contents[i]))
        i++;
      std::string_view lexeme =
          std::string_view(contents).substr(start, i - start);

      // key words
      TokenType type =
          (lexeme == "ret") ? TokenType::_RETURN : TokenType::_IDENTIFIER;
      tokens.push_back({type, lexeme, line});
      continue;
    }

    // int literal
    if (std::isdigit(c)) {
      while (i < contents.length() && std::isdigit(contents[i]))
        i++;
      tokens.push_back({TokenType::_INT_LITERAL,
                        std::string_view(contents).substr(start, i - start),
                        line});
      continue;
    }

    // str literal
    if (c == '"') {
      i++;  // skip opening quote

      while (i < contents.length() && contents[i] != '"') {
        if (contents[i] == '\n')
          line++;
        i++;
      }

      // parse lexeme
      std::string_view lexeme{
          std::string_view(contents).substr(start + 1, i - start - 1)};

      if (i < contents.length())
        i++;  // skip closing quote
      else {
        std::cerr << "Line " << line << ": Unterminated string literal\n";
        exit(EXIT_FAILURE);
      }

      tokens.push_back({TokenType::_STR_LITERAL, lexeme, line});
      continue;
    }

    // punctuation tokens
    switch (c) {
      case ';':
        tokens.push_back({TokenType::_SEMICOLON, ";", line});
        i++;
        continue;
      case '{':
        tokens.push_back({TokenType::_LEFT_BRACE, "{", line});
        i++;
        continue;
      case '}':
        tokens.push_back({TokenType::_RIGHT_BRACE, "}", line});
        i++;
        continue;
      default:
        std::cerr << "Line " << line << ": Unexpected character '" << c
                  << "'\n";
        exit(EXIT_FAILURE);
    }

    std::cerr << "Line " << line << ": Unexpected character '" << c << "'\n";
    exit(EXIT_FAILURE);
  }

  // EOF token
  tokens.push_back({TokenType::_EOF, "", line});

  return tokens;
}
