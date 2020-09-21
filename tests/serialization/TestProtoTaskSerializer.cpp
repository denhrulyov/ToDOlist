//
// Created by denis on 21.09.20.
//

#include "serialization/ProtoTaskSerializer.h"

#include <gtest/gtest.h>
#include <gmock/gmock.h>

class TestProtoTaskSerializer : public ::testing::Test {

};

TEST_F(TestProtoTaskSerializer, TestAllFieldsSet) {
    ProtoTaskSerializer pts;
    TaskProto proto;
    auto task = TaskDTO::create( TaskID(1),
                                "name",
                                TaskPriority::SECOND,
                                "label",
                                boost::gregorian::day_clock::local_day(),
                                true);
    pts.serializeTo(task, &proto);
    ASSERT_EQ(proto.name(), task.getName());
    ASSERT_EQ(proto.prior(), serialization::serialize_priority(task.getPriority()));
    ASSERT_EQ(proto.label(), task.getLabel());
    ASSERT_EQ(proto.date().seconds(), serialization::serialize_date(task.getDate())->seconds());
    ASSERT_EQ(proto.completed(), task.isCompleted());
}