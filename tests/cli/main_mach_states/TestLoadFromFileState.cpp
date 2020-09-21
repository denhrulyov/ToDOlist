//
// Created by denis on 21.09.20.
//

#include "mocks/MockStateFactory.h"
#include "mocks/MockContext.h"
#include "mocks/MockIstreamDeserializer.h"
#include "cli/state_machines/main/states/LoadFromFileState.h"


class LoadFromFileStateTest : public ::testing::Test {

};

using ::testing::NiceMock;
using ::testing::ReturnRef;
using ::testing::Truly;
using ::testing::StrictMock;
using ::testing::ByMove;

TEST_F(LoadFromFileStateTest, BreakIfFileNotExist) {
    MockStateFactory mf;
    EXPECT_CALL(mf, getInstanceOfParseCommand).WillOnce(Return(nullptr));
    MockContext mctx;
    MockIstreamDeserializer mdsr;
    EXPECT_CALL(mdsr, deserialize).Times(0);
    EXPECT_CALL(mctx, getDeserializer).WillRepeatedly(ReturnRef(mdsr));
    NiceMock<MockIO> mio("jkkdsfjsdklfjsdkljfl");
    EXPECT_CALL(mctx, getIO).WillRepeatedly(ReturnRef(mio));
    LoadFromFileState state;
    state.execute(mctx, mf);
}

TEST_F(LoadFromFileStateTest, OkIfCorrectData) {
    MockStateFactory mf;
    EXPECT_CALL(mf, getInstanceOfParseCommand).WillOnce(Return(nullptr));
    auto ms = std::make_unique<MockService>();
    MockService* ms_ptr = ms.get();
    MockContext mctx;
    EXPECT_CALL(mctx, setTaskService(Truly([ms_ptr] (const auto& srv) {return srv.get() == ms_ptr;}))).Times(1);
    MockIstreamDeserializer mdsr;
    EXPECT_CALL(mdsr, deserialize).WillOnce(Return(ByMove(std::move(ms))));
    EXPECT_CALL(mctx, getDeserializer).WillRepeatedly(ReturnRef(mdsr));
    NiceMock<MockIO> mio("data.bin");
    EXPECT_CALL(mctx, getIO).WillRepeatedly(ReturnRef(mio));
    LoadFromFileState state;
    state.execute(mctx, mf);
}
