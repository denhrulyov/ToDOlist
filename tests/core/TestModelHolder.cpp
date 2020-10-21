//
// Created by denis on 04.10.20.
//

#include "mocks/CoreMocks.h"
#include "mocks/MockModelPersister.h"
#include "mocks/MockModelPersisterCreator.h"
#include "core/RepositoryHolder.h"

using ::testing::Ref;
using ::testing::ReturnRef;
using ::testing::ByMove;

class ModelHolderTest : public ::testing::Test {

};


TEST_F(ModelHolderTest, TestSaveSuccessfull) {
    auto mm =  std::make_unique<MockRepository>();
    TaskRepositoryInterface *mmget = mm.get();
    auto mmc = std::make_unique<MockModelCreator>();
    auto mmp = std::make_unique<MockModelPersister>();
    auto mmpc = std::make_unique<MockModelPersisterCreator>();

    EXPECT_CALL(*mmc, CreateModel).WillOnce(Return(ByMove(std::move(mm))));
    EXPECT_CALL(*mmp, Save)
            .WillOnce(Return(true));
    EXPECT_CALL(*mmpc, CreatePersister).WillOnce(Return(ByMove(std::move(mmp))));
    RepositoryHolder mh(std::move(mmc), std::move(mmpc));
    ASSERT_TRUE(mh.SaveRepositoryToFile("abacabadabacaba"));
}

TEST_F(ModelHolderTest, TestSaveFail) {
    auto mm =  std::make_unique<MockRepository>();
    TaskRepositoryInterface *mmget = mm.get();
    auto mmc = std::make_unique<MockModelCreator>();
    auto mmp = std::make_unique<MockModelPersister>();
    auto mmpc = std::make_unique<MockModelPersisterCreator>();
    EXPECT_CALL(*mmc, CreateModel).WillOnce(Return(ByMove(std::move(mm))));
    EXPECT_CALL(*mmp, Save)
            .WillOnce(Return(false));
    EXPECT_CALL(*mmpc, CreatePersister).WillOnce(Return(ByMove(std::move(mmp))));
    RepositoryHolder mh(std::move(mmc), std::move(mmpc));
    ASSERT_FALSE(mh.SaveRepositoryToFile("abacabadabacaba"));
}

TEST_F(ModelHolderTest, TestLoadSuccessfull) {
    auto mm =  std::make_unique<MockRepository>();
    auto mm0 =  std::make_unique<MockRepository>();
    TaskRepositoryInterface *mmget = mm.get();
    auto mmc = std::make_unique<MockModelCreator>();
    auto mmp = std::make_unique<MockModelPersister>();
    auto mmpc = std::make_unique<MockModelPersisterCreator>();
    EXPECT_CALL(*mmc, CreateModel)
        .WillOnce(Return(ByMove(std::move(mm0))))
        .WillOnce(Return(ByMove(std::move(mm))));
    EXPECT_CALL(*mmp, Load)
            .WillOnce(Return(true));
    EXPECT_CALL(*mmpc, CreatePersister).WillOnce(Return(ByMove(std::move(mmp))));
    RepositoryHolder mh(std::move(mmc), std::move(mmpc));
    ASSERT_TRUE(mh.LoadRepositoryFromFile("abacabadabacaba"));
}

TEST_F(ModelHolderTest, TestLoadFail) {
    auto mm =  std::make_unique<MockRepository>();
    auto mm0 =  std::make_unique<MockRepository>();
    TaskRepositoryInterface *mmget = mm.get();
    auto mmc = std::make_unique<MockModelCreator>();
    auto mmp = std::make_unique<MockModelPersister>();
    auto mmpc = std::make_unique<MockModelPersisterCreator>();
    EXPECT_CALL(*mmc, CreateModel)
            .WillOnce(Return(ByMove(std::move(mm0))))
            .WillOnce(Return(ByMove(std::move(mm))));
    EXPECT_CALL(*mmp, Load)
            .WillOnce(Return(false));
    EXPECT_CALL(*mmpc, CreatePersister).WillOnce(Return(ByMove(std::move(mmp))));
    RepositoryHolder mh(std::move(mmc), std::move(mmpc));
    ASSERT_FALSE(mh.LoadRepositoryFromFile("abacabadabacaba"));
}
