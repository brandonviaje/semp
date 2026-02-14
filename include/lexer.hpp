#pragma once
#include <vector>
#include <iostream>
#include "token.hpp"

namespace semp
{
    class Lexer
    {
    private:
        std::string contents;

    public:
        Lexer(std::string file_path) : contents{load_file(file_path)}
        {
        }
        std::string load_file(std::string file_path);
        std::vector<Token> tokenize();
    };
};
