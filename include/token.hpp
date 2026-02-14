#pragma once
#include <ostream>

namespace semp
{
    enum class TokenType
    {
        _RETURN,
        _INT_LITERAL,
        _STR_LITERAL,
        _LEFT_PARENS,
        _RIGHT_PARENS,
        _SEMICOLON
    };

    struct Token
    {
        TokenType type;
        std::string lexeme;
        int line;
    };

    inline const char *to_string(TokenType type)
    {
        switch (type)
        {
        case TokenType::_RETURN:
            return "RETURN";
        case TokenType::_INT_LITERAL:
            return "INT_LITERAL";
        case TokenType::_STR_LITERAL:
            return "STR_LITERAL";
        case TokenType::_LEFT_PARENS:
            return "LEFT_PARENTHESES";
        case TokenType::_RIGHT_PARENS:
            return "RIGHT_PARENTHESES";
        case TokenType::_SEMICOLON:
            return "SEMICOLON";
        }
        return "UNKNOWN";
    }

    inline std::ostream &operator<<(std::ostream &os, const Token &token)
    {
        os << to_string(token.type) << "(" << token.lexeme << ")";
        return os;
    }
}
