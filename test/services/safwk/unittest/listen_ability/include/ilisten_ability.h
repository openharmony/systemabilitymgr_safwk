/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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

#ifndef SAFWK_TEST_SERVICES_SAFWK_UNITTEST_LISTEN_ABILITY_INCLUDE_ILISTEN_ABILITY_H
#define SAFWK_TEST_SERVICES_SAFWK_UNITTEST_LISTEN_ABILITY_INCLUDE_ILISTEN_ABILITY_H

#include <string_ex.h>
#include <cstdint>
#include <iremote_broker.h>

namespace OHOS {
class IListenAbility : public IRemoteBroker {
public:
    DECLARE_INTERFACE_DESCRIPTOR(u"OHOS.IListenAbility");

    virtual int32_t AddVolume(
        int32_t volume) = 0;
    virtual ErrCode TestSaCallSa(
        int32_t input, double& output) = 0;
    virtual ErrCode TestGetIpcSendRequestTimes(
        int32_t& times) = 0;
    virtual ErrCode TestClearSa1493Proxy_() = 0;
protected:
    const int VECTOR_MAX_SIZE = 102400;
    const int LIST_MAX_SIZE = 102400;
    const int MAP_MAX_SIZE = 102400;
};
} // namespace OHOS
#endif // SAFWK_TEST_SERVICES_SAFWK_UNITTEST_LISTEN_ABILITY_INCLUDE_ILISTEN_ABILITY_H