#pragma once
#include <vector>
#include "token.hpp"

class Parser
{
    public:
        Parser(std::vector<semp::Token> tokens);
    private:
        std::vector<semp::Token> m_tokens;
        std::size_t m_current {};
        
        [[nodiscard]] bool isAtEnd() const;
        [[nodiscard]]  semp::Token peek() const;
        [[nodiscard]]  semp::Token previous() const;
        semp::Token consume();
};
