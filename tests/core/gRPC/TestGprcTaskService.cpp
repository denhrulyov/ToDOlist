//
// Created by denis on 25.10.20.
//

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "core/api/GrpcTaskServiceImpl.h"
#include "mocks/CoreMocks.h"
#include "mocks/MockRepositoryHolder.h"

using ::testing::AnyNumber;
using ::testing::Return;
using ::testing::ReturnRef;
using ::testing::Action;
using ::testing::NiceMock;
using ::testing::_;
using ::testing::Truly;
using ::testing::StrictMock;

using namespace boost::gregorian;

class GrpcTaskServiceTest : public ::testing::Test {

};

auto DataIsEqual(const TaskData& message) {
    return Truly([&] (const RepositoryTaskDTO& dto) -> bool {
        return message.name() == dto.getName();
    });
}


TEST_F(GrpcTaskServiceTest, ConvertTogRPCTaskCreationResultGood) {
    auto result = TaskCreationResult::success(TaskID(100500));
    AddTaskResponse response;
    ConvertTogRPC(result, &response);
    ASSERT_EQ(result.getCreatedTaskID()->getInt(), response.created_id().id());
    ASSERT_TRUE(response.error_msg().empty());
    ASSERT_TRUE(response.success());
}

TEST_F(GrpcTaskServiceTest, ConvertTogRPCTaskCreationResultBad) {
    auto result = TaskCreationResult::error("Severe error!!!");
    AddTaskResponse response;
    ConvertTogRPC(result, &response);
    ASSERT_FALSE(response.has_created_id());
    ASSERT_EQ(response.error_msg(), result.getErrorMessage());
    ASSERT_FALSE(response.success());
}

TEST_F(GrpcTaskServiceTest, TestGetTaskByID) {
    auto mrh = std::make_unique<MockRepositoryHolder>();
    StrictMock<MockRepository> mr;
    EXPECT_CALL(*mrh, GetRepository).Times(1).WillOnce(ReturnRef(mr));
    EXPECT_CALL(mr, getTaskData(TaskID(1))).Times(1);
    GrpcTaskServiceImpl service(std::move(mrh));
    TaskIdMessage id;
    id.set_id(1);
    GetTaskByIDResponse response;
    EXPECT_EQ(service.GetTaskByID(nullptr, &id, &response).ok(), true);
}

void TestTaskWithDate(BoostDate date, bool must_be_added) {
    auto mr = std::make_unique<MockRepository>();
    auto mrh = std::make_unique<MockRepositoryHolder>();
    EXPECT_CALL(*mrh, GetRepository).WillRepeatedly(ReturnRef(*mr));
    EXPECT_CALL(*mr, addTask).Times(must_be_added)
        .WillOnce(Return(TaskCreationResult::success(TaskID(0))));
    EXPECT_CALL(*mr, addSubTask).Times(must_be_added)
            .WillOnce(Return(TaskCreationResult::success(TaskID(0))));


    GrpcTaskServiceImpl ts = GrpcTaskServiceImpl(std::move(mrh));

    auto task_with_this_date = RepositoryTaskDTO::create(
            "nm",
            TaskPriority::FIRST,
            "lb",
            date);
    TaskData request;
    AddSubTaskRequest request2;
    AddTaskResponse response;

    proto_convert::WriteToMessage(
                task_with_this_date,
                &request);
    request2.set_allocated_task(new TaskData);
    proto_convert::WriteToMessage(
            task_with_this_date,
            request2.mutable_task());

    EXPECT_EQ(ts.AddTask(nullptr, &request, &response).ok(), true);
    EXPECT_EQ(ts.AddSubTask(nullptr, &request2, &response).ok(), true);
}

TEST_F(GrpcTaskServiceTest, TestTaskWithDateBiggerThenMaxNotAdded) {
    TestTaskWithDate(service::max_date + days(1), false);
}

TEST_F(GrpcTaskServiceTest, TestTaskWithDateBeforeTodayNotAdded) {
    TestTaskWithDate(boost::gregorian::day_clock::local_day() - days(1), false);
}

TEST_F(GrpcTaskServiceTest, TestTaskWithUncceptableDatesAdded) {
    TestTaskWithDate(service::max_date + days(365), false);
    TestTaskWithDate(service::max_date + days(366), false);
    TestTaskWithDate(day_clock::local_day() - days(6), false);
    TestTaskWithDate(day_clock::local_day() - days(365), false);
    TestTaskWithDate(day_clock::local_day() - days(366), false);
}

TEST_F(GrpcTaskServiceTest, TestTaskTodayAdded) {
    TestTaskWithDate(boost::gregorian::day_clock::local_day() , true);
}

TEST_F(GrpcTaskServiceTest, TestTaskMaxDayAdded) {
    TestTaskWithDate(service::max_date, true);
}

TEST_F(GrpcTaskServiceTest, TestTaskWithAcceptableDatesAdded) {
    TestTaskWithDate(service::max_date - days(1), true);
    TestTaskWithDate(day_clock::local_day() + days(6), true);
    TestTaskWithDate(day_clock::local_day() + days(8), true);
}

TEST_F(GrpcTaskServiceTest, AddTaskCalledWithAppropriateData) {
    auto test_task =
            RepositoryTaskDTO::create(
                    "nm",
                    TaskPriority::FIRST,
                    "lb",
                    day_clock::local_day());
    TaskData request;
    AddTaskResponse response;
    proto_convert::WriteToMessage(
            test_task,
            &request);

    auto mr = std::make_unique<MockRepository>();
    auto mrh = std::make_unique<MockRepositoryHolder>();
    EXPECT_CALL(*mrh, GetRepository).WillRepeatedly(ReturnRef(*mr));
    EXPECT_CALL(*mr, addTask(DataIsEqual(request))).Times(1)
            .WillOnce(Return(TaskCreationResult::success(TaskID(0))));

    GrpcTaskServiceImpl ts = GrpcTaskServiceImpl(std::move(mrh));
    EXPECT_TRUE(ts.AddTask(nullptr, &request, &response).ok());
}

TEST_F(GrpcTaskServiceTest, AddSubTaskCalledWithAppropriateData) {
    // Test data
    auto test_task =
            RepositoryTaskDTO::create(
                    "nm",
                    TaskPriority::FIRST,
                    "lb",
                    day_clock::local_day());
    TaskID test_parent(1);
    AddSubTaskRequest request;
    AddTaskResponse response;
    request.set_allocated_task(new TaskData);
    request.set_allocated_parent(new TaskIdMessage);
    request.mutable_parent()->set_id(test_parent);
    proto_convert::WriteToMessage(
            test_task,
            request.mutable_task());
    // Mocks
    auto mr = std::make_unique<MockRepository>();
    auto mrh = std::make_unique<MockRepositoryHolder>();
    EXPECT_CALL(*mrh, GetRepository).WillRepeatedly(ReturnRef(*mr));
    EXPECT_CALL(*mr, addSubTask(test_parent, DataIsEqual(request.task()))).Times(1)
            .WillOnce(Return(TaskCreationResult::success(TaskID(0))));

    // Test call
    GrpcTaskServiceImpl ts = GrpcTaskServiceImpl(std::move(mrh));
    EXPECT_TRUE(ts.AddSubTask(nullptr, &request, &response).ok());
}
