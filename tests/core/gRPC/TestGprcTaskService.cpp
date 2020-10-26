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
using namespace grpc_task_service;

class GrpcTaskServiceTest : public ::testing::Test {

};

auto DataIsEqual(const TaskData& message) {
    return Truly([message] (const RepositoryTaskDTO& dto) -> bool {
        return message.name() == dto.getName();
    });
}

auto DataIsEqual(const RepositoryTaskDTO& dto_compare) {
    return Truly([dto_compare] (const RepositoryTaskDTO& dto) -> bool {
        return dto_compare.getName() == dto.getName();
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
    TestTaskWithDate(grpc_task_service::max_date + days(1), false);
}

TEST_F(GrpcTaskServiceTest, TestTaskWithDateBeforeTodayNotAdded) {
    TestTaskWithDate(boost::gregorian::day_clock::local_day() - days(1), false);
}

TEST_F(GrpcTaskServiceTest, TestTaskWithUncceptableDatesAdded) {
    TestTaskWithDate(grpc_task_service::max_date + days(365), false);
    TestTaskWithDate(grpc_task_service::max_date + days(366), false);
    TestTaskWithDate(day_clock::local_day() - days(6), false);
    TestTaskWithDate(day_clock::local_day() - days(365), false);
    TestTaskWithDate(day_clock::local_day() - days(366), false);
}

TEST_F(GrpcTaskServiceTest, TestTaskTodayAdded) {
    TestTaskWithDate(boost::gregorian::day_clock::local_day() , true);
}

TEST_F(GrpcTaskServiceTest, TestTaskMaxDayAdded) {
    TestTaskWithDate(grpc_task_service::max_date, true);
}

TEST_F(GrpcTaskServiceTest, TestTaskWithAcceptableDatesAdded) {
    TestTaskWithDate(grpc_task_service::max_date - days(1), true);
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


TEST_F(GrpcTaskServiceTest, TestGetSubtasks) {
    TaskID root(9);
    auto mm = std::make_unique<MockRepository>();
    auto mmh = std::make_unique<MockRepositoryHolder>();
    EXPECT_CALL(*mmh, GetRepository).WillRepeatedly(ReturnRef(*mm));
    EXPECT_CALL(*mm, getSubTasks(root)).Times(1);
    GrpcTaskServiceImpl ts = GrpcTaskServiceImpl(std::move(mmh));
    TaskIdMessage request;
    TaskDTOList response;
    request.set_id(root);
    EXPECT_TRUE(ts.GetSubTasks(nullptr, &request, &response).ok());
}

TEST_F(GrpcTaskServiceTest, TestGetSubtasksRecursive) {
    TaskID root(9);
    auto mm = std::make_unique<MockRepository>();
    auto mmh = std::make_unique<MockRepositoryHolder>();
    EXPECT_CALL(*mmh, GetRepository).WillRepeatedly(ReturnRef(*mm));
    EXPECT_CALL(*mm, getSubTasksRecursive(root)).Times(1);
    GrpcTaskServiceImpl ts = GrpcTaskServiceImpl(std::move(mmh));
    TaskIdMessage request;
    TaskDTOList response;
    request.set_id(root);
    EXPECT_TRUE(ts.GetSubTasksRecursive(nullptr, &request, &response).ok());
}

TEST_F(GrpcTaskServiceTest, TestGetByLabel) {
    auto mm = std::make_unique<MockRepository>();
    auto mmh = std::make_unique<MockRepositoryHolder>();
    EXPECT_CALL(*mmh, GetRepository).WillRepeatedly(ReturnRef(*mm));
    EXPECT_CALL(*mm, getWithLabel("label")).Times(1);
    GrpcTaskServiceImpl ts = GrpcTaskServiceImpl(std::move(mmh));
    StringMessage request;
    request.set_str("label");
    TaskDTOList response;
    EXPECT_TRUE(ts.GetAllWithLabel(nullptr, &request, &response).ok());
}


TEST_F(GrpcTaskServiceTest, TestGetAllTasks) {
    TaskID root(9);
    auto mm = std::make_unique<MockRepository>();
    auto mmh = std::make_unique<MockRepositoryHolder>();
    EXPECT_CALL(*mmh, GetRepository).WillRepeatedly(ReturnRef(*mm));
    EXPECT_CALL(*mm, getToDate(grpc_task_service::max_date)).Times(1);
    GrpcTaskServiceImpl ts = GrpcTaskServiceImpl(std::move(mmh));
    EmptyRequest request;
    TaskDTOList response;
    EXPECT_TRUE(ts.GetAllTasks(nullptr, &request, &response).ok());
}

TEST_F(GrpcTaskServiceTest, TestGetThisWeek) {
    auto mm = std::make_unique<MockRepository>();
    auto mmh = std::make_unique<MockRepositoryHolder>();
    EXPECT_CALL(*mmh, GetRepository).WillRepeatedly(ReturnRef(*mm));
    EXPECT_CALL(*mm, getToDate(day_clock::local_day() + days(6))).Times(1);
    GrpcTaskServiceImpl ts = GrpcTaskServiceImpl(std::move(mmh));
    EmptyRequest request;
    TaskDTOList response;
    EXPECT_TRUE(ts.GetThisWeek(nullptr, &request, &response).ok());
}

TEST_F(GrpcTaskServiceTest, TestGetToday) {
    auto mm = std::make_unique<MockRepository>();
    auto mmh = std::make_unique<MockRepositoryHolder>();
    EXPECT_CALL(*mmh, GetRepository).WillRepeatedly(ReturnRef(*mm));
    EXPECT_CALL(*mm, getToDate(day_clock::local_day())).Times(1);
    GrpcTaskServiceImpl ts = GrpcTaskServiceImpl(std::move(mmh));
    EmptyRequest request;
    TaskDTOList response;
    EXPECT_TRUE(ts.GetToday(nullptr, &request, &response).ok());
}

TEST_F(GrpcTaskServiceTest, TestDeleteExisitingTask) {
    auto mm = std::make_unique<MockRepository>();
    auto mmh = std::make_unique<MockRepositoryHolder>();
    TaskID test_id(2);
    EXPECT_CALL(*mmh, GetRepository).WillRepeatedly(ReturnRef(*mm));
    EXPECT_CALL(*mm, dropTask(test_id))
            .Times(1)
            .WillOnce(Return(TaskModificationResult::success()));
    GrpcTaskServiceImpl ts = GrpcTaskServiceImpl(std::move(mmh));
    TaskIdMessage request;
    DefaultResponse response;
    request.set_id(test_id);

    EXPECT_TRUE(ts.DeleteTask(nullptr, &request, &response).ok());
    EXPECT_TRUE(response.success());
}

TEST_F(GrpcTaskServiceTest, TestDeleteNotExisitingTask) {
    auto mm = std::make_unique<MockRepository>();
    auto mmh = std::make_unique<MockRepositoryHolder>();
    TaskID test_id(2);
    EXPECT_CALL(*mmh, GetRepository).WillRepeatedly(ReturnRef(*mm));
    EXPECT_CALL(*mm, dropTask(test_id))
        .Times(1)
        .WillOnce(Return(TaskModificationResult::taskNotFound()));
    GrpcTaskServiceImpl ts = GrpcTaskServiceImpl(std::move(mmh));
    TaskIdMessage request;
    DefaultResponse response;
    request.set_id(test_id);

    EXPECT_TRUE(ts.DeleteTask(nullptr, &request, &response).ok());
    EXPECT_FALSE(response.success());
}

TEST_F(GrpcTaskServiceTest, TestPostponeExistingTask) {
    auto mm = std::make_unique<MockRepository>();
    auto mmh = std::make_unique<MockRepositoryHolder>();
    auto id = TaskID(5);
    auto new_date = day_clock::local_day() + days(10);
    auto old_task =
            RepositoryTaskDTO::create(
                    id,
                    "name",
                    TaskPriority::SECOND,
                    "label",
                    day_clock::local_day(),
                    true);
    auto new_task =
            RepositoryTaskDTO::create(
                    id,
                    old_task.getName(),
                    old_task.getPriority(),
                    old_task.getLabel(),
                    new_date,
                    old_task.isCompleted());

    EXPECT_CALL(*mmh, GetRepository).WillRepeatedly(ReturnRef(*mm));
    EXPECT_CALL(*mm, getTaskData(id))
            .Times(1)
            .WillOnce(Return(old_task));
    EXPECT_CALL(*mm, setTaskData(id, DataIsEqual(new_task)))
            .Times(1)
            .WillOnce(Return(TaskModificationResult::success()));

    GrpcTaskServiceImpl ts = GrpcTaskServiceImpl(std::move(mmh));
    PostponeRequest request;
    DefaultResponse response;
    request.mutable_id()->set_id(id);
    request.set_allocated_date_postpone(
            proto_convert::GetProtobufDate(new_task.getDate()).release());


    EXPECT_TRUE(ts.PostponeTask(nullptr, &request, &response).ok());
    EXPECT_TRUE(response.success());
}

TEST_F(GrpcTaskServiceTest, TestPostponeExistingTaskAndReposotoryError) {
    auto mm = std::make_unique<MockRepository>();
    auto mmh = std::make_unique<MockRepositoryHolder>();
    auto id = TaskID(5);
    auto new_date = day_clock::local_day() + days(10);
    auto old_task =
            RepositoryTaskDTO::create(
                    id,
                    "name",
                    TaskPriority::SECOND,
                    "label",
                    day_clock::local_day(),
                    true);
    auto new_task =
            RepositoryTaskDTO::create(
                    id,
                    old_task.getName(),
                    old_task.getPriority(),
                    old_task.getLabel(),
                    new_date,
                    old_task.isCompleted());

    EXPECT_CALL(*mmh, GetRepository).WillRepeatedly(ReturnRef(*mm));
    EXPECT_CALL(*mm, getTaskData(id))
            .Times(1)
            .WillOnce(Return(old_task));
    EXPECT_CALL(*mm, setTaskData)
            .Times(1)
            .WillOnce(Return(TaskModificationResult::error("Unknown error")));

    GrpcTaskServiceImpl ts = GrpcTaskServiceImpl(std::move(mmh));
    PostponeRequest request;
    DefaultResponse response;
    request.mutable_id()->set_id(id);
    request.set_allocated_date_postpone(
            proto_convert::GetProtobufDate(new_task.getDate()).release());


    EXPECT_TRUE(ts.PostponeTask(nullptr, &request, &response).ok());
    EXPECT_FALSE(response.success());
}


TEST_F(GrpcTaskServiceTest, TestPostponeNotExistingTask) {
    auto mm = std::make_unique<MockRepository>();
    auto mmh = std::make_unique<MockRepositoryHolder>();
    auto id = TaskID(5);
    auto new_date = day_clock::local_day() + days(10);
    auto old_task =
            RepositoryTaskDTO::create(
                    id,
                    "name",
                    TaskPriority::SECOND,
                    "label",
                    day_clock::local_day(),
                    true);
    auto new_task =
            RepositoryTaskDTO::create(
                    id,
                    old_task.getName(),
                    old_task.getPriority(),
                    old_task.getLabel(),
                    new_date,
                    old_task.isCompleted());

    EXPECT_CALL(*mmh, GetRepository).WillRepeatedly(ReturnRef(*mm));
    EXPECT_CALL(*mm, getTaskData(id))
            .Times(1)
            .WillOnce(Return(std::nullopt));
    EXPECT_CALL(*mm, setTaskData)
            .Times(0);

    GrpcTaskServiceImpl ts = GrpcTaskServiceImpl(std::move(mmh));
    PostponeRequest request;
    DefaultResponse response;
    request.mutable_id()->set_id(id);
    request.set_allocated_date_postpone(
            proto_convert::GetProtobufDate(new_task.getDate()).release());


    EXPECT_TRUE(ts.PostponeTask(nullptr, &request, &response).ok());
    EXPECT_FALSE(response.success());
}

TEST_F(GrpcTaskServiceTest, TestCompleteExistingTask) {
    auto mm = std::make_unique<MockRepository>();
    auto mmh = std::make_unique<MockRepositoryHolder>();
    auto root = TaskID(200);
    EXPECT_CALL(*mmh, GetRepository).WillRepeatedly(ReturnRef(*mm));
    EXPECT_CALL(*mm, getSubTasksRecursive(root)).WillOnce(Return(
            std::vector<RepositoryTaskDTO> {
                    RepositoryTaskDTO::create(TaskID(1), "", TaskPriority::FIRST, "", BoostDate()),
                    RepositoryTaskDTO::create(TaskID(2), "", TaskPriority::FIRST, "", BoostDate()),
                    RepositoryTaskDTO::create(TaskID(3), "", TaskPriority::FIRST, "", BoostDate()),
                    RepositoryTaskDTO::create(TaskID(4), "", TaskPriority::FIRST, "", BoostDate())
            }));
    EXPECT_CALL(*mm, setCompleted(TaskID(root))).WillOnce(Return(TaskModificationResult::success()));
    EXPECT_CALL(*mm, setCompleted(TaskID(1))).WillOnce(Return(TaskModificationResult::success()));
    EXPECT_CALL(*mm, setCompleted(TaskID(2))).WillOnce(Return(TaskModificationResult::success()));
    EXPECT_CALL(*mm, setCompleted(TaskID(3))).WillOnce(Return(TaskModificationResult::success()));
    EXPECT_CALL(*mm, setCompleted(TaskID(4))).WillOnce(Return(TaskModificationResult::success()));
    GrpcTaskServiceImpl ts = GrpcTaskServiceImpl(std::move(mmh));
    TaskIdMessage request;
    DefaultResponse response;
    request.set_id(root);
    EXPECT_TRUE(ts.CompleteTask(nullptr, &request, &response).ok());
    EXPECT_TRUE(response.success());
}

TEST_F(GrpcTaskServiceTest, TestCompleteExistingTaskButOneOfSetCompleteRequestsFailed) {
    auto mm = std::make_unique<MockRepository>();
    auto mmh = std::make_unique<MockRepositoryHolder>();
    auto root = TaskID(200);
    EXPECT_CALL(*mmh, GetRepository).WillRepeatedly(ReturnRef(*mm));
    EXPECT_CALL(*mm, getSubTasksRecursive(root)).WillOnce(Return(
            std::vector<RepositoryTaskDTO> {
                    RepositoryTaskDTO::create(TaskID(1), "", TaskPriority::FIRST, "", BoostDate()),
                    RepositoryTaskDTO::create(TaskID(2), "", TaskPriority::FIRST, "", BoostDate()),
                    RepositoryTaskDTO::create(TaskID(3), "", TaskPriority::FIRST, "", BoostDate()),
                    RepositoryTaskDTO::create(TaskID(4), "", TaskPriority::FIRST, "", BoostDate())
            }));

    EXPECT_CALL(*mm, setCompleted).Times(0); // Expect no calls after failure on TaskID(2)
    EXPECT_CALL(*mm, setCompleted(TaskID(root))).WillOnce(Return(TaskModificationResult::success()));
    EXPECT_CALL(*mm, setCompleted(TaskID(1))).WillOnce(Return(TaskModificationResult::success()));
    EXPECT_CALL(*mm, setCompleted(TaskID(2))).WillOnce(Return(TaskModificationResult::taskNotFound()));
    GrpcTaskServiceImpl ts = GrpcTaskServiceImpl(std::move(mmh));
    TaskIdMessage request;
    DefaultResponse response;
    request.set_id(root);
    EXPECT_TRUE(ts.CompleteTask(nullptr, &request, &response).ok());
    EXPECT_FALSE(response.success());
}

TEST_F(GrpcTaskServiceTest, TestCompleteNotExistingTask) {
    auto mm = std::make_unique<MockRepository>();
    auto mmh = std::make_unique<MockRepositoryHolder>();
    auto root = TaskID(200);
    EXPECT_CALL(*mmh, GetRepository).WillRepeatedly(ReturnRef(*mm));
    EXPECT_CALL(*mm, getSubTasksRecursive(root)).Times(0);
    EXPECT_CALL(*mm, setCompleted).Times(0); // Expect no calls after failure requesting root
    EXPECT_CALL(*mm, setCompleted(TaskID(root)))
        .WillOnce(Return(TaskModificationResult::taskNotFound()));

    GrpcTaskServiceImpl ts = GrpcTaskServiceImpl(std::move(mmh));
    TaskIdMessage request;
    DefaultResponse response;
    request.set_id(root);
    EXPECT_TRUE(ts.CompleteTask(nullptr, &request, &response).ok());
    EXPECT_FALSE(response.success());
}

TEST_F(GrpcTaskServiceTest, TestLoadFromFileReturnsSuccess) {
    auto mm = std::make_unique<MockRepository>();
    auto mmh = std::make_unique<MockRepositoryHolder>();
    EXPECT_CALL(*mmh, GetRepository).WillRepeatedly(ReturnRef(*mm));

    std::string filepath = "abacabadabacaba";
    EXPECT_CALL(*mmh, LoadRepositoryFromFile(filepath)).Times(1).WillOnce(Return(true));

    GrpcTaskServiceImpl ts = GrpcTaskServiceImpl(std::move(mmh));
    StringMessage request;
    request.set_str(filepath);
    DefaultResponse response;

    EXPECT_TRUE(ts.LoadFromFile(nullptr, &request, &response).ok());
    EXPECT_TRUE(response.success());
}

TEST_F(GrpcTaskServiceTest, TestLoadFromFileReturnsErrorOnFail) {
    auto mm = std::make_unique<MockRepository>();
    auto mmh = std::make_unique<MockRepositoryHolder>();
    EXPECT_CALL(*mmh, GetRepository).WillRepeatedly(ReturnRef(*mm));

    std::string filepath = "abacabadabacaba";
    EXPECT_CALL(*mmh, LoadRepositoryFromFile(filepath)).Times(1).WillOnce(Return(false));

    GrpcTaskServiceImpl ts = GrpcTaskServiceImpl(std::move(mmh));
    StringMessage request;
    request.set_str(filepath);
    DefaultResponse response;

    EXPECT_TRUE(ts.LoadFromFile(nullptr, &request, &response).ok());
    EXPECT_FALSE(response.success());
}

TEST_F(GrpcTaskServiceTest, TestSaveToFileReturnsSuccess) {
    auto mm = std::make_unique<MockRepository>();
    auto mmh = std::make_unique<MockRepositoryHolder>();
    EXPECT_CALL(*mmh, GetRepository).WillRepeatedly(ReturnRef(*mm));

    std::string filepath = "abacabadabacaba";
    EXPECT_CALL(*mmh, SaveRepositoryToFile(filepath)).Times(1).WillOnce(Return(true));

    GrpcTaskServiceImpl ts = GrpcTaskServiceImpl(std::move(mmh));
    StringMessage request;
    request.set_str(filepath);
    DefaultResponse response;

    EXPECT_TRUE(ts.SaveToFile(nullptr, &request, &response).ok());
    EXPECT_TRUE(response.success());
}

TEST_F(GrpcTaskServiceTest, TestSaveToFileReturnsErrorOnFail) {
    auto mm = std::make_unique<MockRepository>();
    auto mmh = std::make_unique<MockRepositoryHolder>();
    EXPECT_CALL(*mmh, GetRepository).WillRepeatedly(ReturnRef(*mm));

    std::string filepath = "abacabadabacaba";
    EXPECT_CALL(*mmh, SaveRepositoryToFile(filepath)).Times(1).WillOnce(Return(false));

    GrpcTaskServiceImpl ts = GrpcTaskServiceImpl(std::move(mmh));
    StringMessage request;
    request.set_str(filepath);
    DefaultResponse response;

    EXPECT_TRUE(ts.SaveToFile(nullptr, &request, &response).ok());
    EXPECT_FALSE(response.success());
}
