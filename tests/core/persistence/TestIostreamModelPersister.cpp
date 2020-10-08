//
// Created by denis on 30.09.20.
//

#include "mocks/CoreMocks.h"
#include "mocks/CoreMocks.h"
#include "core/persistence/IostreamModelPersister.h"
#include <gtest/gtest.h>
#include <gmock/gmock.h>


#include "core/api/TODOList.h"
using ::testing::NiceMock;
using ::testing::Return;
using ::testing::Truly;
using ::testing::_;

class IostreamModelPersisterTest : public ::testing::Test {

};

#define DUMMY_TASK_FIELDS "name", TaskPriority::FIRST, "label", boost::gregorian::day_clock::local_day()
#define DUMMY_TAIL  TaskPriority::FIRST, "label", boost::gregorian::day_clock::local_day()

void fill_task(TaskData* task, std::string name) {
    task->set_name(name);
    task->set_prior(TaskData::THIRD);
    task->set_label("label");
    task->set_allocated_date(::google::protobuf::Timestamp().New());
    task->set_completed(true);
}

auto has_name(std::string str) {
    return Truly([str] (const TaskDTO& dto) {
        return dto.getName() == str;
    });
}

TEST_F(IostreamModelPersisterTest, TestDemanglesAllSubtasks) {
    MockModel mm;
    TaskModelMessage model_proto;
    TaskMessage* task1 = model_proto.add_tasks();
    task1->set_allocated_task(new TaskData);
    fill_task(task1->mutable_task(), "1");
    EXPECT_CALL(mm, addTask(Truly([] (const TaskDTO& dto) {
        return dto.getName() == "1";
    })))
            .WillOnce(Return(TaskCreationResult::success(TaskID(0))));
    TaskMessage* task2 = model_proto.add_tasks();
    task2->set_allocated_task(new TaskData);
    fill_task(task2->mutable_task(), "2");
    EXPECT_CALL(mm, addTask(has_name("2")))
            .WillOnce(Return(TaskCreationResult::success(TaskID(1))));
    TaskMessage* task3 = model_proto.add_tasks();
    task3->set_allocated_task(new TaskData);
    fill_task(task3->mutable_task(), "3");
    EXPECT_CALL(mm, addTask(has_name("3")))
            .WillOnce(Return(TaskCreationResult::success(TaskID(2))));
    TaskMessage* task11 = task1->add_subtasks();
    task11->set_allocated_task(new TaskData);
    fill_task(task11->mutable_task(), "11");
    EXPECT_CALL(mm, addSubTask(TaskID(0), has_name("11")))
            .WillOnce(Return(TaskCreationResult::success(TaskID(3))));
    TaskMessage* task12 = task1->add_subtasks();
    task12->set_allocated_task(new TaskData);
    fill_task(task12->mutable_task(), "12");
    EXPECT_CALL(mm, addSubTask(TaskID(0), has_name("12")))
            .WillOnce(Return(TaskCreationResult::success(TaskID(4))));
    TaskMessage* task13 = task1->add_subtasks();
    task13->set_allocated_task(new TaskData);
    fill_task(task13->mutable_task(), "13");
    EXPECT_CALL(mm, addSubTask(TaskID(0), has_name("13")))
            .WillOnce(Return(TaskCreationResult::success(TaskID(5))));
    TaskMessage* task121 = task12->add_subtasks();
    task121->set_allocated_task(new TaskData);
    fill_task(task121->mutable_task(), "121");
    EXPECT_CALL(mm, addSubTask(TaskID(4), has_name("121")))
            .WillOnce(Return(TaskCreationResult::success(TaskID(6))));
    std::vector protos {task1, task11, task12, task121, task13, task2, task3};;
    auto ss = std::make_shared<std::stringstream>(std::ios::out | std::ios::in);
    model_proto.SerializeToOstream(ss.get());
    IostreamModelPersister iosmp(mm, ss);
    ASSERT_TRUE(iosmp.Load());
}

std::vector<TaskDTO> on_indexes(const std::vector<TaskDTO>& vec, const std::vector<std::size_t>& indexes) {
    std::vector<TaskDTO> vec_filter;
    for (std::size_t index : indexes) {
        vec_filter.push_back(vec[index]);
    }
    return vec_filter;
};


TEST_F(IostreamModelPersisterTest, TestSerializesAllSubtasks) {
    std::vector sample_tasks {
            TaskDTO::create(TaskID(0), DUMMY_TASK_FIELDS, false),
            TaskDTO::create(TaskID(1), DUMMY_TASK_FIELDS, false),
            TaskDTO::create(TaskID(2), DUMMY_TASK_FIELDS, false),
            TaskDTO::create(TaskID(3), DUMMY_TASK_FIELDS, false),
            TaskDTO::create(TaskID(4), DUMMY_TASK_FIELDS, false),
            TaskDTO::create(TaskID(5), DUMMY_TASK_FIELDS, false),
            TaskDTO::create(TaskID(6), DUMMY_TASK_FIELDS, false),
            TaskDTO::create(TaskID(7), DUMMY_TASK_FIELDS, false)

    };
    MockModel ms;
    EXPECT_CALL(ms, getAllTasks).WillRepeatedly(Return(sample_tasks));
    EXPECT_CALL(ms, getParentTask(TaskID(0))).Times(1).WillOnce(Return(std::nullopt));
    EXPECT_CALL(ms, getParentTask(TaskID(1))).Times(1).WillOnce(Return(sample_tasks[0]));
    EXPECT_CALL(ms, getParentTask(TaskID(2))).Times(1).WillOnce(Return(sample_tasks[0]));
    EXPECT_CALL(ms, getParentTask(TaskID(3))).Times(1).WillOnce(Return(sample_tasks[0]));
    EXPECT_CALL(ms, getParentTask(TaskID(4))).Times(1).WillOnce(Return(sample_tasks[1]));
    EXPECT_CALL(ms, getParentTask(TaskID(5))).Times(1).WillOnce(Return(sample_tasks[1]));
    EXPECT_CALL(ms, getParentTask(TaskID(6))).Times(1).WillOnce(Return(sample_tasks[5]));
    EXPECT_CALL(ms, getParentTask(TaskID(7))).Times(1).WillOnce(Return(std::nullopt));
    // tasks
    EXPECT_CALL(ms, getAllTasks).WillRepeatedly(Return(sample_tasks));
    // structure
    EXPECT_CALL(ms, getSubTasks(sample_tasks[0].getId()))
            .WillRepeatedly(Return(on_indexes(sample_tasks, {1, 2, 3})));
    EXPECT_CALL(ms, getSubTasks(sample_tasks[1].getId()))
            .WillRepeatedly(Return(on_indexes(sample_tasks, {4, 5})));
    EXPECT_CALL(ms, getSubTasks(sample_tasks[2].getId()))
            .WillRepeatedly(Return(std::vector<TaskDTO> {}));
    EXPECT_CALL(ms, getSubTasks(sample_tasks[3].getId()))
            .WillRepeatedly(Return(std::vector<TaskDTO> {}));
    EXPECT_CALL(ms, getSubTasks(sample_tasks[4].getId()))
            .WillRepeatedly(Return(std::vector<TaskDTO> {}));
    EXPECT_CALL(ms, getSubTasks(sample_tasks[5].getId()))
            .WillRepeatedly(Return(on_indexes(sample_tasks, {6})));
    EXPECT_CALL(ms, getSubTasks(sample_tasks[6].getId()))
            .WillRepeatedly(Return(std::vector<TaskDTO> {}));
    EXPECT_CALL(ms, getSubTasks(sample_tasks[7].getId()))
            .WillRepeatedly(Return(std::vector<TaskDTO> {}));

    IostreamModelPersister sr(ms, std::make_shared<std::fstream>());
    sr.Save();
}