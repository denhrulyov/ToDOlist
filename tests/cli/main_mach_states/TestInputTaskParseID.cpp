//
// Created by denis on 13.09.20.
//

#include "cli/state_machines/main/states/parse_id/InputTaskParseID.h"
#include "mocks/MockStateFactory.h"
#include "mocks/MockContext.h"
#include "mocks/MockKeywordTokenizer.h"

class TestInputTaskParseID : public ::testing::Test {

};

using ::testing::NiceMock;
using ::testing::ReturnRef;
using ::testing::Truly;


TEST_F(TestInputTaskParseID, ReturnsToParseCommandIfTableIsEmpty) {
    MockStateFactory mf;
    EXPECT_CALL(mf, getInstanceOfParseCommand).WillOnce(Return(nullptr));
    NiceMock<MockContext> mctx;
    std::map<TaskNumber, TaskID> matching;
    EXPECT_CALL(mctx, getMatchingTablePositionToID).WillOnce(ReturnRef(matching));
    NiceMock<MockIO> mio;
    ON_CALL(mctx, getIO).WillByDefault(ReturnRef(mio));
    InputTaskParseID state;
    state.execute(mctx, mf);
}

TEST_F(TestInputTaskParseID, GoToSubtaskInputChainIfSuchRowExitstInTable) {
    MockStateFactory mf;
    EXPECT_CALL(mf, getInstanceOfSubTaskInputChain).WillOnce(Return(nullptr));
    NiceMock<MockContext> mctx;
    std::map<TaskNumber, TaskID> matching = {{TaskNumber(2), TaskID(4)}};
    EXPECT_CALL(mctx, getMatchingTablePositionToID).WillRepeatedly(ReturnRef(matching));
    NiceMock<MockIO> mio("2");
    ON_CALL(mctx, getIO).WillByDefault(ReturnRef(mio));
    InputTaskParseID state;
    state.execute(mctx, mf);
}
