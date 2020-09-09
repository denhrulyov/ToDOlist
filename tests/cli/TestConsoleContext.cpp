//
// Created by denis on 09.09.20.
//

#include <gtest/gtest.h>
#include "cli/state_machines/main/ConsoleContext.h"
#include "mocks/MockIO.h"
#include "mocks/MockService.h"

class ConsoleContextTest : public ::testing::Test {

};



TEST_F(ConsoleContextTest, TestIDBufferWritten) {
    ConsoleContext ctx(nullptr, std::move(std::make_unique<MockIO>()));
    TaskID id_to_write(2);
    ASSERT_FALSE(ctx.getBufferedId().has_value());
    ctx.fillIDBuffer(id_to_write);
    ASSERT_EQ(ctx.getBufferedId(), id_to_write);
}

TEST_F(ConsoleContextTest, TestTaskDTOBufferWritten) {
    ConsoleContext ctx(nullptr, std::move(std::make_unique<MockIO>()));
    auto dto = TaskDTO::create(
            TaskID(3),
            "name",
            TaskPriority::SECOND,
            "label",
            boost::gregorian::day_clock::local_day(),
            true);
    ASSERT_FALSE(ctx.getTaskBuffer().has_value());
    ctx.fillTaskBuffer(dto);
    ASSERT_TRUE(ctx.getTaskBuffer().has_value());
    ASSERT_EQ(ctx.getTaskBuffer()->getId(), dto.getId());
    ASSERT_EQ(ctx.getTaskBuffer()->getName(), dto.getName());
    ASSERT_EQ(ctx.getTaskBuffer()->getPriority(), dto.getPriority());
    ASSERT_EQ(ctx.getTaskBuffer()->getLabel(), dto.getLabel());
    ASSERT_EQ(ctx.getTaskBuffer()->getDate(), dto.getDate());
    ASSERT_EQ(ctx.getTaskBuffer()->isCompleted(), dto.isCompleted());
}

TEST_F(ConsoleContextTest, BringCorrectIO) {
    auto m0 = std::make_unique<MockIO>();
    ConsoleIOInterface* ptr = m0.get();
    ConsoleContext ctx(nullptr, std::move(m0));
    ASSERT_EQ(&ctx.getIO(), ptr);
}

TEST_F(ConsoleContextTest, BringCorrectService) {
    auto ms = std::make_unique<MockService>();
    TaskServiceInterface* ptr = ms.get();
    ConsoleContext ctx( std::move(ms), nullptr);
    ASSERT_EQ(&ctx.getTaskService(), ptr);
}

TEST_F(ConsoleContextTest, Added_Item_To_MatcingIDtoTablePosition) {
    ConsoleContext ctx(nullptr, nullptr);
    auto id_to_table_position_matching = ctx.getMatchingIDtoTablePosition();
    TaskID id1(1); TaskNumber num1(3);
    TaskID id2(2); TaskNumber num2(10);
    id_to_table_position_matching[id1] = num1;
    id_to_table_position_matching[id2] = num2;
    ASSERT_TRUE(id_to_table_position_matching.count(id1));
    ASSERT_TRUE(id_to_table_position_matching.count(id2));
    EXPECT_EQ(id_to_table_position_matching[id1], num1);
    EXPECT_EQ(id_to_table_position_matching[id2], num2);
}

TEST_F(ConsoleContextTest, Added_Item_To_MatcingTablePositionToID) {
    ConsoleContext ctx(nullptr, nullptr);
    auto table_position_to_id_matching = ctx.getMatchingTablePositionToID();
    TaskNumber num1(3); TaskID id1(1);
    TaskNumber num2(10); TaskID id2(2);
    table_position_to_id_matching[num1] = id1;
    table_position_to_id_matching[num2] = id2;
    ASSERT_TRUE(table_position_to_id_matching.count(num1));
    ASSERT_TRUE(table_position_to_id_matching.count(num2));
    EXPECT_EQ(table_position_to_id_matching[num1], id1);
    EXPECT_EQ(table_position_to_id_matching[num2], id2);
}