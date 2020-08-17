//
// Created by denis on 06.08.20.
//

#include <gtest/gtest.h>
#include "core/api/RequestResult.h"

class TestRequestResult : public ::testing::Test {

};

TEST_F(TestRequestResult, CorrectConstructor) {
    RequestResult rr(false, "error");
    ASSERT_EQ(false, rr.getSuccessStatus());
    ASSERT_EQ("error", rr.getErrorMessage());
}
