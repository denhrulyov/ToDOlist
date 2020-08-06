#include <gtest/gtest.h>
#include "memory_model/TaskNode.h"

using namespace boost::gregorian;

class TaskNodeTest : public ::testing::Test {

};

const std::vector<Task> sample_tasks {
        Task::create("t1", Task::Priority::FIRST, "lbl1",
                day_clock::local_day() + days(200)),
        Task::create("t2", Task::Priority::NONE, "lbl2",
                day_clock::local_day() + days(220)),
        Task::create("t3", Task::Priority::SECOND, "lbl3",
                day_clock::local_day() + days(210))
};

TEST_F(TaskNodeTest, correctConstruction) {
    auto task = Task::create("a", Task::Priority::NONE, "lbl",
                             day_clock::local_day() + days(202));
    TaskNode tst(TaskID(1), task);
    auto sample_parent = std::make_shared<TaskNode>(TaskID(1), sample_tasks[0]);
    tst.setParent(sample_parent);
    EXPECT_EQ(tst.getId(), 1);
    EXPECT_EQ(tst.getTask().getName(), "a");
    EXPECT_EQ(tst.getTask().getPriority(), Task::Priority::NONE);
    EXPECT_EQ(tst.getTask().getLabel(), "lbl");
    EXPECT_EQ(tst.getTask().getDate(),
              day_clock::local_day() + days(202));
    EXPECT_EQ(tst.getSubtasks().size(), 0);
}

TEST_F(TaskNodeTest, notCompleteByDefault) {
    auto task = Task::create("a", Task::Priority::NONE, "lbl",
                             day_clock::local_day() + days(202));
    TaskNode tst(TaskID(1), task);
    EXPECT_FALSE(tst.isComplete());
}

TEST_F(TaskNodeTest, correctCloning) {
    auto task = Task::create("x", Task::Priority::NONE, "lbl2",
                             day_clock::local_day() + days(300));
    auto new_task = Task::create("a", Task::Priority::FIRST, "lbl",
                                 day_clock::local_day() + days(202));
    TaskNode sample(TaskID(1), task);
    auto sample_parent = std::make_shared<TaskNode>(TaskID(1), sample_tasks[0]);
    sample.setParent(sample_parent);
    const TaskNode& tst = *sample.clone(new_task);
    EXPECT_EQ(tst.getId(), 1);
    EXPECT_EQ(tst.getTask().getName(), "a");
    EXPECT_EQ(tst.getTask().getPriority(), Task::Priority::FIRST);
    EXPECT_EQ(tst.getTask().getLabel(), "lbl");
    EXPECT_EQ(tst.getTask().getDate(), day_clock::local_day() + days(202));
    EXPECT_EQ(tst.getParent(), sample_parent);
    EXPECT_EQ(tst.getSubtasks().size(), 0);
}

TEST_F(TaskNodeTest, correct) {

}

