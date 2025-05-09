/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include "gtest/gtest.h"
#include "iservice_registry.h"
#include "local_ability_manager_stub.h"
#include "memory"
#include "sa_mock_permission.h"
#include "test_log.h"

#define private public
#define protected public
#include "local_ability_manager.h"
#include "mock_sa_realize.h"
using namespace testing;
using namespace testing::ext;

namespace OHOS {
namespace SAFWK {
namespace {
    constexpr int32_t SAID = 1489;
    const std::string TEST_STRING = "test";
    const std::string EVENT_NAME = "name";
    const std::string EVENT_ID = "eventId";
    const std::string TEST_RESOURCE_PATH = "/data/test/resource/samgr/profile/";
    constexpr int32_t LISTENER_ID = 1488;
    constexpr int32_t MOCK_DEPEND_TIMEOUT = 1000;
}

class MockLocalAbilityManager : public LocalAbilityManagerStub {
public:
    MockLocalAbilityManager() = default;
    ~MockLocalAbilityManager() = default;

    bool StartAbility(int32_t systemAbilityId, const std::string& eventStr) override;
    bool StopAbility(int32_t systemAbilityId, const std::string& eventStr) override;
    bool ActiveAbility(int32_t systemAbilityId,
        const nlohmann::json& activeReason) override;
    bool IdleAbility(int32_t systemAbilityId,
        const nlohmann::json& idleReason, int32_t& delayTime) override;
    bool SendStrategyToSA(int32_t type, int32_t systemAbilityId,
        int32_t level, std::string& action) override;
    bool IpcStatCmdProc(int32_t fd, int32_t cmd) override;
    bool FfrtDumperProc(std::string& ffrtdumpinfo) override;
    int32_t SystemAbilityExtProc(const std::string& extension, int32_t said,
        SystemAbilityExtensionPara* callback, bool isAsync) override;
    bool FfrtStatCmdProc(int32_t fd, int32_t cmd) override;
    int32_t ServiceControlCmd(int32_t fd, int32_t systemAbilityId, const std::vector<std::u16string>& args) override;
};
class SystemAbilityTest : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp();
    void TearDown();
};

void SystemAbilityTest::SetUpTestCase()
{
    DTEST_LOG << "SetUpTestCase" << std::endl;
}

void SystemAbilityTest::TearDownTestCase()
{
    DTEST_LOG << "TearDownTestCase" << std::endl;
}

void SystemAbilityTest::SetUp()
{
    SaMockPermission::MockPermission();
    DTEST_LOG << "SetUp" << std::endl;
}

void SystemAbilityTest::TearDown()
{
    DTEST_LOG << "TearDown" << std::endl;
}

bool MockLocalAbilityManager::StartAbility(int32_t systemAbilityId, const std::string& eventStr)
{
    DTEST_LOG << "said : " << systemAbilityId <<std::endl;
    return true;
}

bool MockLocalAbilityManager::StopAbility(int32_t systemAbilityId, const std::string& eventStr)
{
    DTEST_LOG << "said : " << systemAbilityId <<std::endl;
    return true;
}

bool MockLocalAbilityManager::ActiveAbility(int32_t systemAbilityId,
    const nlohmann::json& activeReason)
{
    DTEST_LOG << "said : " << systemAbilityId <<std::endl;
    return true;
}

bool MockLocalAbilityManager::IdleAbility(int32_t systemAbilityId,
    const nlohmann::json& idleReason, int32_t& delayTime)
{
    DTEST_LOG << "said : " << systemAbilityId <<std::endl;
    return true;
}

bool MockLocalAbilityManager::SendStrategyToSA(int32_t type, int32_t systemAbilityId,
    int32_t level, std::string& action)
{
    DTEST_LOG << "said : " << systemAbilityId <<std::endl;
    return true;
}

bool MockLocalAbilityManager::IpcStatCmdProc(int32_t fd, int32_t cmd)
{
    DTEST_LOG << "fd : " << fd <<std::endl;
    DTEST_LOG << "cmd : " << cmd <<std::endl;
    return true;
}

bool MockLocalAbilityManager::FfrtDumperProc(std::string& ffrtDumpInfo)
{
    DTEST_LOG << "FfrtDumperProc" <<std::endl;
    return true;
}

int32_t MockLocalAbilityManager::SystemAbilityExtProc(const std::string& extension, int32_t said,
    SystemAbilityExtensionPara* callback, bool isAsync)
{
    DTEST_LOG << "said : " << said <<std::endl;
    return 0;
}
bool MockLocalAbilityManager::FfrtStatCmdProc(int32_t fd, int32_t cmd)
{
    DTEST_LOG << "fd : " << fd <<std::endl;
    DTEST_LOG << "cmd : " << cmd <<std::endl;
    return true;
}

int32_t MockLocalAbilityManager::ServiceControlCmd(int32_t fd, int32_t systemAbilityId,
    const std::vector<std::u16string>& args)
{
    DTEST_LOG << "fd : " << fd << std::endl;
    DTEST_LOG << "said : " << systemAbilityId << std::endl;
    return 0;
}

/**
 * @tc.name: RemoveSystemAbilityListener001
 * @tc.desc: Check RemoveSystemAbilityListener
 * @tc.type: FUNC
 * @tc.require: I5KMF7
 */
HWTEST_F(SystemAbilityTest, RemoveSystemAbilityListener001, TestSize.Level0)
{
    DTEST_LOG << "RemoveSystemAbilityListener001 start" << std::endl;
    std::shared_ptr<SystemAbility> sysAby = std::make_shared<MockSaRealize>(SAID, false);
    sysAby->AddSystemAbilityListener(LISTENER_ID);
    bool res = sysAby->RemoveSystemAbilityListener(LISTENER_ID);
    EXPECT_EQ(res, true);
    DTEST_LOG << "RemoveSystemAbilityListener001 end" << std::endl;
}

/**
 * @tc.name: MakeAndRegisterAbility001
 * @tc.desc: Check MakeAndRegisterAbility
 * @tc.type: FUNC
 * @tc.require: I5KMF7
 */
HWTEST_F(SystemAbilityTest, MakeAndRegisterAbility001, TestSize.Level0)
{
    DTEST_LOG << "MakeAndRegisterAbility001 start" << std::endl;
    bool res = SystemAbility::MakeAndRegisterAbility(new MockSaRealize(SAID, false));
    EXPECT_EQ(res, false);
    DTEST_LOG << "MakeAndRegisterAbility001 end" << std::endl;
}

/**
 * @tc.name: MakeAndRegisterAbility002
 * @tc.desc: Check MakeAndRegisterAbility
 * @tc.type: FUNC
 * @tc.require: I5KMF7
 */
HWTEST_F(SystemAbilityTest, MakeAndRegisterAbility002, TestSize.Level2)
{
    DTEST_LOG << "MakeAndRegisterAbility002 start" << std::endl;
    bool ret = LocalAbilityManager::GetInstance().profileParser_->ParseSaProfiles(TEST_RESOURCE_PATH + "1489.json");
    EXPECT_EQ(ret, true);
    bool res = SystemAbility::MakeAndRegisterAbility(new MockSaRealize(SAID, false));
    EXPECT_EQ(res, true);
    DTEST_LOG << "MakeAndRegisterAbility002 start" << std::endl;
}

/**
 * @tc.name: Publish001
 * @tc.desc: Verify Publish when systemabitly is nullptr
 * @tc.type: FUNC
 * @tc.require: I5KMF7
 */
HWTEST_F(SystemAbilityTest, Publish001, TestSize.Level2)
{
    DTEST_LOG << "Publish001 start" << std::endl;
    std::shared_ptr<SystemAbility> sysAby = std::make_shared<MockSaRealize>(SAID, false);
    bool ret = sysAby->Publish(nullptr);
    EXPECT_FALSE(ret);
    DTEST_LOG << "Publish001 end" << std::endl;
}

/**
 * @tc.name: Publish002
 * @tc.desc: Verify Publish function
 * @tc.type: FUNC
 * @tc.require: I5KMF7
 */
HWTEST_F(SystemAbilityTest, Publish002, TestSize.Level2)
{
    DTEST_LOG << "Publish002 start" << std::endl;
    std::shared_ptr<SystemAbility> sysAby = std::make_shared<MockSaRealize>(SAID, false);
    sptr<IRemoteObject> obj(new MockLocalAbilityManager());
    bool ret = sysAby->Publish(obj);
    ASSERT_TRUE(ret);
    sysAby->Stop();
    sysAby->StopAbility(-1);
    sysAby->Start();
    sysAby->Stop();
    EXPECT_EQ(sysAby->abilityState_, SystemAbilityState::NOT_LOADED);
    DTEST_LOG << "Publish002 end" << std::endl;
}

/**
 * @tc.name: SetDependTimeout001
 * @tc.desc: Verify SetDependTimeout
 * @tc.type: FUNC
 * @tc.require: I5KMF7
 */
HWTEST_F(SystemAbilityTest, SetDependTimeout001, TestSize.Level2)
{
    DTEST_LOG << "SetDependTimeout001 start" << std::endl;
    std::shared_ptr<SystemAbility> sysAby = std::make_shared<MockSaRealize>(SAID, false);
    sysAby->SetDependTimeout(0);
    sysAby->SetDependTimeout(MOCK_DEPEND_TIMEOUT);
    EXPECT_EQ(sysAby->GetDependTimeout(), MOCK_DEPEND_TIMEOUT);
    DTEST_LOG << "SetDependTimeout001 end" << std::endl;
}

/**
 * @tc.name: GetSystemAbility001
 * @tc.desc: Check GetSystemAbility
 * @tc.type: FUNC
 * @tc.require: I5KMF7
 */
HWTEST_F(SystemAbilityTest, GetSystemAbility001, TestSize.Level2)
{
    DTEST_LOG << "GetSystemAbility001 start" << std::endl;
    std::shared_ptr<SystemAbility> sysAby = std::make_shared<MockSaRealize>(SAID, false);
    sptr<IRemoteObject> obj = sysAby->GetSystemAbility(-1);
    EXPECT_TRUE(obj == nullptr);
    DTEST_LOG << "GetSystemAbility001 end" << std::endl;
}

/**
 * @tc.name: CancelIdle001
 * @tc.desc: test CancelIdle with abilityState_ is not SystemAbilityState::IDLE
 * @tc.type: FUNC
 * @tc.require:I6LSSX
 */
HWTEST_F(SystemAbilityTest, CancelIdle001, TestSize.Level2)
{
    DTEST_LOG << "CancelIdle001 start" << std::endl;
    std::shared_ptr<SystemAbility> sysAby = std::make_shared<MockSaRealize>(SAID, false);
    sysAby->abilityState_ = SystemAbilityState::NOT_LOADED;
    int32_t ret = sysAby->CancelIdle();
    EXPECT_TRUE(ret);
    DTEST_LOG << "CancelIdle001 end" << std::endl;
}

/**
 * @tc.name: CancelIdle002
 * @tc.desc: test CancelIdle with abilityState_ is SystemAbilityState::IDLE
 * @tc.type: FUNC
 * @tc.require:I6LSSX
 */
HWTEST_F(SystemAbilityTest, CancelIdle002, TestSize.Level2)
{
    DTEST_LOG << "CancelIdle002 start" << std::endl;
    std::shared_ptr<SystemAbility> sysAby = std::make_shared<MockSaRealize>(SAID, false);
    sysAby->abilityState_ = SystemAbilityState::IDLE;
    int32_t ret = sysAby->CancelIdle();
    EXPECT_FALSE(ret);
    DTEST_LOG << "CancelIdle002 end" << std::endl;
}

/**
 * @tc.name: Start001
 * @tc.desc: test Start with abilityState_ is not SystemAbilityState::NOT_LOADED
 * @tc.type: FUNC
 * @tc.require:I6LSSX
 */
HWTEST_F(SystemAbilityTest, Start001, TestSize.Level2)
{
    DTEST_LOG << "Start001 start" << std::endl;
    std::shared_ptr<SystemAbility> sysAby = std::make_shared<MockSaRealize>(SAID, false);
    sysAby->abilityState_ = SystemAbilityState::IDLE;
    sysAby->Start();
    EXPECT_FALSE(sysAby->isRunning_);
    DTEST_LOG << "Start001 end" << std::endl;
}

/**
 * @tc.name: Start002
 * @tc.desc: test Start with is SystemAbilityState::NOT_LOADED
 * @tc.type: FUNC
 * @tc.require:I6LSSX
 */
HWTEST_F(SystemAbilityTest, Start002, TestSize.Level2)
{
    DTEST_LOG << "Start002 start" << std::endl;
    std::shared_ptr<SystemAbility> sysAby = std::make_shared<MockSaRealize>(SAID, false);
    sysAby->abilityState_ = SystemAbilityState::NOT_LOADED;
    sysAby->Start();
    EXPECT_TRUE(sysAby->isRunning_);
    DTEST_LOG << "Start002 end" << std::endl;
}

/**
 * @tc.name: Idle001
 * @tc.desc: test Idle with abilityState_ is not SystemAbilityState::ACTIVE
 * @tc.type: FUNC
 * @tc.require:I6LSSX
 */
HWTEST_F(SystemAbilityTest, Idle001, TestSize.Level2)
{
    DTEST_LOG << "Idle001 start" << std::endl;
    std::shared_ptr<SystemAbility> sysAby = std::make_shared<MockSaRealize>(SAID, false);
    sysAby->abilityState_ = SystemAbilityState::IDLE;
    SystemAbilityOnDemandReason idleReason;
    int32_t delayTime = 123;
    sysAby->Idle(idleReason, delayTime);
    EXPECT_EQ(sysAby->abilityState_,  SystemAbilityState::IDLE);
    DTEST_LOG << "Idle001 end" << std::endl;
}

/**
 * @tc.name: Idle002
 * @tc.desc: test Idle with abilityState_ is SystemAbilityState::ACTIVE and delayTime is 0
 * @tc.type: FUNC
 * @tc.require:I6LSSX
 */
HWTEST_F(SystemAbilityTest, Idle002, TestSize.Level2)
{
    DTEST_LOG << "Idle002 start" << std::endl;
    std::shared_ptr<SystemAbility> sysAby = std::make_shared<MockSaRealize>(SAID, false);
    sysAby->abilityState_ = SystemAbilityState::ACTIVE;
    SystemAbilityOnDemandReason idleReason;
    idleReason.SetId(OnDemandReasonId::DEVICE_ONLINE);
    int32_t noDelayTime = 0;
    sysAby->Idle(idleReason, noDelayTime);
    EXPECT_EQ(sysAby->abilityState_, SystemAbilityState::IDLE);
    DTEST_LOG << "Idle002 end" << std::endl;
}

/**
 * @tc.name: Idle003
 * @tc.desc: test Idle with abilityState_ is SystemAbilityState::ACTIVE and delayTime is 0
 * @tc.type: FUNC
 * @tc.require:I6LSSX
 */
HWTEST_F(SystemAbilityTest, Idle003, TestSize.Level2)
{
    DTEST_LOG << "Idle003 start" << std::endl;
    std::shared_ptr<SystemAbility> sysAby = std::make_shared<MockSaRealize>(SAID, false);
    sysAby->abilityState_ = SystemAbilityState::ACTIVE;
    SystemAbilityOnDemandReason idleReason;
    idleReason.SetId(OnDemandReasonId::DEVICE_ONLINE);
    int32_t delayTime = 123;
    sysAby->Idle(idleReason, delayTime);
    EXPECT_EQ(sysAby->abilityState_, SystemAbilityState::IDLE);
    DTEST_LOG << "Idle003 end" << std::endl;
}

/**
 * @tc.name: Active001
 * @tc.desc: test Active with abilityState_ is not SystemAbilityState::IDLE
 * @tc.type: FUNC
 * @tc.require:I6LSSX
 */
HWTEST_F(SystemAbilityTest, Active001, TestSize.Level2)
{
    DTEST_LOG << "Active001 start" << std::endl;
    std::shared_ptr<SystemAbility> sysAby = std::make_shared<MockSaRealize>(SAID, false);
    sysAby->abilityState_ = SystemAbilityState::ACTIVE;
    SystemAbilityOnDemandReason activeReason;
    sysAby->Active(activeReason);
    EXPECT_EQ(sysAby->abilityState_, SystemAbilityState::ACTIVE);
    DTEST_LOG << "Active001 end" << std::endl;
}

/**
 * @tc.name: Active002
 * @tc.desc: test Active with abilityState_ is SystemAbilityState::IDLE
 * @tc.type: FUNC
 * @tc.require:I6LSSX
 */
HWTEST_F(SystemAbilityTest, Active002, TestSize.Level2)
{
    DTEST_LOG << "Active002 start" << std::endl;
    std::shared_ptr<SystemAbility> sysAby = std::make_shared<MockSaRealize>(SAID, false);
    sysAby->abilityState_ = SystemAbilityState::IDLE;
    SystemAbilityOnDemandReason activeReason;
    activeReason.SetId(OnDemandReasonId::DEVICE_ONLINE);
    sysAby->Active(activeReason);
    EXPECT_EQ(sysAby->abilityState_, SystemAbilityState::ACTIVE);
    DTEST_LOG << "Active002 end" << std::endl;
}

/**
 * @tc.name: GetLibPath001
 * @tc.desc: Check GetLibPath,cover function
 * @tc.type: FUNC
 * @tc.require:I6LSSX
 */
HWTEST_F(SystemAbilityTest, GetLibPath001, TestSize.Level2)
{
    DTEST_LOG << "GetLibPath001 start" << std::endl;
    std::shared_ptr<SystemAbility> sysAby = std::make_shared<MockSaRealize>(SAID, false);
    sysAby->libPath_ = TEST_RESOURCE_PATH;
    EXPECT_EQ(sysAby->libPath_, TEST_RESOURCE_PATH);
    DTEST_LOG << "GetLibPath001 end" << std::endl;
}

/**
 * @tc.name: IsRunOnCreate001
 * @tc.desc: Check IsRunOnCreate,cover function
 * @tc.type: FUNC
 * @tc.require:I6LSSX
 */
HWTEST_F(SystemAbilityTest, IsRunOnCreate001, TestSize.Level2)
{
    DTEST_LOG << "IsRunOnCreate001 start" << std::endl;
    std::shared_ptr<SystemAbility> sysAby = std::make_shared<MockSaRealize>(SAID, false);
    sysAby->isRunOnCreate_ = true;
    EXPECT_TRUE(sysAby->isRunOnCreate_);
    DTEST_LOG << "IsRunOnCreate001 end" << std::endl;
}

/**
 * @tc.name: OnIdle001
 * @tc.desc: Check OnIdle,cover function
 * @tc.type: FUNC
 * @tc.require:I6LSSX
 */
HWTEST_F(SystemAbilityTest, OnIdle001, TestSize.Level2)
{
    DTEST_LOG << "OnIdle001 start" << std::endl;
    std::shared_ptr<SystemAbility> sysAby = std::make_shared<MockSaRealize>(SAID, false);
    SystemAbilityOnDemandReason idleReason;
    int32_t ret = sysAby->OnIdle(idleReason);
    EXPECT_EQ(ret, 0);
    DTEST_LOG << "OnIdle001 end" << std::endl;
}

/**
 * @tc.name: GetCapability001
 * @tc.desc: Check GetCapability, cover function
 * @tc.type: FUNC
 * @tc.require: I73XRZ
 */
HWTEST_F(SystemAbilityTest, GetCapability001, TestSize.Level2)
{
    DTEST_LOG << "GetCapability001 start" << std::endl;
    std::shared_ptr<SystemAbility> sysAby = std::make_shared<MockSaRealize>(SAID, false);
    sysAby->OnDump();
    std::u16string capability;
    auto ret = sysAby->GetCapability();
    EXPECT_EQ(ret, capability);
    DTEST_LOG << "GetCapability001 end" << std::endl;
}

/**
 * @tc.name: GetAbilityState001
 * @tc.desc: Check GetAbilityState, cover function
 * @tc.type: FUNC
 * @tc.require: I73XRZ
 */
HWTEST_F(SystemAbilityTest, GetAbilityState001, TestSize.Level2)
{
    DTEST_LOG << "GetAbilityState001 start" << std::endl;
    std::shared_ptr<SystemAbility> sysAby = std::make_shared<MockSaRealize>(SAID, false);
    SystemAbilityState ret = sysAby->GetAbilityState();
    EXPECT_EQ(ret, SystemAbilityState::NOT_LOADED);
    DTEST_LOG << "GetAbilityState001 end" << std::endl;
}

/**
 * @tc.name: IsRunOnCreate002
 * @tc.desc: Check IsRunOnCreate, cover function
 * @tc.type: FUNC
 * @tc.require: I73XRZ
 */
HWTEST_F(SystemAbilityTest, IsRunOnCreate002, TestSize.Level2)
{
    DTEST_LOG << "IsRunOnCreate002 start" << std::endl;
    std::shared_ptr<SystemAbility> sysAby = std::make_shared<MockSaRealize>(SAID, false);
    bool ret = sysAby->IsRunOnCreate();
    EXPECT_FALSE(ret);
    DTEST_LOG << "IsRunOnCreate002 end" << std::endl;
}

/**
 * @tc.name: GetLibPath002
 * @tc.desc: Check GetLibPath, cover function
 * @tc.type: FUNC
 * @tc.require: I73XRZ
 */
HWTEST_F(SystemAbilityTest, GetLibPath002, TestSize.Level2)
{
    DTEST_LOG << "GetLibPath002 start" << std::endl;
    std::shared_ptr<SystemAbility> sysAby = std::make_shared<MockSaRealize>(SAID, false);
    sysAby->SADump();
    SystemAbilityOnDemandReason onDemandStartReason;
    sysAby->GetOnDemandReasonExtraData(onDemandStartReason);
    std::string capability;
    auto ret = sysAby->GetLibPath();
    EXPECT_EQ(ret, capability);
    DTEST_LOG << "GetLibPath002 end" << std::endl;
}

/**
 * @tc.name: GetOnDemandReasonExtraData001
 * @tc.desc: Check GetOnDemandReasonExtraData
 * @tc.type: FUNC
 * @tc.require: I73XRZ
 */
HWTEST_F(SystemAbilityTest, GetOnDemandReasonExtraData001, TestSize.Level2)
{
    DTEST_LOG << "GetOnDemandReasonExtraData001 start" << std::endl;
    std::shared_ptr<SystemAbility> sysAby = std::make_shared<MockSaRealize>(SAID, false);
    SystemAbilityOnDemandReason onDemandStartReason;
    onDemandStartReason.reasonId_ = OHOS::OnDemandReasonId::COMMON_EVENT;
    sysAby->GetOnDemandReasonExtraData(onDemandStartReason);
    EXPECT_TRUE(onDemandStartReason.HasExtraData());
    DTEST_LOG << "GetOnDemandReasonExtraData001 end" << std::endl;
}
}
}