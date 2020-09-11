//
// Created by denis on 10.09.20.
//

#include "mocks/MockStateFactory.h"
#include "mocks/MockContext.h"
#include "cli/state_machines/main/states/StartState.h"

class TestParseCommand : public ::testing::Test {

};

using ::testing::NiceMock;
using ::testing::ReturnRef;
using ::testing::Truly;

template<class T>
bool operator==(Visitor<T>, Visitor<T>) {
    return true;
}

TEST_F(TestParseCommand, WillPassToParseCommand) {
    MockStateFactory mf;
    EXPECT_CALL(mf, getInstance(Visitor<ParseCommand>())).WillRepeatedly(Return(nullptr));
    NiceMock<MockContext> mctx;
    NiceMock<MockIO> mio();
    ON_CALL(mctx, getIO).WillByDefault(ReturnRef(mio));
    StartState state;
    state.execute(mctx, mf);
}