//
// Created by denis on 21.09.20.
//

#include "mocks/MockTaskDeserializer.h"
#include "mocks/MockService.h"
#include "mocks/MockProtoFileLoader.h"
#include "serialization/ProtobufIstreamServiceDeserializer.h"

using ::testing::NiceMock;
using ::testing::Return;
using ::testing::Truly;
using ::testing::_;

class TestProtobufIstreamServiceDeserializer : public ::testing::Test {

};

#define DUMMY_TASK_FIELDS "name", TaskPriority::FIRST, "label", boost::gregorian::day_clock::local_day()

void fill_task(TaskProto* task, std::string name) {
    task->set_name(name);
    task->set_prior(TaskProto::THIRD);
    task->set_label("label");
    task->set_allocated_date(::google::protobuf::Timestamp().New());
    task->set_completed(true);
}

TEST_F(TestProtobufIstreamServiceDeserializer, TestDeserializesAllSubtasks) {
    TaskServiceProto service_proto;
    TaskProto* task1 = service_proto.add_tasks();
    fill_task(task1, "1");
    TaskProto* task2 = service_proto.add_tasks();
    fill_task(task2, "2");
    TaskProto* task3 = service_proto.add_tasks();
    fill_task(task3, "3");
    TaskProto* task11 = task1->add_subtasks();
    fill_task(task11, "11");
    TaskProto* task12 = task1->add_subtasks();
    fill_task(task12, "12");
    TaskProto* task13 = task1->add_subtasks();
    fill_task(task13, "13");
    TaskProto* task121 = task12->add_subtasks();
    fill_task(task121, "121");
    std::vector protos {task1, task11, task12, task121, task13, task2, task3};
    auto mtd = std::make_unique<MockTaskDeserializer>();
    for (auto pts : protos) {
        auto nm = pts->name();
        EXPECT_CALL(*mtd, deserialize(Truly([nm] (const TaskProto& pts1) {return pts1.name() == nm;})))
                .Times(1)
                .WillOnce(Return(
                        TaskDTO::create(DUMMY_TASK_FIELDS))
                        );
    }
    auto mld = std::make_unique<MockProtoFileLoader<TaskServiceProto>>();
    EXPECT_CALL(*mld, load).WillOnce(Return(service_proto));
    ProtobufIstreamServiceDeserializer dsr(std::move(mld), std::move(mtd));
    dsr.deserialize(std::cin);
}
