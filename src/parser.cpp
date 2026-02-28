#include "parser.hpp"

Parser::Parser(std::vector<semp::Token> tokens) 
    : m_tokens{std::move(tokens)}
    {}

bool Parser::isAtEnd() const 
{
    // check if we hit EOF or end of vector
    return m_current >= m_tokens.size() || m_tokens[m_current].type == semp::TokenType::_EOF; 
}

semp::Token Parser::peek() const 
{
    return m_tokens[m_current];
}

semp::Token Parser::previous() const 
{
    return m_tokens[m_current - 1];
}

semp::Token Parser::consume() 
{
    // check if token isnt the end
    if (!isAtEnd()) 
    {
        m_current++;
    }

    return previous(); 
}
