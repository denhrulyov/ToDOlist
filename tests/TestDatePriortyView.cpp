//
// Created by denis on 29.07.20.
//

#include <gtest/gtest.h>
#include "memory_model/DatePriorityView.h"

class PriorityViewTest : public ::testing::Test {
protected:
    const time_t date_infinity = std::numeric_limits<time_t>::max();
    std::shared_ptr<TaskNode>  node1;
    std::shared_ptr<TaskNode>  node2;
    std::shared_ptr<TaskNode>  node3;
    std::shared_ptr<TaskNode>  node4;
    void SetUp() override {
        node1 = std::make_shared<TaskNode>(
                TaskID(1),
                Task::create("t1", Task::Priority::FIRST, "lbl1", 2000)
        );
        node2 = std::make_shared<TaskNode>(
                TaskID(2),
                Task::create("t2", Task::Priority::SECOND, "lbl2", 2000)
        );
        node3 = std::make_shared<TaskNode>(
                TaskID(3),
                Task::create("t3", Task::Priority::THIRD, "lbl1", 2000)
        );
        node4 = std::make_shared<TaskNode>(
                TaskID(4),
                Task::create("t4", Task::Priority::NONE, "lbl2", 2000)
        );
    }
};


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
        EXPECT_GE(result_set[i + 1].lock()->getTask().getPriority(),
                  result_set[i].lock()->getTask().getPriority()      );
    }
}

