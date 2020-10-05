//
// Created by denis on 04.10.20.
//

#include "mocks/CoreMocks.h"
#include "mocks/MockModelPersister.h"
#include "mocks/MockStreamOwner.h"
#include "core/ModelHolder.h"

using ::testing::Ref;
using ::testing::ReturnRef;
using ::testing::ByMove;

class ModelHolderTest : public ::testing::Test {

};


TEST_F(ModelHolderTest, TestSaveSuccessfull) {
    auto mm =  std::make_unique<MockModel>();
    TaskModelInterface *mmget = mm.get();
    auto mmc = std::make_unique<MockModelCreator>();
    auto mmp = std::make_unique<MockModelPersister>();
    MockStreamOwner mso;
    EXPECT_CALL(mso, SetStream).Times(1);
    EXPECT_CALL(*mmc, CreateModel).WillOnce(Return(ByMove(std::move(mm))));
    EXPECT_CALL(*mmp, Save(Truly(
            [mmget] (const TaskModelInterface& mip) {
                return &mip == mmget;
            })))
            .WillOnce(Return(true));
    ModelHolder mh(std::move(mmc), std::move(mmp), mso);
    ASSERT_TRUE(mh.SaveModelToFile("abacabadabacaba"));
}

TEST_F(ModelHolderTest, TestSaveFail) {
    auto mm =  std::make_unique<MockModel>();
    TaskModelInterface *mmget = mm.get();
    auto mmc = std::make_unique<MockModelCreator>();
    auto mmp = std::make_unique<MockModelPersister>();
    MockStreamOwner mso;
    EXPECT_CALL(mso, SetStream).Times(1);
    EXPECT_CALL(*mmc, CreateModel).WillOnce(Return(ByMove(std::move(mm))));
    EXPECT_CALL(*mmp, Save(Truly(
            [mmget] (const TaskModelInterface& mip) {
                return &mip == mmget;
            })))
            .WillOnce(Return(false));
    ModelHolder mh(std::move(mmc), std::move(mmp), mso);
    ASSERT_FALSE(mh.SaveModelToFile("abacabadabacaba"));
}

TEST_F(ModelHolderTest, TestLoadSuccessfull) {
    auto mm =  std::make_unique<MockModel>();
    auto mm0 =  std::make_unique<MockModel>();
    TaskModelInterface *mmget = mm.get();
    auto mmc = std::make_unique<MockModelCreator>();
    auto mmp = std::make_unique<MockModelPersister>();
    MockStreamOwner mso;
    EXPECT_CALL(mso, SetStream).Times(1);
    EXPECT_CALL(*mmc, CreateModel)
        .WillOnce(Return(ByMove(std::move(mm0))))
        .WillOnce(Return(ByMove(std::move(mm))));
    EXPECT_CALL(*mmp, Load(Truly(
            [mmget] (TaskModelInterface& mip) {
                return &mip == mmget;
            })))
            .WillOnce(Return(true));
    ModelHolder mh(std::move(mmc), std::move(mmp), mso);
    ASSERT_TRUE(mh.LoadModelFromFile("abacabadabacaba"));
}

TEST_F(ModelHolderTest, TestLoadFail) {
    auto mm =  std::make_unique<MockModel>();
    auto mm0 =  std::make_unique<MockModel>();
    TaskModelInterface *mmget = mm.get();
    auto mmc = std::make_unique<MockModelCreator>();
    auto mmp = std::make_unique<MockModelPersister>();
    MockStreamOwner mso;
    EXPECT_CALL(mso, SetStream).Times(1);
    EXPECT_CALL(*mmc, CreateModel)
            .WillOnce(Return(ByMove(std::move(mm0))))
            .WillOnce(Return(ByMove(std::move(mm))));
    EXPECT_CALL(*mmp, Load(Truly(
            [mmget] (TaskModelInterface& mip) {
                return &mip == mmget;
            })))
            .WillOnce(Return(false));
    ModelHolder mh(std::move(mmc), std::move(mmp), mso);
    ASSERT_FALSE(mh.LoadModelFromFile("abacabadabacaba"));
}
