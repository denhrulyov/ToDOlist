//
// Created by denis on 29.07.20.
//

#include <gtest/gtest.h>
#include "memory_model/TagPriorityView.h"
#include "memory_model/TagPriorityView.cpp"

class TagPriorityViewPriTest : public ::testing::Test {

};

TEST_F(TagPriorityViewPriTest, AllTasksAdded) {
    auto node1 = std::make_shared<TaskNode>(
            TaskID(1),
            Task {"t1", Task::Priority::FIRST, "lbl1", 2000}
            );
    auto node2 = std::make_shared<TaskNode>(
            TaskID(2),
            Task {"t2", Task::Priority::SECOND, "lbl2", 2000}
    );
    auto node3 = std::make_shared<TaskNode>(
            TaskID(3),
            Task {"t3", Task::Priority::THIRD, "lbl1", 2000}
    );
    auto node4 = std::make_shared<TaskNode>(
            TaskID(4),
            Task {"t4", Task::Priority::NONE, "lbl2", 2000}
    );
    TagPriorityView tw;
    tw.addToView(node1);
    tw.addToView(node2);
    tw.addToView(node3);
    tw.addToView(node4);
    EXPECT_EQ(tw.getAllWithTag("lbl1").size(), 2);
    EXPECT_EQ(tw.getAllWithTag("lbl2").size(), 2);
}

TEST_F(TagPriorityViewPriTest, PointerExpiredCorrectReaction) {
    auto node1 = std::make_shared<TaskNode>(
            TaskID(1),
            Task {"t1", Task::Priority::FIRST, "lbl1", 2000}
    );
    auto node2 = std::make_shared<TaskNode>(
            TaskID(2),
            Task {"t2", Task::Priority::SECOND, "lbl2", 2000}
    );
    TagPriorityView tw;
    tw.addToView(node1);
    tw.addToView(node2);
    node2.reset();
    EXPECT_EQ(tw.getAllWithTag("lbl1").size(), 1);
    EXPECT_EQ(tw.getAllWithTag("lbl2").size(), 0);
}