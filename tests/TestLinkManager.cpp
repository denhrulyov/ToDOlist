//
// Created by denis on 03.08.20.
//

#include <gtest/gtest.h>
#include "core/memory_model/structure/LinkManager.h"
#include "core/memory_model/view/DatePriorityView.h"
#include "core/memory_model/view/TagPriorityView.h"

using namespace boost::gregorian;

class ReferenceHandlerTest : public ::testing::Test {
public:
    std::list<std::unique_ptr<DatePriorityView>> all_view1_;
    std::list<std::unique_ptr<TagPriorityView>> all_view2_;
    virtual void SetUp() override {

    }
};

LinkManager defaultRefernceHandler(ReferenceHandlerTest* test) {
    auto by_date = std::make_unique<DatePriorityView>();
    auto by_tag = std::make_unique<TagPriorityView>();
    LinkManager rh(*by_date, *by_tag);
    test->all_view1_.push_back(std::move(by_date));
    test->all_view2_.push_back(std::move(by_tag));
    return rh;
}

TEST_F(ReferenceHandlerTest, TestChildLinkedToParent) {
    auto rh = defaultRefernceHandler(this);
    auto node1 = std::make_shared<TaskNode>(
            TaskID(1),
            Task::create("t1", TaskPriority::THIRD, "tg",
                    day_clock::local_day() + days(30)));
    auto node2 = std::make_shared<TaskNode>(
            TaskID(2),
            Task::create("t2", TaskPriority::SECOND, "tg2",
                    day_clock::local_day() + days(31)));
    rh.linkSubTask(node1, node2);
    EXPECT_EQ(node1.get(), node2->getParent().lock().get());
    EXPECT_EQ(  node1->getSubtaskByID(node2->getId()).lock().get(),
                node2.get());
}


TEST_F(ReferenceHandlerTest, TestSetReferencesInView) {
    auto by_date = std::make_unique<DatePriorityView>();
    auto by_tag = std::make_unique<TagPriorityView>();
    LinkManager rh(*by_date, *by_tag);
    auto node1 = std::make_shared<TaskNode>(
            TaskID(1),
            Task::create("t1", TaskPriority::THIRD, "tg",
                    day_clock::local_day() + days(30)));
    rh.setLinks(node1);
    EXPECT_EQ(by_date->getAllWithConstraint(day_clock::local_day() + days(31)).size(), 1);
    EXPECT_EQ(by_tag->getAllWithConstraint("tg").size(), 1);
}

TEST_F(ReferenceHandlerTest, TestSubtaskAddedToParentIfParentStillDoesNotContainIt) {
    auto by_date = std::make_unique<DatePriorityView>();
    auto by_tag = std::make_unique<TagPriorityView>();
    LinkManager rh(*by_date, *by_tag);
    auto parent = std::make_shared<TaskNode>(
            TaskID(1),
            Task::create("t1", TaskPriority::THIRD, "tg",
                    day_clock::local_day() + days(30)));
    auto node2 = std::make_shared<TaskNode>(
            TaskID(2),
            Task::create("t2", TaskPriority::SECOND, "tg2",
                    day_clock::local_day() + days(31)));
    node2->setParent(parent);
    rh.setLinks(node2);
    EXPECT_EQ(parent->getSubtasks().size(), 1);
}

TEST_F(ReferenceHandlerTest, TestAllLinksAreSet) {
    auto by_date = std::make_unique<DatePriorityView>();
    auto by_tag = std::make_unique<TagPriorityView>();
    LinkManager rh(*by_date, *by_tag);
    auto parent = std::make_shared<TaskNode>(
            TaskID(1),
            Task::create("t1", TaskPriority::THIRD, "tg",
                    day_clock::local_day() + days(30)));
    auto node = std::make_shared<TaskNode>(
            TaskID(2),
            Task::create("t2", TaskPriority::SECOND, "tg2",
                    day_clock::local_day() + days(31)));
    auto child1 = std::make_shared<TaskNode>(
            TaskID(3),
            Task::create("t3", TaskPriority::FIRST, "tg2",
                    day_clock::local_day() + days(21)));
    auto child2 = std::make_shared<TaskNode>(
            TaskID(4),
            Task::create("t4", TaskPriority::NONE, "tg2",
                    day_clock::local_day() + days(51)));
    rh.linkSubTask(parent, node);
    rh.linkSubTask(node, child1);
    rh.linkSubTask(node, child2);
    rh.setLinks(parent);
    rh.setLinks(node);
    rh.setLinks(child1);
    rh.setLinks(child2);
    EXPECT_EQ(parent->getSubNodes().size(), 1);
    EXPECT_EQ(node->getSubNodes().size(), 2);
    ASSERT_EQ(node->getParent().lock().get(), parent.get());
    ASSERT_EQ(child1->getParent().lock().get(), node.get());
    ASSERT_EQ(child2->getParent().lock().get(), node.get());
}

TEST_F(ReferenceHandlerTest, MoveInternalReferencesMethodSetLinksCorrect) {
    auto by_date = std::make_unique<DatePriorityView>();
    auto by_tag = std::make_unique<TagPriorityView>();
    LinkManager rh(*by_date, *by_tag);
    auto parent = std::make_shared<TaskNode>(
            TaskID(1),
            Task::create("t1", TaskPriority::THIRD, "tg",
                    day_clock::local_day() + days(30)));
    auto node = std::make_shared<TaskNode>(
            TaskID(2),
            Task::create("t2", TaskPriority::SECOND, "tg2",
                    day_clock::local_day() + days(31)));
    auto child1 = std::make_shared<TaskNode>(
            TaskID(3),
            Task::create("t3", TaskPriority::FIRST, "tg3",
                    day_clock::local_day() + days(21)));
    auto child2 = std::make_shared<TaskNode>(
            TaskID(4),
            Task::create("t4", TaskPriority::NONE, "tg4",
                    day_clock::local_day() + days(51)));
    rh.linkSubTask(parent, node);
    rh.linkSubTask(node, child1);
    rh.linkSubTask(node, child2);
    rh.setLinks(parent);
    rh.setLinks(node);
    rh.setLinks(child1);
    rh.setLinks(child2);
    auto node2 = node->clone(Task::create("t2_copy", TaskPriority::SECOND, "tg5",
                                          day_clock::local_day() + days(31)));
    rh.moveInboundLinks(node, node2);
    EXPECT_EQ(parent->getSubNodes().size(), 1);
    EXPECT_EQ(node2->getSubNodes().size(), 2);
    EXPECT_EQ(node2->getParent().lock().get(), parent.get());
    EXPECT_EQ(child1->getParent().lock().get(), node2.get());
    EXPECT_EQ(child2->getParent().lock().get(), node2.get());
    // check if view was updated
    auto with_node2_tag = by_tag->getAllWithConstraint(
            node2
                    ->getTask()
                    .getLabel()
    );
    EXPECT_EQ(with_node2_tag.size(), 1);
    EXPECT_EQ(with_node2_tag[0]
                                 .lock()
                                 .get(),
              node2.get()
              );

}