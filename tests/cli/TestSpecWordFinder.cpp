//
// Created by denis on 09.09.20.
//

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "cli/tokenization/SpecwordFinder.h"


class SpecwordFinderTest : public ::testing::Test {

};

TEST_F(SpecwordFinderTest, FindsSpecWord) {
    ASSERT_EQ(SpecwordFinder::findSpecWord("__exit__"), Keyword::EXIT);
    ASSERT_EQ(SpecwordFinder::findSpecWord("__abort__"), Keyword::ABORT);
}

TEST_F(SpecwordFinderTest, FindsSpecWordsWithinText) {
    ASSERT_EQ(SpecwordFinder::findSpecWord("  __exit__  "), Keyword::EXIT);
    ASSERT_EQ(SpecwordFinder::findSpecWord("  __abort__  "), Keyword::ABORT);
    ASSERT_EQ(SpecwordFinder::findSpecWord("d  ds__exit__sad  "), Keyword::EXIT);
    ASSERT_EQ(SpecwordFinder::findSpecWord("d  dd__abort__1  "), Keyword::ABORT);
}

TEST_F(SpecwordFinderTest, FindsExitFirst) {
    ASSERT_EQ(SpecwordFinder::findSpecWord("  __abort__ __exit__  "), Keyword::EXIT);
}

TEST_F(SpecwordFinderTest, ReturnsNoneIfNoSuch) {
    ASSERT_EQ(SpecwordFinder::findSpecWord("  _1_abort_1__ _exit__  "), Keyword::NONE);
}