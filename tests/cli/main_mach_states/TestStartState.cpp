//
// Created by denis on 10.09.20.
//

#include "mocks/MockStateFactory.h"
#include "mocks/MockContext.h"
#include "cli/state_machines/main/states/StartState.h"

class StartStateTest : public ::testing::Test {

};

using ::testing::NiceMock;
using ::testing::ReturnRef;
using ::testing::Truly;


TEST_F(StartStateTest, WillPassToParseCommand) {
    MockStateFactory mf;
    EXPECT_CALL(mf, getInstanceOfParseCommand()).WillRepeatedly(Return(nullptr));
    NiceMock<MockContext> mctx;
    NiceMock<MockIO> mio("");
    ON_CALL(mctx, getIO).WillByDefault(ReturnRef(mio));
    StartState state;
    state.execute(mctx, mf);
}

