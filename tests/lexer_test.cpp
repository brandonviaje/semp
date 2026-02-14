#include <gtest/gtest.h>
#include <fstream>
#include <sstream>
#include <string>
#include "../include/lexer.hpp"

class LexerTest : public testing::Test
{
protected:
    std::string content;

    void SetUp() override
    {
        content = load_file("test.semp");
    }

    std::string load_file(const std::string &file_path)
    {
        std::ifstream input(file_path);
        std::stringstream buffer;

        buffer << input.rdbuf();
        return buffer.str();
    }
};

TEST_F(LexerTest, TestCaseSensitive)
{
    auto content = load_file("test.semp");
    EXPECT_FALSE(content.empty());
}
