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
                Task::create("t1", Task::Priority::FIRST, "lbl1", 2100)
        );
        node2 = std::make_shared<TaskNode>(
                TaskID(2),
                Task::create("t2", Task::Priority::SECOND, "lbl2", 2000)
        );
        node3 = std::make_shared<TaskNode>(
                TaskID(3),
                Task::create("t3", Task::Priority::THIRD, "lbl1", 100500)
        );
        node4 = std::make_shared<TaskNode>(
                TaskID(4),
                Task::create("t4", Task::Priority::NONE, "lbl2", 30)
        );
    }
};


TEST_F(PriorityViewTest, AllTasksAdded) {
    DatePriorityView tw;
    tw.addToView(node1);
    tw.addToView(node2);
    tw.addToView(node3);
    tw.addToView(node4);
    EXPECT_EQ(tw.getAllWithConstraint(date_infinity).size(), 4);
}

TEST_F(PriorityViewTest, AllTasksSortedByPrior) {
    DatePriorityView tw;
    tw.addToView(node1);
    tw.addToView(node2);
    tw.addToView(node3);
    tw.addToView(node4);
    auto result_set = tw.getAllWithConstraint(date_infinity);
    for (std::size_t i = 0; i < result_set.size() - 1; ++i) {
        EXPECT_GE(result_set[i + 1].lock()->getTask().getPriority(),
                  result_set[i].lock()->getTask().getPriority()      );
    }
}

TEST_F(PriorityViewTest, AllTasksSortedByDate) {
    DatePriorityView tw;
    tw.addToView(node1);
    tw.addToView(node2);
    tw.addToView(node3);
    tw.addToView(node4);
    auto result_set = tw.getAllWithConstraint(date_infinity);
    for (std::size_t i = 0; i < result_set.size() - 1; ++i) {
        EXPECT_GE(result_set[i + 1].lock()->getTask().getPriority(),
                  result_set[i].lock()->getTask().getPriority()      );
    }
}

TEST_F(PriorityViewTest, DateConstraintIsWorkingProperly) {
    DatePriorityView tw;
    tw.addToView(node1);
    tw.addToView(node2);
    tw.addToView(node3);
    tw.addToView(node4);
    std::vector nodes = {node1, node2, node3, node4};
    std::sort(nodes.begin(), nodes.end(),
            [] (const auto& lhs, const auto& rhs) {
                return lhs->getTask().getDate() < rhs->getTask().getDate();
    });
    ASSERT_EQ(tw.getAllWithConstraint(nodes[0]->getTask().getDate()).size(), 1);
    ASSERT_EQ(tw.getAllWithConstraint(nodes[0]->getTask().getDate() + 1).size(), 1);
    ASSERT_EQ(tw.getAllWithConstraint(nodes[1]->getTask().getDate()).size(), 2);
    ASSERT_EQ(tw.getAllWithConstraint(nodes[1]->getTask().getDate() + 1).size(), 2);
    ASSERT_EQ(tw.getAllWithConstraint(nodes[2]->getTask().getDate()).size(), 3);
    ASSERT_EQ(tw.getAllWithConstraint(nodes[2]->getTask().getDate() + 1).size(), 3);
    ASSERT_EQ(tw.getAllWithConstraint(nodes[3]->getTask().getDate()).size(), 4);
    ASSERT_EQ(tw.getAllWithConstraint(nodes[3]->getTask().getDate() + 1).size(), 4);
}

TEST_F(PriorityViewTest, PartialResultSetSortedByPriority) {
    DatePriorityView tw;
    tw.addToView(node1);
    tw.addToView(node2);
    tw.addToView(node3);
    tw.addToView(node4);
    std::vector nodes = {node1, node2, node3, node4};
    std::sort(nodes.begin(), nodes.end(),
              [] (const auto& lhs, const auto& rhs) {
                  return lhs->getTask().getDate() < rhs->getTask().getDate();
              });
    for (std::size_t j = 0; j < nodes.size(); ++j) {
        auto result_set = tw.getAllWithConstraint(nodes[j]->getTask().getDate());
        for (std::size_t i = 0; i < result_set.size() - 1; ++i) {
            EXPECT_GE(result_set[i + 1].lock()->getTask().getPriority(),
                      result_set[i].lock()->getTask().getPriority()      );
        }
    }
}