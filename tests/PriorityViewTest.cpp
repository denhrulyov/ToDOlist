//
// Created by denis on 29.07.20.
//

#include <gtest/gtest.h>
#include "memory_model/DatePriorityView.h"
#include "memory_model/DatePriorityView.cpp"

class PriorityViewTest : public ::testing::Test {

};

const auto date_infinity = std::numeric_limits<time_t>::max();

const auto node1 = std::make_shared<TaskNode>(
        TaskID(1),
        Task {"t1", Task::Priority::FIRST, "lbl1", 2000}
);
const auto node2 = std::make_shared<TaskNode>(
        TaskID(2),
        Task {"t2", Task::Priority::SECOND, "lbl2", 2000}
);
const auto node3 = std::make_shared<TaskNode>(
        TaskID(3),
        Task {"t3", Task::Priority::THIRD, "lbl1", 2000}
);
const auto node4 = std::make_shared<TaskNode>(
        TaskID(4),
        Task {"t4", Task::Priority::NONE, "lbl2", 2000}
);



TEST_F(PriorityViewTest, AllTasksAdded) {
    DatePriorityView tw;
    tw.addToView(node1);
    tw.addToView(node2);
    tw.addToView(node3);
    tw.addToView(node4);
    EXPECT_EQ(tw.getAll(date_infinity).size(), 4);
}

TEST_F(PriorityViewTest, AllTasksSorted) {
    DatePriorityView tw;
    tw.addToView(node1);
    tw.addToView(node2);
    tw.addToView(node3);
    tw.addToView(node4);
    auto result_set = tw.getAll(date_infinity);
    for (std::size_t i = 0; i < result_set.size() - 1; ++i) {
        EXPECT_GE(result_set[i + 1].lock()->getTask().priority,
                  result_set[i].lock()->getTask().priority      );
    }
}

