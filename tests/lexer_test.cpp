#include <gtest/gtest.h>
#include "../include/lexer.hpp"
#include "../include/token.hpp"

class LexerTest : public testing::Test {};

// Test: lexer handles basic return statement
TEST_F(LexerTest, HandleBasicReturn) 
{
    std::string source = "ret 42;";
    semp::Lexer lexer(source);
    auto tokens = lexer.tokenize();

    // expect 4 tokens: ret, 42, ;, EOF
    ASSERT_EQ(tokens.size(), 4);

    EXPECT_EQ(tokens[0].type, semp::TokenType::_RETURN);
    EXPECT_EQ(tokens[0].lexeme, "ret");
    EXPECT_EQ(tokens[0].line, 1);
    EXPECT_EQ(tokens[1].type, semp::TokenType::_INT_LITERAL);
    EXPECT_EQ(tokens[1].lexeme, "42");
    EXPECT_EQ(tokens[2].type, semp::TokenType::_SEMICOLON);
    EXPECT_EQ(tokens[3].type, semp::TokenType::_EOF);
}

// Test: lexer ignores whitespace and newlines
TEST_F(LexerTest, HandleComplexFormatting) 
{
    std::string source = "  ret    \n  100  ;  ";
    semp::Lexer lexer(source);
    auto tokens = lexer.tokenize();

    // expect 4 tokens: ret, 100, ;, EOF
    ASSERT_EQ(tokens.size(), 4);
    
    EXPECT_EQ(tokens[0].type, semp::TokenType::_RETURN);
    EXPECT_EQ(tokens[1].type, semp::TokenType::_INT_LITERAL);
    EXPECT_EQ(tokens[1].lexeme, "100");
    EXPECT_EQ(tokens[1].line, 2); 
}

// Test: lexer distinguishes keywords from identifiers
TEST_F(LexerTest, DistinguishKeywordsFromIdentifiers) 
{
    std::string source = "ret returnVal ret";
    semp::Lexer lexer(source);
    auto tokens = lexer.tokenize();

    // expect 4 tokens: ret, returnVal, ret, EOF
    ASSERT_EQ(tokens.size(), 4);
    
    EXPECT_EQ(tokens[0].type, semp::TokenType::_RETURN);
    EXPECT_EQ(tokens[1].type, semp::TokenType::_IDENTIFIER);
    EXPECT_EQ(tokens[1].lexeme, "returnVal"); 
    EXPECT_EQ(tokens[2].type, semp::TokenType::_RETURN);
    EXPECT_EQ(tokens[3].type, semp::TokenType::_EOF);
}

// Test: lexer handles symbols and string literals
TEST_F(LexerTest, HandleSymbolsAndStrings) 
{
    std::string source = "{ \"hello\" }";
    semp::Lexer lexer(source);
    auto tokens = lexer.tokenize();

    // expect 4 tokens: {, "hello", }, EOF
    ASSERT_EQ(tokens.size(), 4);

    EXPECT_EQ(tokens[0].type, semp::TokenType::_LEFT_BRACE);
    EXPECT_EQ(tokens[1].type, semp::TokenType::_STR_LITERAL);
    EXPECT_EQ(tokens[1].lexeme, "hello");
    EXPECT_EQ(tokens[2].type, semp::TokenType::_RIGHT_BRACE);
    EXPECT_EQ(tokens[3].type, semp::TokenType::_EOF);
}
