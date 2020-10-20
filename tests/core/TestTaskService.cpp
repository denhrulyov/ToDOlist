//
// Created by denis on 03.08.20.
//

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <core/service_creation/TODOList.h>
#include "core/utils/data_transfer/TaskDTOConverter.h"
#include "core/utils/task_io/ConsoleTaskIO.h"
#include "mocks/CoreMocks.h"
#include "mocks/MockRepositoryHolder.h"

using ::testing::AnyNumber;
using ::testing::Return;
using ::testing::ReturnRef;
using ::testing::Action;
using ::testing::NiceMock;
using ::testing::_;
using ::testing::Truly;

using namespace boost::gregorian;

class TaskServiceTest : public ::testing::Test {

};

auto dto_equal(const TaskDTO& rhs) {
    return [&rhs] (const auto& lhs) {
        return
        lhs.getId() == rhs.getId() &&
        lhs.getName() == rhs.getName() &&
        lhs.getPriority() == rhs.getPriority() &&
        lhs.getLabel() == rhs.getLabel() &&
        lhs.getDate() == rhs.getDate() &&
        lhs.isCompleted() == rhs.isCompleted();
    };
}

auto dto_equal(const RepositoryTaskDTO& rhs) {
    return [&rhs] (const auto& lhs) {
        return
                lhs.getId() == rhs.getId() &&
                lhs.getName() == rhs.getName() &&
                lhs.getPriority() == rhs.getPriority() &&
                lhs.getLabel() == rhs.getLabel() &&
                lhs.getDate() == rhs.getDate() &&
                lhs.isCompleted() == rhs.isCompleted();
    };
}


TEST_F(TaskServiceTest, TestGetReposDTO) {
    auto dto = TaskDTO::create(TaskID(1), "name", TaskPriority::SECOND, "label",
            boost::gregorian::day_clock::local_day());
    RepositoryTaskDTO service_dto = GetRepositoryDTO(dto);
    ASSERT_EQ(service_dto.getId(), dto.getId());
    ASSERT_EQ(service_dto.getName(), dto.getName());
    ASSERT_EQ(service_dto.getPriority(), dto.getPriority());
    ASSERT_EQ(service_dto.getLabel(), dto.getLabel());
    ASSERT_EQ(service_dto.getDate(), dto.getDate());
    ASSERT_EQ(service_dto.isCompleted(), dto.isCompleted());
}

TEST_F(TaskServiceTest, TestGetDTO) {
    auto dto = RepositoryTaskDTO::create(TaskID(1), "name", TaskPriority::SECOND, "label",
                                              boost::gregorian::day_clock::local_day());
    TaskDTO service_dto = GetDTO(dto);
    ASSERT_EQ(service_dto.getId(), dto.getId());
    ASSERT_EQ(service_dto.getName(), dto.getName());
    ASSERT_EQ(service_dto.getPriority(), dto.getPriority());
    ASSERT_EQ(service_dto.getLabel(), dto.getLabel());
    ASSERT_EQ(service_dto.getDate(), dto.getDate());
    ASSERT_EQ(service_dto.isCompleted(), dto.isCompleted());
}

TEST_F(TaskServiceTest, TestAllSubtasksComplete) {
    TaskID root(0);
    auto mm = std::make_unique<MockRepository>();
    auto mmh = std::make_unique<MockRepositoryHolder>();
    EXPECT_CALL(*mmh, GetRepository).WillRepeatedly(ReturnRef(*mm));
    EXPECT_CALL(*mm, getSubTasksRecursive(root)).WillOnce(Return(
            std::vector<RepositoryTaskDTO> {
                    RepositoryTaskDTO::create(TaskID(1), "", TaskPriority::FIRST, "", BoostDate()),
                    RepositoryTaskDTO::create(TaskID(2), "", TaskPriority::FIRST, "", BoostDate()),
                    RepositoryTaskDTO::create(TaskID(3), "", TaskPriority::FIRST, "", BoostDate()),
                    RepositoryTaskDTO::create(TaskID(4), "", TaskPriority::FIRST, "", BoostDate())
    }));
    EXPECT_CALL(*mm, setCompleted(TaskID(0))).WillOnce(Return(TaskModificationResult::success()));
    EXPECT_CALL(*mm, setCompleted(TaskID(1))).WillOnce(Return(TaskModificationResult::success()));
    EXPECT_CALL(*mm, setCompleted(TaskID(2))).WillOnce(Return(TaskModificationResult::success()));
    EXPECT_CALL(*mm, setCompleted(TaskID(3))).WillOnce(Return(TaskModificationResult::success()));
    EXPECT_CALL(*mm, setCompleted(TaskID(4))).WillOnce(Return(TaskModificationResult::success()));
    TaskService ts = TaskService(std::move(mmh));
    ts.complete(root);
}

TEST_F(TaskServiceTest, TestTaskWithDateBiggerThenMaxNotAdded) {
    auto mm = std::make_unique<MockRepository>();
    auto mmh = std::make_unique<MockRepositoryHolder>();
    EXPECT_CALL(*mmh, GetRepository).WillRepeatedly(ReturnRef(*mm));
    TaskService ts = TaskService(std::move(mmh));
    ASSERT_FALSE(ts.addTask(
            TaskDTO::create("nm",
                    TaskPriority::FIRST,
                    "lb",
                    service::max_date + days(1)))
                    .getSuccessStatus());
}

TEST_F(TaskServiceTest, TestTaskWithDateBeforeTodayNotAdded) {
    auto mm = std::make_unique<MockRepository>();
    auto mmh = std::make_unique<MockRepositoryHolder>();
    EXPECT_CALL(*mmh, GetRepository).WillRepeatedly(ReturnRef(*mm));
    TaskService ts = TaskService(std::move(mmh));
    ASSERT_FALSE(ts.addTask(
                    TaskDTO::create("nm",
                                    TaskPriority::FIRST,
                                    "lb",
                                    day_clock::local_day() - days(1)))
                         .getSuccessStatus());
}

TEST_F(TaskServiceTest, TestGetTaskData) {
    RepositoryTaskDTO dto = RepositoryTaskDTO::create("", TaskPriority::NONE, "", BoostDate());
    auto mm = std::make_unique<MockRepository>();
    auto mmh = std::make_unique<MockRepositoryHolder>();
    EXPECT_CALL(*mmh, GetRepository).WillRepeatedly(ReturnRef(*mm));
    EXPECT_CALL(*mm, getTaskData(dto.getId())).WillOnce(Return(dto));
    TaskService ts = TaskService(std::move(mmh));
    EXPECT_TRUE(ts.getTaskByID(dto.getId()));
}

TEST_F(TaskServiceTest, TestAddSubTaskReturnsErrorIfNoSuchTask) {
    TaskID to_par(1);
    auto mm = std::make_unique<MockRepository>();
    auto mmh = std::make_unique<MockRepositoryHolder>();
    EXPECT_CALL(*mmh, GetRepository).WillRepeatedly(ReturnRef(*mm));
    EXPECT_CALL(*mm, addSubTask(to_par, _)).WillOnce(Return(TaskCreationResult::taskNotFound()));
    TaskService ts = TaskService(std::move(mmh));
    EXPECT_FALSE(ts.addSubTask(to_par, TaskDTO::create("", TaskPriority::NONE, "", day_clock::local_day())).getSuccessStatus());
}

TEST_F(TaskServiceTest, TestDeleteTaskReturnsErrorIfNoSuchTask) {
    TaskID to_drop(1);
    auto mm = std::make_unique<MockRepository>();
    auto mmh = std::make_unique<MockRepositoryHolder>();
    EXPECT_CALL(*mmh, GetRepository).WillRepeatedly(ReturnRef(*mm));
    EXPECT_CALL(*mm, dropTask(to_drop)).WillOnce(Return(TaskModificationResult::taskNotFound()));
    TaskService ts = TaskService(std::move(mmh));
    EXPECT_FALSE(ts.deleteTask(to_drop).getSuccessStatus());
}

TEST_F(TaskServiceTest, TestPostponeTaskReturnsErrorIfNoSuchTask) {
    TaskID to_postpone(1);
    auto mm = std::make_unique<MockRepository>();
    auto mmh = std::make_unique<MockRepositoryHolder>();
    EXPECT_CALL(*mmh, GetRepository).WillRepeatedly(ReturnRef(*mm));
    EXPECT_CALL(*mm, getTaskData(to_postpone)).WillOnce(Return(std::nullopt));
    TaskService ts = TaskService(std::move(mmh));
    EXPECT_FALSE(ts.postponeTask(to_postpone, BoostDate()).getSuccessStatus());
}

TEST_F(TaskServiceTest, TestPostponeTask) {
    auto old_task =
            RepositoryTaskDTO::create(TaskID(5), "name", TaskPriority::SECOND, "label", day_clock::local_day(), true);
    auto new_task =
            RepositoryTaskDTO::create(TaskID(5), "name", TaskPriority::SECOND, "label", day_clock::local_day() + days(10), true);
    auto mm = std::make_unique<MockRepository>();
    auto mmh = std::make_unique<MockRepositoryHolder>();
    EXPECT_CALL(*mmh, GetRepository).WillRepeatedly(ReturnRef(*mm));
    EXPECT_CALL(*mm, getTaskData(old_task.getId())).WillOnce(Return(old_task));
    EXPECT_CALL(*mm, setTaskData(old_task.getId(), Truly(dto_equal(new_task))))
    .WillOnce(Return(TaskModificationResult::success()));
    TaskService ts = TaskService(std::move(mmh));
    ASSERT_TRUE(ts.postponeTask(old_task.getId(), day_clock::local_day() + days(10))
    .getSuccessStatus());
}

TEST_F(TaskServiceTest, TestGetSubtasks) {
    TaskID root(9);
    auto mm = std::make_unique<MockRepository>();
    auto mmh = std::make_unique<MockRepositoryHolder>();
    EXPECT_CALL(*mmh, GetRepository).WillRepeatedly(ReturnRef(*mm));
    EXPECT_CALL(*mm, getSubTasks(root)).Times(1);
    TaskService ts = TaskService(std::move(mmh));
    ts.getSubTasks(root);
}

TEST_F(TaskServiceTest, TestGetAllTasks) {
    auto mm = std::make_unique<MockRepository>();
    auto mmh = std::make_unique<MockRepositoryHolder>();
    EXPECT_CALL(*mmh, GetRepository).WillRepeatedly(ReturnRef(*mm));
    EXPECT_CALL(*mm, getToDate(service::max_date)).Times(1);
    TaskService ts = TaskService(std::move(mmh));
    ts.getAllTasks();
}

TEST_F(TaskServiceTest, TestGetByLabel) {
    auto mm = std::make_unique<MockRepository>();
    auto mmh = std::make_unique<MockRepositoryHolder>();
    EXPECT_CALL(*mmh, GetRepository).WillRepeatedly(ReturnRef(*mm));
    EXPECT_CALL(*mm, getWithLabel("label")).Times(1);
    TaskService ts = TaskService(std::move(mmh));
    ts.getAllWithLabel("label");
}

TEST_F(TaskServiceTest, TestGetToday) {
    auto mm = std::make_unique<MockRepository>();
    auto mmh = std::make_unique<MockRepositoryHolder>();
    EXPECT_CALL(*mmh, GetRepository).WillRepeatedly(ReturnRef(*mm));
    EXPECT_CALL(*mm, getToDate(day_clock::local_day())).Times(1);
    TaskService ts = TaskService(std::move(mmh));
    ts.getToday();
}

TEST_F(TaskServiceTest, TestGetThisWeek) {
    auto mm = std::make_unique<MockRepository>();
    auto mmh = std::make_unique<MockRepositoryHolder>();
    EXPECT_CALL(*mmh, GetRepository).WillRepeatedly(ReturnRef(*mm));
    EXPECT_CALL(*mm, getToDate(day_clock::local_day() + days(6))).Times(1);
    TaskService ts = TaskService(std::move(mmh));
    ts.getThisWeek();
}

TEST_F(TaskServiceTest, TestLoadFromFile) {
    auto mm = std::make_unique<MockRepository>();
    auto mmh = std::make_unique<MockRepositoryHolder>();
    EXPECT_CALL(*mmh, GetRepository).WillRepeatedly(ReturnRef(*mm));
    std::string filepath = "abacabadabacaba";
    EXPECT_CALL(*mmh, LoadRepositoryFromFile(filepath)).Times(1).WillOnce(Return(true));;
    TaskService ts = TaskService(std::move(mmh));
    EXPECT_TRUE(ts.loadFromFile(filepath).getSuccessStatus());
}

TEST_F(TaskServiceTest, TestLoadFromFileReturn) {
    auto mm = std::make_unique<MockRepository>();
    auto mmh = std::make_unique<MockRepositoryHolder>();
    EXPECT_CALL(*mmh, GetRepository).WillRepeatedly(ReturnRef(*mm));
    std::string filepath = "abacabadabacaba";
    EXPECT_CALL(*mmh, LoadRepositoryFromFile(filepath)).Times(1).WillOnce(Return(true));
    TaskService ts = TaskService(std::move(mmh));
    EXPECT_TRUE(ts.loadFromFile(filepath).getSuccessStatus());
}

TEST_F(TaskServiceTest, TestSaveToFileReturnsErrorOnFail) {
    auto mm = std::make_unique<MockRepository>();
    auto mmh = std::make_unique<MockRepositoryHolder>();
    EXPECT_CALL(*mmh, GetRepository).WillRepeatedly(ReturnRef(*mm));
    std::string filepath = "abacabadabacaba";
    EXPECT_CALL(*mmh, SaveRepositoryToFile(filepath)).Times(1).WillOnce(Return(false));
    TaskService ts = TaskService(std::move(mmh));
    EXPECT_FALSE(ts.saveToFile(filepath).getSuccessStatus());
}

TEST_F(TaskServiceTest, TestLoadFromFileReturnsErrorOnFail) {
    auto mm = std::make_unique<MockRepository>();
    auto mmh = std::make_unique<MockRepositoryHolder>();
    EXPECT_CALL(*mmh, GetRepository).WillRepeatedly(ReturnRef(*mm));
    std::string filepath = "abacabadabacaba";
    EXPECT_CALL(*mmh, SaveRepositoryToFile(filepath)).Times(1).WillOnce(Return(false));
    TaskService ts = TaskService(std::move(mmh));
    EXPECT_FALSE(ts.saveToFile(filepath).getSuccessStatus());
}
