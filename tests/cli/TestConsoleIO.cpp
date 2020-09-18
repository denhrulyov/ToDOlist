//
// Created by denis on 09.09.20.
//

#include <gtest/gtest.h>
#include "cli/ConsoleIO.h"

class ConsoleIOTest : public ::testing::Test {
public:
    ConsoleIO io;
    std::stringstream mock_stream;
    ConsoleIOTest() : io(mock_stream, mock_stream) {}
};

TEST_F(ConsoleIOTest, TestReadWord) {
    std::string test_line = "first word";
    std::string test_line_1st_word = "first";
    mock_stream << test_line << std::endl;
    io.requestInputLine();
    ASSERT_EQ(io.readWord(), test_line_1st_word);
}

TEST_F(ConsoleIOTest, TestRequestInputLineBufferCleared) {
    std::string test_line = "some text";
    mock_stream << test_line << std::endl;
    io.requestInputLine();
    io.requestInputLine();
    ASSERT_EQ(io.seeBuffer(), "");
}

TEST_F(ConsoleIOTest, TestRequestInputLineAllRead) {
    std::string test_line = "some text";
    mock_stream << test_line << std::endl;
    io.requestInputLine();
    ASSERT_EQ(io.seeBuffer(), test_line);
}

TEST_F(ConsoleIOTest, TestBufferClear) {
    std::string test_line;
    mock_stream << test_line << std::endl;
    io.requestInputLine();
    io.clear();
    ASSERT_EQ(io.seeBuffer(), "");
}

TEST_F(ConsoleIOTest, TestSeeBuffer) {
    std::string test_line = "   test line with spaces  ";
    mock_stream << test_line << std::endl;
    io.requestInputLine();
    ASSERT_EQ(io.seeBuffer(), test_line);
}

TEST_F(ConsoleIOTest, TestPutLine) {
    mock_stream.clear();
    io.clear();
    std::string test_line = "   test line with spaces  ";
    io.putLine(test_line);
    std::string what_put;
    std::getline(mock_stream, what_put);
    ASSERT_EQ(test_line, what_put);
}

TEST_F(ConsoleIOTest, TestIsEmpty) {
    mock_stream.clear();
    io.clear();
    ASSERT_TRUE(io.isEmpty());
}

TEST_F(ConsoleIOTest, TestReadRestBuffer) {
    mock_stream.clear();
    io.clear();
    std::string test_line = "   test line with spaces  ";
    std::string test_line_without_prefix_spaces = "test line with spaces  ";
    mock_stream << test_line << std::endl;
    io.requestInputLine();
    ASSERT_EQ(io.readRestBuffer(), test_line_without_prefix_spaces);
}

TEST_F(ConsoleIOTest, TestReadRestBufferAfterReadWord) {
    mock_stream.clear();
    io.clear();
    std::string test_line = "   test line with spaces  ";
    std::string after_read_word = "line with spaces  ";
    mock_stream << test_line << std::endl;
    io.requestInputLine();
    io.readWord();
    ASSERT_EQ(io.readRestBuffer(), after_read_word);
}