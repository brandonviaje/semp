#include "../include/lexer.hpp"
#include <fstream>
#include <sstream>

// load source code into lexer
std::string semp::Lexer::load_file(std::string file_path)
{
    std::fstream input(file_path, std::ios::in);
    std::stringstream string_buffer;

    string_buffer << input.rdbuf(); // load file into string buffer
    input.close();

    return string_buffer.str();
}

// convert characters into tokens
std::vector<semp::Token> semp::Lexer::tokenize()
{
    std::vector<semp::Token> tokens;
    std::string buffer;
    std::size_t i{};

    // read through source file char by char
    while (i < contents.length())
    {
        char c{contents[i]};

        // skip whitespace
        if (std::isspace(c))
        {
            i++;
            continue;
        }

        // semicolon
        if (c == ';')
        {
            tokens.push_back({semp::TokenType::_SEMICOLON, ";", 0});
            i++;
            continue;
        }

        // parentheses
        if (c == '{')
        {
            tokens.push_back({semp::TokenType::_LEFT_PARENS, "{", 0});
            i++;
            continue;
        }

        if (c == '}')
        {
            tokens.push_back({semp::TokenType::_RIGHT_PARENS, "}", 0});
            i++;
            continue;
        }

        // identifier / keyword
        if (std::isalpha(c))
        {
            buffer.clear();
            while (i < contents.length() && std::isalpha(contents[i]))
            {
                buffer.push_back(contents[i]);
                i++;
            }

            // check for keywords
            if (buffer == "ret")
            {
                tokens.push_back({semp::TokenType::_RETURN, buffer, 0});
            }
            else
            {
                std::cerr << "Unknown Token: " << buffer << std::endl;
                exit(EXIT_FAILURE);
            }
            continue;
        }

        // str literal
        if (c == '"')
        {
            buffer.clear();
            i++; // skip begining quote

            while (i < contents.length())
            {
                if (contents[i] == '"')
                {
                    i++; // skip closing quote
                    break;
                }
                else
                {
                    buffer.push_back(contents[i]);
                    i++;
                }
            }
            tokens.push_back({semp::TokenType::_STR_LITERAL, buffer, 0}); // add to tokens
            continue;
        }

        // integer literal
        if (std::isdigit(c))
        {
            buffer.clear();

            // keep scanning if char is still a digit
            while (i < contents.length() && std::isdigit(contents[i]))
            {
                buffer.push_back(contents[i]);
                i++;
            }

            tokens.push_back({semp::TokenType::_INT_LITERAL, buffer, 0}); // add to tokens
            continue;
        }

        std::cerr << "Unexpected character: " << c << std::endl; // unknown character
        exit(EXIT_FAILURE);
    }

    return tokens;
}