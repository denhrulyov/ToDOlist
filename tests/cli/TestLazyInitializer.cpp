//
// Created by denis on 10.09.20.
//

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "cli/state_machines/utils/LazyInitializer.h"

class LazyInitializerTest : public ::testing::Test {

};

class MockBase {};

class MockType : public MockBase {};

TEST_F(LazyInitializerTest, TestReturnsNotNull) {
    auto li = LazyInitializer<MockBase, MockType>::createDefault();
    auto ptr_obj = li.getValue();
    ASSERT_TRUE(ptr_obj);
}

TEST_F(LazyInitializerTest, TestSameValueReturned) {
    auto li = LazyInitializer<MockBase, MockType>::createDefault();
    auto ptr_obj = li.getValue();
    ASSERT_EQ(ptr_obj.get(), li.getValue().get());
    ASSERT_EQ(ptr_obj.get(), li.getValue().get());
    ASSERT_EQ(ptr_obj.get(), li.getValue().get());
}