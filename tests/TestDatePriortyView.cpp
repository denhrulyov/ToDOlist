//
// Created by denis on 29.07.20.
//

#include <gtest/gtest.h>
#include "core/memory_model/view/DatePriorityView.h"

using namespace boost::gregorian;

class PriorityViewTest : public ::testing::Test {
protected:
    const BoostDate date_infinity = day_clock::local_day() + years(100);
    std::shared_ptr<TaskNode>  node1;
    std::shared_ptr<TaskNode>  node2;
    std::shared_ptr<TaskNode>  node3;
    std::shared_ptr<TaskNode>  node4;
    void SetUp() override {
        node1 = std::make_shared<TaskNode>(
                TaskID(1),
                Task::create("t1", TaskPriority::FIRST, "lbl1",
                        day_clock::local_day() + days(10))
        );
        node2 = std::make_shared<TaskNode>(
                TaskID(2),
                Task::create("t2", TaskPriority::SECOND, "lbl2",
                        day_clock::local_day() + days(20))
        );
        node3 = std::make_shared<TaskNode>(
                TaskID(3),
                Task::create("t3", TaskPriority::THIRD, "lbl1",
                        day_clock::local_day() + days(1))
        );
        node4 = std::make_shared<TaskNode>(
                TaskID(4),
                Task::create("t4", TaskPriority::NONE, "lbl2",
                             day_clock::local_day() + days(100))
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
    ASSERT_EQ(tw.getAllWithConstraint(nodes[0]->getTask().getDate() + days(1)).size(), 1);
    ASSERT_EQ(tw.getAllWithConstraint(nodes[1]->getTask().getDate()).size(), 2);
    ASSERT_EQ(tw.getAllWithConstraint(nodes[1]->getTask().getDate() + days(1)).size(), 2);
    ASSERT_EQ(tw.getAllWithConstraint(nodes[2]->getTask().getDate()).size(), 3);
    ASSERT_EQ(tw.getAllWithConstraint(nodes[2]->getTask().getDate() + days(1)).size(), 3);
    ASSERT_EQ(tw.getAllWithConstraint(nodes[3]->getTask().getDate()).size(), 4);
    ASSERT_EQ(tw.getAllWithConstraint(nodes[3]->getTask().getDate() + days(1)).size(), 4);
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