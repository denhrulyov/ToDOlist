//
// Created by denis on 21.09.20.
//

#include "serialization/ProtoTaskDeserializer.h"

#include <gtest/gtest.h>
#include <gmock/gmock.h>


class TestProtoTaskDeserializer : public ::testing::Test {

};

TEST_F(TestProtoTaskDeserializer, TestAllFieldsSet) {
    ProtoTaskDeserializer pts;
    TaskProto proto;
    proto.set_name("name");
    proto.set_prior(TaskProto::THIRD);
    proto.set_label("label");
    proto.set_allocated_date(::google::protobuf::Timestamp().New());
    proto.set_completed(true);
    TaskDTO task = pts.deserialize(proto);
    ASSERT_EQ(proto.name(), task.getName());
    ASSERT_EQ(serialization::deserialize_priority(proto.prior()), task.getPriority());
    ASSERT_EQ(proto.label(), task.getLabel());
    ASSERT_EQ(serialization::deserialize_date(proto.date()), task.getDate());
    ASSERT_EQ(proto.completed(), task.isCompleted());
}
