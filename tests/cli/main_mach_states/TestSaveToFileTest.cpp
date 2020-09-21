//
// Created by denis on 21.09.20.
//

#include "mocks/MockStateFactory.h"
#include "mocks/MockContext.h"
#include "mocks/MockOstreamSerializer.h"
#include "cli/state_machines/main/states/SaveToFileState.h"


class LoadFromFileStateTest : public ::testing::Test {

};

using ::testing::NiceMock;
using ::testing::ReturnRef;
using ::testing::Truly;
using ::testing::StrictMock;
using ::testing::ByMove;
using ::testing::ByRef;
using ::testing::_;

TEST_F(LoadFromFileStateTest, WritesService) {
    MockStateFactory mf;
    EXPECT_CALL(mf, getInstanceOfParseCommand).WillOnce(Return(nullptr));
    auto ms = std::make_unique<MockService>();
    MockContext mctx;
    EXPECT_CALL(mctx, getTaskService).WillRepeatedly(ReturnRef(*ms));
    MockOstreamSerializer msr;
    EXPECT_CALL(msr, serialize(_, Truly([&ms] (const auto& srv) { return ms.get() == &srv;})));
    EXPECT_CALL(mctx, getSerializer).WillRepeatedly(ReturnRef(msr));
    NiceMock<MockIO> mio("test.bin");
    EXPECT_CALL(mctx, getIO).WillRepeatedly(ReturnRef(mio));
    SaveToFileState state;
    state.execute(mctx, mf);
}
