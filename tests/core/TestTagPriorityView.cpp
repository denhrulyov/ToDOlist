//
// Created by denis on 29.07.20.
//

#include <gtest/gtest.h>
#include "core/memory_model/view/TagPriorityView.h"

class TestTagPriorityView : public ::testing::Test {

public:
    std::shared_ptr<TaskNode>  node1;
    std::shared_ptr<TaskNode>  node2;
    std::shared_ptr<TaskNode>  node3;
    std::shared_ptr<TaskNode>  node4;
    void SetUp() override {
        node1 = std::make_shared<TaskNode>(
                TaskID(1),
                Task::create("t1", TaskPriority::FIRST, "lbl1",
                        boost::gregorian::day_clock::local_day())
        );
        node2 = std::make_shared<TaskNode>(
                TaskID(2),
                Task::create("t2", TaskPriority::SECOND,
                        "lbl2", boost::gregorian::day_clock::local_day())
        );
        node3 = std::make_shared<TaskNode>(
                TaskID(3),
                Task::create("t3", TaskPriority::THIRD,
                        "lbl1", boost::gregorian::day_clock::local_day())
        );
        node4 = std::make_shared<TaskNode>(
                TaskID(4),
                Task::create("t4", TaskPriority::NONE,
                        "lbl2", boost::gregorian::day_clock::local_day())
        );
    }
};


TEST_F(TestTagPriorityView, AllTasksAdded) {
    TagPriorityView tw;
    tw.addToView(node1);
    tw.addToView(node2);
    tw.addToView(node3);
    tw.addToView(node4);
    EXPECT_EQ(tw.getAllWithConstraint("lbl1").size(), 2);
    EXPECT_EQ(tw.getAllWithConstraint("lbl2").size(), 2);
}

TEST_F(TestTagPriorityView, AllTasksSorted) {
    TagPriorityView tw;
    tw.addToView(node1);
    tw.addToView(node2);
    tw.addToView(node3);
    tw.addToView(node4);
    for (auto node : {node1, node2, node3, node4}) {
        auto result_set = tw.getAllWithConstraint(node->getTask().getLabel());
        for (std::size_t i = 0; i < result_set.size() - 1; ++i) {
            EXPECT_GE(result_set[i + 1].lock()->getTask().getPriority(),
                      result_set[i].lock()->getTask().getPriority());
        }
    }
}