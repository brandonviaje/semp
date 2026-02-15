#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include "../include/lexer.hpp"

// load source code into lexer
std::string load_file(const char* file_path) {
  std::fstream input(file_path, std::ios::in);

  if (!input) {
    std::cerr << "Could not open file: " << file_path << '\n';
    exit(EXIT_FAILURE);
  }

  std::stringstream string_buffer;
  string_buffer << input.rdbuf();  // load file into string buffer
  return string_buffer.str();
}

int main(int argc, char* argv[]) {
  // catch args
  if (argc != 2) {
    std::cout << "Usage: semp <text.semp>" << '\n';
    return EXIT_FAILURE;
  }

  std::string source_code{load_file(argv[1])};

  // create lexer object that reads .semp file
  semp::Lexer lexer(std::move(source_code));

  // tokenize source file
  std::vector<semp::Token> tokens{lexer.tokenize()};

  for (const auto& element : tokens) {
    std::cout << element << '\n';
  }

  return EXIT_SUCCESS;
}
