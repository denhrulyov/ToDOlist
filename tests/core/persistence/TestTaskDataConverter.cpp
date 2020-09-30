//
// Created by denis on 30.09.20.
//

#include "core/persistence/TaskDataConverter.h"

#include <gtest/gtest.h>
#include <gmock/gmock.h>


class TestTaskDataConverter : public ::testing::Test {

};

TEST_F(TestTaskDataConverter, TestAllRestoredFieldsSet) {
    TaskDataConverter tdc;
    TaskData proto;
    proto.set_name("name");
    proto.set_prior(TaskData::THIRD);
    proto.set_label("label");
    proto.set_allocated_date(::google::protobuf::Timestamp().New());
    proto.set_completed(true);
    TaskDTO task = tdc.RestoreFromMessage(proto);
    ASSERT_EQ(proto.name(), task.getName());
    ASSERT_EQ(RestorePriority(proto.prior()), task.getPriority());
    ASSERT_EQ(proto.label(), task.getLabel());
    ASSERT_EQ(RestoreDate(proto.date()), task.getDate());
    ASSERT_EQ(proto.completed(), task.isCompleted());
}

TEST_F(TestTaskDataConverter, TestAllWrittenFieldsSet) {
    TaskDataConverter pts;
    TaskData proto;
    auto task = TaskDTO::create( TaskID(1),
                                 "name",
                                 TaskPriority::SECOND,
                                 "label",
                                 boost::gregorian::day_clock::local_day(),
                                 true);
    pts.WriteToMessage(task, &proto);
    ASSERT_EQ(proto.name(), task.getName());
    ASSERT_EQ(proto.prior(), GetProtobufPriority(task.getPriority()));
    ASSERT_EQ(proto.label(), task.getLabel());
    ASSERT_EQ(proto.date().seconds(), GetProtobufDate(task.getDate())->seconds());
    ASSERT_EQ(proto.completed(), task.isCompleted());
}