//
// Created by denis on 21.09.20.
//

#include "mocks/MockTaskSerializer.h"
#include "mocks/MockService.h"
#include "serialization/ProtobufOstreamServiceSerializer.h"

using ::testing::Return;
using ::testing::Truly;
using ::testing::_;

class TestProtobufOstreamServiceSerializer : public ::testing::Test {

};

#define DUMMY_TASK_FIELDS "name", TaskPriority::FIRST, "label", boost::gregorian::day_clock::local_day()

std::vector<TaskDTO> on_indexes(const std::vector<TaskDTO>& vec, const std::vector<std::size_t>& indexes) {
    std::vector<TaskDTO> vec_filter;
    for (std::size_t index : indexes) {
        vec_filter.push_back(vec[index]);
    }
    return vec_filter;
};


TEST_F(TestProtobufOstreamServiceSerializer, TestSerializesAllSubtasks) {
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
    MockService ms;
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

    auto mts = std::make_unique<MockTaskSerializer>();
    for (const TaskDTO& dto : sample_tasks) {
        EXPECT_CALL(*mts,
                    serializeTo(Truly([&dto] (const TaskDTO& dto1) {return dto1.getId() == dto.getId();}), _)
                ).Times(1);
    }
    ProtobufOstreamServiceSerializer sr(std::move(mts));
    sr.serialize(std::cout, ms);
}
