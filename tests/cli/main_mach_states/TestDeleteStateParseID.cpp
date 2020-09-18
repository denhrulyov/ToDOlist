//
// Created by denis on 13.09.20.
//

#include "cli/state_machines/main/states/parse_id/DeleteStateParseID.h"
#include "mocks/MockStateFactory.h"
#include "mocks/MockContext.h"
#include "mocks/MockKeywordTokenizer.h"
#include <gtest/gtest.h>
#include <gmock/gmock.h>

using ::testing::NiceMock;
using ::testing::ReturnRef;
using ::testing::Truly;


class TestDeleteStateParseID : public ::testing::Test {

};

TEST_F(TestDeleteStateParseID, ReturnsToParseCommandIfTableIsEmpty) {
    MockStateFactory mf;
    EXPECT_CALL(mf, getInstanceOfParseCommand).WillOnce(Return(nullptr));
    NiceMock<MockContext> mctx;
    std::map<TaskNumber, TaskID> matching;
    EXPECT_CALL(mctx, getMatchingTablePositionToID).WillOnce(ReturnRef(matching));
    NiceMock<MockIO> mio;
    ON_CALL(mctx, getIO).WillByDefault(ReturnRef(mio));
    DeleteStateParseID state;
    state.execute(mctx, mf);
}

TEST_F(TestDeleteStateParseID, GoToDeleteStateIfSuchRowExitstInTable) {
    MockStateFactory mf;
    EXPECT_CALL(mf, getInstanceOfDeleteTaskState).WillOnce(Return(nullptr));
    NiceMock<MockContext> mctx;
    std::map<TaskNumber, TaskID> matching = {{TaskNumber(2), TaskID(4)}};
    EXPECT_CALL(mctx, getMatchingTablePositionToID).WillRepeatedly(ReturnRef(matching));
    NiceMock<MockIO> mio("2");
    ON_CALL(mctx, getIO).WillByDefault(ReturnRef(mio));
    DeleteStateParseID state;
    state.execute(mctx, mf);
}
