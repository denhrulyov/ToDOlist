//
// Created by denis on 04.10.20.
//

#include "mocks/CoreMocks.h"
#include "mocks/MockModelPersister.h"
#include "mocks/MockModelPersisterCreator.h"
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
    auto mmpc = std::make_unique<MockModelPersisterCreator>();

    EXPECT_CALL(*mmc, CreateModel).WillOnce(Return(ByMove(std::move(mm))));
    EXPECT_CALL(*mmp, Save)
            .WillOnce(Return(true));
    EXPECT_CALL(*mmpc, CreatePersister).WillOnce(Return(ByMove(std::move(mmp))));
    ModelHolder mh(std::move(mmc), std::move(mmpc));
    ASSERT_TRUE(mh.SaveModelToFile("abacabadabacaba"));
}

TEST_F(ModelHolderTest, TestSaveFail) {
    auto mm =  std::make_unique<MockModel>();
    TaskModelInterface *mmget = mm.get();
    auto mmc = std::make_unique<MockModelCreator>();
    auto mmp = std::make_unique<MockModelPersister>();
    auto mmpc = std::make_unique<MockModelPersisterCreator>();
    EXPECT_CALL(*mmc, CreateModel).WillOnce(Return(ByMove(std::move(mm))));
    EXPECT_CALL(*mmp, Save)
            .WillOnce(Return(false));
    EXPECT_CALL(*mmpc, CreatePersister).WillOnce(Return(ByMove(std::move(mmp))));
    ModelHolder mh(std::move(mmc), std::move(mmpc));
    ASSERT_FALSE(mh.SaveModelToFile("abacabadabacaba"));
}

TEST_F(ModelHolderTest, TestLoadSuccessfull) {
    auto mm =  std::make_unique<MockModel>();
    auto mm0 =  std::make_unique<MockModel>();
    TaskModelInterface *mmget = mm.get();
    auto mmc = std::make_unique<MockModelCreator>();
    auto mmp = std::make_unique<MockModelPersister>();
    auto mmpc = std::make_unique<MockModelPersisterCreator>();
    EXPECT_CALL(*mmc, CreateModel)
        .WillOnce(Return(ByMove(std::move(mm0))))
        .WillOnce(Return(ByMove(std::move(mm))));
    EXPECT_CALL(*mmp, Load)
            .WillOnce(Return(true));
    EXPECT_CALL(*mmpc, CreatePersister).WillOnce(Return(ByMove(std::move(mmp))));
    ModelHolder mh(std::move(mmc), std::move(mmpc));
    ASSERT_TRUE(mh.LoadModelFromFile("abacabadabacaba"));
}

TEST_F(ModelHolderTest, TestLoadFail) {
    auto mm =  std::make_unique<MockModel>();
    auto mm0 =  std::make_unique<MockModel>();
    TaskModelInterface *mmget = mm.get();
    auto mmc = std::make_unique<MockModelCreator>();
    auto mmp = std::make_unique<MockModelPersister>();
    auto mmpc = std::make_unique<MockModelPersisterCreator>();
    EXPECT_CALL(*mmc, CreateModel)
            .WillOnce(Return(ByMove(std::move(mm0))))
            .WillOnce(Return(ByMove(std::move(mm))));
    EXPECT_CALL(*mmp, Load)
            .WillOnce(Return(false));
    EXPECT_CALL(*mmpc, CreatePersister).WillOnce(Return(ByMove(std::move(mmp))));
    ModelHolder mh(std::move(mmc), std::move(mmpc));
    ASSERT_FALSE(mh.LoadModelFromFile("abacabadabacaba"));
}
