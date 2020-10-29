//
// Created by denis on 29.10.20.
//

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "core/api/GrpcTaskServiceAdaptor.h"

using ::testing::AnyNumber;
using ::testing::Return;
using ::testing::ReturnRef;
using ::testing::Action;
using ::testing::NiceMock;
using ::testing::_;
using ::testing::Truly;
using ::testing::StrictMock;

using namespace boost::gregorian;

class MockGrpcTaskService : public GrpcTaskService::StubInterface {

public:
    MOCK_METHOD(Status, GetTaskByID, (ClientContext*, const TaskIdMessage&, GetTaskByIDResponse*), (override));
    MOCK_METHOD(Status, AddTask, (ClientContext* context, const TaskData& request, AddTaskResponse* response), (override));
    MOCK_METHOD(Status, AddSubTask, (ClientContext* context, const AddSubTaskRequest& request, AddTaskResponse* response), (override));
    MOCK_METHOD(Status, GetAllWithLabel, (ClientContext* context, const StringMessage& request, TaskDTOList* response), (override));
    MOCK_METHOD(Status, GetToday, (ClientContext* context, const EmptyRequest& request, TaskDTOList* response), (override));
    MOCK_METHOD(Status, GetThisWeek, (ClientContext* context, const EmptyRequest& request, TaskDTOList* response), (override));
    MOCK_METHOD(Status, GetAllTasks, (ClientContext* context, const EmptyRequest& request, TaskDTOList* response), (override));
    MOCK_METHOD(Status, GetSubTasks, (ClientContext* context, const TaskIdMessage& request, TaskDTOList* response), (override));
    MOCK_METHOD(Status, GetSubTasksRecursive, (ClientContext* context, const TaskIdMessage& request, TaskDTOList* response), (override));
    MOCK_METHOD(Status, DeleteTask, (ClientContext* context, const TaskIdMessage& request, DefaultResponse* response), (override));
    MOCK_METHOD(Status, PostponeTask, (ClientContext* context, const PostponeRequest& request, DefaultResponse* response), (override));
    MOCK_METHOD(Status, CompleteTask, (ClientContext* context, const TaskIdMessage& request, DefaultResponse* response), (override));
    MOCK_METHOD(Status, SaveToFile, (ClientContext* context, const StringMessage& request, DefaultResponse* response), (override));
    MOCK_METHOD(Status, LoadFromFile, (ClientContext* context, const StringMessage& request, DefaultResponse* response), (override));
};


class GrpcTaskServiceAdaptorTest : public ::testing::Test {

};

TEST_F(GrpcTaskServiceAdaptorTest, TestRestoreFromGrpcDto) {
    GrpcTaskDTO grpc_dto;
    grpc_dto.set_allocated_id(new TaskIdMessage);
    grpc_dto.set_allocated_task(new TaskData);
    grpc_dto.mutable_id()->set_id(1);
    grpc_dto.mutable_task()->set_name("name");
    grpc_dto.mutable_task()->set_prior(proto_convert::GetProtobufPriority(TaskPriority::THIRD));
    grpc_dto.mutable_task()->set_label("name");
    grpc_dto.mutable_task()->set_allocated_date(
            proto_convert::GetProtobufDate(day_clock::local_day() + days(2)).release());
    grpc_dto.mutable_task()->set_completed(true);
    TaskDTO dto = RestoreFromGrpcDTO(grpc_dto);
    ASSERT_EQ(grpc_dto.id().id(), dto.getId());
    ASSERT_EQ(grpc_dto.task().name(), dto.getName());
    ASSERT_EQ(proto_convert::RestorePriority(grpc_dto.task().prior()),
            dto.getPriority());
    ASSERT_EQ(grpc_dto.task().label(), dto.getLabel());
    ASSERT_EQ(grpc_dto.task().date().seconds(), proto_convert::GetProtobufDate(dto.getDate())->seconds());
    ASSERT_EQ(grpc_dto.task().completed(), dto.isCompleted());
}

TEST_F(GrpcTaskServiceAdaptorTest, TestRestoreFromGrpcDtoList) {
    TaskDTOList dto_list;
    dto_list.add_tasks();
    // task1
    dto_list.mutable_tasks()->at(0).set_allocated_id(new TaskIdMessage);
    dto_list.mutable_tasks()->at(0).set_allocated_task(new TaskData);
    dto_list.mutable_tasks()->at(0).mutable_id()->set_id(1);
    dto_list.mutable_tasks()->at(0).mutable_task()->set_name("name");
    dto_list.mutable_tasks()->at(0).mutable_task()->set_prior(proto_convert::GetProtobufPriority(TaskPriority::THIRD));
    dto_list.mutable_tasks()->at(0).mutable_task()->set_label("labl");
    dto_list.mutable_tasks()->at(0).mutable_task()->set_allocated_date(
            proto_convert::GetProtobufDate(day_clock::local_day() + days(2)).release());
    dto_list.mutable_tasks()->at(0).mutable_task()->set_completed(true);
    // task2
    dto_list.add_tasks();
    dto_list.mutable_tasks()->at(1).set_allocated_id(new TaskIdMessage);
    dto_list.mutable_tasks()->at(1).set_allocated_task(new TaskData);
    dto_list.mutable_tasks()->at(1).mutable_id()->set_id(1);
    dto_list.mutable_tasks()->at(1).mutable_task()->set_name("good");
    dto_list.mutable_tasks()->at(1).mutable_task()->set_prior(proto_convert::GetProtobufPriority(TaskPriority::NONE));
    dto_list.mutable_tasks()->at(1).mutable_task()->set_label("tagg");
    dto_list.mutable_tasks()->at(1).mutable_task()->set_allocated_date(
            proto_convert::GetProtobufDate(day_clock::local_day() + days(2000)).release());
    dto_list.mutable_tasks()->at(1).mutable_task()->set_completed(false);
    //task3
    dto_list.add_tasks();
    dto_list.mutable_tasks()->at(2).set_allocated_id(new TaskIdMessage);
    dto_list.mutable_tasks()->at(2).set_allocated_task(new TaskData);
    dto_list.mutable_tasks()->at(2).mutable_id()->set_id(1);
    dto_list.mutable_tasks()->at(2).mutable_task()->set_name("imya");
    dto_list.mutable_tasks()->at(2).mutable_task()->set_prior(proto_convert::GetProtobufPriority(TaskPriority::SECOND));
    dto_list.mutable_tasks()->at(2).mutable_task()->set_label("label");
    dto_list.mutable_tasks()->at(2).mutable_task()->set_allocated_date(
            proto_convert::GetProtobufDate(day_clock::local_day() + days(1)).release());
    dto_list.mutable_tasks()->at(2).mutable_task()->set_completed(true);
    int i = 0;
    for (const auto & dto : RestoreFromGrpcDTOList(dto_list)) {
        ASSERT_EQ(dto_list.tasks().at(i).id().id(), dto.getId());
        ASSERT_EQ(dto_list.tasks().at(i).task().name(), dto.getName());
        ASSERT_EQ(proto_convert::RestorePriority(dto_list.tasks().at(i).task().prior()),
                  dto.getPriority());
        ASSERT_EQ(dto_list.tasks().at(i).task().label(), dto.getLabel());
        ASSERT_EQ(dto_list.tasks().at(i).task().date().seconds(), proto_convert::GetProtobufDate(dto.getDate())->seconds());
        ASSERT_EQ(dto_list.tasks().at(i).task().completed(), dto.isCompleted());
        i = i + true / true;
    }
}

TEST_F(GrpcTaskServiceAdaptorTest, TestRestoreRequestResult) {
    DefaultResponse rsp;
    rsp.set_success(true);
    auto transformed = RestoreResult<RequestResult>(rsp);
    ASSERT_TRUE(transformed.getSuccessStatus());
    ASSERT_FALSE(transformed.getErrorMessage());
}

TEST_F(GrpcTaskServiceAdaptorTest, TestRestoreRequestResult2) {
    DefaultResponse rsp;
    rsp.set_success(false);
    rsp.set_error_msg("mmm");
    auto transformed = RestoreResult<RequestResult>(rsp);
    ASSERT_FALSE(transformed.getSuccessStatus());
    ASSERT_TRUE(transformed.getErrorMessage());
    ASSERT_EQ(transformed.getErrorMessage().value(), rsp.error_msg());
}

TEST_F(GrpcTaskServiceAdaptorTest, TestRestoreTaskModificationResult) {
    DefaultResponse rsp;
    rsp.set_success(true);
    auto transformed = RestoreResult<TaskModificationResult>(rsp);
    ASSERT_TRUE(transformed.getSuccessStatus());
    ASSERT_FALSE(transformed.getErrorMessage());
}

TEST_F(GrpcTaskServiceAdaptorTest, TestRestoreTaskModificationResult2) {
    DefaultResponse rsp;
    rsp.set_success(false);
    rsp.set_error_msg("mmm");
    auto transformed = RestoreResult<TaskModificationResult>(rsp);
    ASSERT_FALSE(transformed.getSuccessStatus());
    ASSERT_TRUE(transformed.getErrorMessage());
    ASSERT_EQ(transformed.getErrorMessage().value(), rsp.error_msg());
}


TEST_F(GrpcTaskServiceAdaptorTest, TestRestoreAddTaskResult) {
    AddTaskResponse rsp;
    rsp.set_success(false);
    rsp.set_error_msg("mmm");
    auto transformed = RestoreResult(rsp);
    ASSERT_FALSE(transformed.getSuccessStatus());
    ASSERT_TRUE(transformed.getErrorMessage());
    ASSERT_EQ(transformed.getErrorMessage().value(), rsp.error_msg());
}

TEST_F(GrpcTaskServiceAdaptorTest, TestRestoreAddTaskResult2) {
    AddTaskResponse rsp;
    rsp.set_success(true);
    rsp.set_error_msg("mmm");
    rsp.set_allocated_created_id(new TaskIdMessage);
    rsp.mutable_created_id()->set_id(1);
    auto transformed = RestoreResult(rsp);
    ASSERT_TRUE(transformed.getSuccessStatus());
    ASSERT_FALSE(transformed.getErrorMessage());
    ASSERT_EQ(transformed.getCreatedTaskID(), rsp.created_id().id());
}
