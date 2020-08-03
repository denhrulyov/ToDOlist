//
// Created by denis on 03.08.20.
//

#include <gtest/gtest.h>
#include "memory_model/ReferenceHandler.h"
#include "memory_model/DatePriorityView.h"
#include "memory_model/TagPriorityView.h"

class ReferenceHandlerTest : public ::testing::Test {
public:
    std::list<std::unique_ptr<DatePriorityView>> all_view1_;
    std::list<std::unique_ptr<TagPriorityView>> all_view2_;
    virtual void SetUp() override {

    }
};

ReferenceHandler defaultRefernceHandler(ReferenceHandlerTest* test) {
    auto by_date = std::make_unique<DatePriorityView>();
    auto by_tag = std::make_unique<TagPriorityView>();
    ReferenceHandler rh(*by_date, *by_tag);
    test->all_view1_.push_back(std::move(by_date));
    test->all_view2_.push_back(std::move(by_tag));
    return rh;
}

TEST_F(ReferenceHandlerTest, TestChildLinkedToParent) {
    auto rh = defaultRefernceHandler(this);
    auto node1 = std::make_shared<TaskNode>(
            TaskID(1),
            Task::create("t1", Task::Priority::THIRD, "tg", 3000));
    auto node2 = std::make_shared<TaskNode>(
            TaskID(2),
            Task::create("t2", Task::Priority::SECOND, "tg2", 3100));
    rh.linkSubTask(node1, node2);
    EXPECT_EQ(node1.get(), node2->getParent().get());
    EXPECT_EQ(  node1->getSubtaskByID(node2->getId()).get(),
                node2.get());
}

TEST_F(ReferenceHandlerTest, TestLinkedNull) {
    auto rh = defaultRefernceHandler(this);
    auto node1 = std::make_shared<TaskNode>(
            TaskID(1),
            Task::create("t1", Task::Priority::THIRD, "tg", 3000));
    auto node2 = std::make_shared<TaskNode>(
            TaskID(2),
            Task::create("t2", Task::Priority::SECOND, "tg2", 3100));
    rh.linkSubTask(node1, nullptr);
    rh.linkSubTask(node2, nullptr);
    rh.linkSubTask(nullptr, node1);
    rh.linkSubTask(nullptr, nullptr);
    ASSERT_EXIT ((rh.linkSubTask(node1, nullptr), exit(0)), ::testing::ExitedWithCode(0), "");
    ASSERT_EXIT ((rh.linkSubTask(node2, nullptr), exit(0)), ::testing::ExitedWithCode(0), "");
    ASSERT_EXIT ((rh.linkSubTask(nullptr, node1), exit(0));, ::testing::ExitedWithCode(0), "");
    ASSERT_EXIT ((rh.linkSubTask(nullptr, nullptr), exit(0)), ::testing::ExitedWithCode(0), "");
}

TEST_F(ReferenceHandlerTest, TestSetReferencesInView) {
    auto by_date = std::make_unique<DatePriorityView>();
    auto by_tag = std::make_unique<TagPriorityView>();
    ReferenceHandler rh(*by_date, *by_tag);
    auto node1 = std::make_shared<TaskNode>(
            TaskID(1),
            Task::create("t1", Task::Priority::THIRD, "tg", 3000));
    rh.setReferences(node1);
    EXPECT_EQ(by_date->getAll(3001).size(), 1);
    EXPECT_EQ(by_tag->getAll("tg").size(), 1);
}

TEST_F(ReferenceHandlerTest, TestSubtaskAddedToParentIfParentStillDoesNotContainIt) {
    auto by_date = std::make_unique<DatePriorityView>();
    auto by_tag = std::make_unique<TagPriorityView>();
    ReferenceHandler rh(*by_date, *by_tag);
    auto parent = std::make_shared<TaskNode>(
            TaskID(1),
            Task::create("t1", Task::Priority::THIRD, "tg", 3000));
    auto node2 = std::make_shared<TaskNode>(
            TaskID(2),
            Task::create("t2", Task::Priority::SECOND, "tg2", 3100));
    node2->setParent(parent);
    rh.setReferences(node2);
    EXPECT_EQ(parent->getSubtasks().size(), 1);
}

TEST_F(ReferenceHandlerTest, TestAllLinksAreSet) {
    auto by_date = std::make_unique<DatePriorityView>();
    auto by_tag = std::make_unique<TagPriorityView>();
    ReferenceHandler rh(*by_date, *by_tag);
    auto parent = std::make_shared<TaskNode>(
            TaskID(1),
            Task::create("t1", Task::Priority::THIRD, "tg", 3000));
    auto node = std::make_shared<TaskNode>(
            TaskID(2),
            Task::create("t2", Task::Priority::SECOND, "tg2", 3100));
    auto child1 = std::make_shared<TaskNode>(
            TaskID(3),
            Task::create("t3", Task::Priority::FIRST, "tg2", 2100));
    auto child2 = std::make_shared<TaskNode>(
            TaskID(4),
            Task::create("t4", Task::Priority::NONE, "tg2", 5100));
    rh.linkSubTask(parent, node);
    rh.linkSubTask(node, child1);
    rh.linkSubTask(node, child2);
    rh.setReferences(parent);
    rh.setReferences(node);
    rh.setReferences(child1);
    rh.setReferences(child2);
    EXPECT_EQ(parent->getSubNodes().size(), 1);
    EXPECT_EQ(node->getSubNodes().size(), 2);
    ASSERT_EQ(node->getParent(), parent);
    ASSERT_EQ(child1->getParent(), node);
    ASSERT_EQ(child2->getParent(), node);
}

TEST_F(ReferenceHandlerTest, MoveInternalReferencesMethodSetLinksCorrect) {
    auto by_date = std::make_unique<DatePriorityView>();
    auto by_tag = std::make_unique<TagPriorityView>();
    ReferenceHandler rh(*by_date, *by_tag);
    auto parent = std::make_shared<TaskNode>(
            TaskID(1),
            Task::create("t1", Task::Priority::THIRD, "tg", 3000));
    auto node = std::make_shared<TaskNode>(
            TaskID(2),
            Task::create("t2", Task::Priority::SECOND, "tg2", 3100));
    auto child1 = std::make_shared<TaskNode>(
            TaskID(3),
            Task::create("t3", Task::Priority::FIRST, "tg3", 2100));
    auto child2 = std::make_shared<TaskNode>(
            TaskID(4),
            Task::create("t4", Task::Priority::NONE, "tg4", 5100));
    rh.linkSubTask(parent, node);
    rh.linkSubTask(node, child1);
    rh.linkSubTask(node, child2);
    rh.setReferences(parent);
    rh.setReferences(node);
    rh.setReferences(child1);
    rh.setReferences(child2);
    auto node2 = std::make_shared<TaskNode>(
            TaskID(2),
            Task::create("t2_copy", Task::Priority::SECOND, "tg5", 3100));
    rh.copyExternalReferences(node, node2);
    rh.moveInboundRefrences(node, node2);
    EXPECT_EQ(parent->getSubNodes().size(), 1);
    EXPECT_EQ(node2->getSubNodes().size(), 2);
    EXPECT_EQ(node2->getParent().get(), parent.get());
    EXPECT_EQ(child1->getParent().get(), node2.get());
    EXPECT_EQ(child2->getParent().get(), node2.get());
    // check if view was updated
    auto with_node2_tag =  by_tag->getAll(
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