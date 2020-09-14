//
// Created by denis on 09.09.20.
//

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "cli/tokenization/KeywordTokenizer.h"
#include "mocks/MockIO.h"

class KeywordTokenizerTest : public ::testing::Test {

public:
    std::vector<std::string> string_commands {
            "add",
            "show",
            "delete",
            "postpone",
            "today",
            "this_week",
            "all",
            "tag",
            "task",
            "subtask",
            "Y",
            "n"
    };
    std::map<std::string, Keyword> must_match;

public:
    KeywordTokenizerTest() : must_match {
        {"add",       Keyword::ADD},
        {"show",      Keyword::SHOW},
        {"delete",    Keyword::DELETE},
        {"postpone",  Keyword::POSTPONE},
        {"today",     Keyword::TODAY},
        {"this_week", Keyword::THIS_WEEK},
        {"all",       Keyword::ALL},
        {"tag",       Keyword::TAG},
        {"task",      Keyword::TASK},
        {"subtask",   Keyword::SUBTASK},
        {"Y",         Keyword::YES},
        {"n",         Keyword::NO}
    } {}
};

using ::testing::Return;

TEST_F(KeywordTokenizerTest, TestTokenizerDetection) {
    KeywordTokenizer tokenizer;
    for (const auto& cmd : string_commands) {
        auto mo = std::make_unique<MockIO>();
        EXPECT_CALL(*mo, readWord()).WillOnce(Return(cmd));
        ASSERT_EQ(must_match[cmd], tokenizer.read(*mo));
    }

}

TEST_F(KeywordTokenizerTest, TestTokenizerReturnUnknown) {
    auto mo = std::make_unique<MockIO>();
    EXPECT_CALL(*mo, readWord()).WillOnce(Return("abacabadabacaba"));
    ASSERT_EQ(Keyword::UNKNOWN, KeywordTokenizer().read(*mo));
}