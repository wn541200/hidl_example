#define LOG_TAG "vendor.hmd.hardware.card_socket_state@1.0-service"

#include <android/log.h>
#include <hidl/HidlSupport.h>
#include <hidl/HidlTransportSupport.h>
#include <vendor/hmd/hardware/card_socket_state/1.0/ICardSocketState.h>
#include "CardSocketState.h"


using vendor::hmd::hardware::card_socket_state::V1_0::ICardSocketState;
using vendor::hmd::hardware::card_socket_state::implementation::CardSocketState;
using android::hardware::configureRpcThreadpool;
using android::hardware::joinRpcThreadpool;
using android::sp;

int main()
{
    android::sp<ICardSocketState> svc = CardSocketState::getInstance();

    configureRpcThreadpool(1, true /*callerWillJoin*/);

    if (svc != nullptr) {
        if (::android::OK != svc->registerAsService()) {
            return 1;
        }
    } else {
        ALOGE("Can't create instance of sileadFingerprint, nullptr");
    }

    joinRpcThreadpool();

    return 0; // should never get here
}
