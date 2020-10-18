//
// Created by denis on 14.07.20.
//

#include <gtest/gtest.h>
#include <boost/date_time.hpp>
#include "core/memory_model/api/RepositoryTaskDTO.h"

class TestRepositoryTaskDTO : public ::testing::Test {

};


TEST_F(TestRepositoryTaskDTO, correctCopy) {
    RepositoryTaskDTO x = RepositoryTaskDTO::create(TaskID(1), "name", TaskPriority::NONE,
                                                    "lbl", boost::gregorian::day_clock::local_day());
    auto y = x;
    EXPECT_EQ(y.getId(), 1);
    EXPECT_EQ(y.getName(), "name");
    EXPECT_EQ(y.getPriority(), TaskPriority::NONE);
    EXPECT_EQ(y.getLabel(), "lbl");
    EXPECT_EQ(y.getDate(), boost::gregorian::day_clock::local_day());
}
