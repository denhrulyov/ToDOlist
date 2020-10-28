//
// Created by denis on 14.08.20.
//
#include <gtest/gtest.h>
#include "client/TODOList.h"

int main(int argc, char** argv) {
    auto srv = todo_list::createService();
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
