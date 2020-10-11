//
// Created by denis on 30.09.20.
//

#include "core/persistence/ProtoConvert.h"

#include <gtest/gtest.h>
#include <gmock/gmock.h>


class TestProtoConvert : public ::testing::Test {

};

TEST_F(TestProtoConvert, TestAllRestoredFieldsSet) {
    TaskData proto;
    proto.set_name("name");
    proto.set_prior(TaskData::THIRD);
    proto.set_label("label");
    proto.set_allocated_date(::google::protobuf::Timestamp().New());
    proto.set_completed(true);
    TaskDTO task = proto_convert::RestoreFromMessage(proto);
    ASSERT_EQ(proto.name(), task.getName());
    ASSERT_EQ(proto_convert::RestorePriority(proto.prior()), task.getPriority());
    ASSERT_EQ(proto.label(), task.getLabel());
    ASSERT_EQ(proto_convert::RestoreDate(proto.date()), task.getDate());
    ASSERT_EQ(proto.completed(), task.isCompleted());
}

TEST_F(TestProtoConvert, TestAllWrittenFieldsSet) {
    TaskData proto;
    auto task = TaskDTO::create( TaskID(1),
                                 "name",
                                 TaskPriority::SECOND,
                                 "label",
                                 boost::gregorian::day_clock::local_day(),
                                 true);
    proto_convert::WriteToMessage(task, &proto);
    ASSERT_EQ(proto.name(), task.getName());
    ASSERT_EQ(proto.prior(), proto_convert::GetProtobufPriority(task.getPriority()));
    ASSERT_EQ(proto.label(), task.getLabel());
    ASSERT_EQ(proto.date().seconds(), proto_convert::GetProtobufDate(task.getDate())->seconds());
    ASSERT_EQ(proto.completed(), task.isCompleted());
}