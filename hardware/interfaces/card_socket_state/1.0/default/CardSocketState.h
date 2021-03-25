// FIXME: your file license if you have one

#pragma once

#include <vendor/hmd/hardware/card_socket_state/1.0/ICardSocketState.h>
#include <vendor/hmd/hardware/card_socket_state/1.0/ICardSocketStateCallback.h>
#include <hidl/MQDescriptor.h>
#include <hidl/Status.h>
#include <thread>

namespace vendor::hmd::hardware::card_socket_state::implementation {

using vendor::hmd::hardware::card_socket_state::V1_0::ICardSocketState;
using vendor::hmd::hardware::card_socket_state::V1_0::ICardSocketStateCallback;
using ::android::hardware::hidl_array;
using ::android::hardware::hidl_memory;
using ::android::hardware::hidl_string;
using ::android::hardware::hidl_vec;
using ::android::hardware::Return;
using ::android::hardware::Void;
using ::android::sp;

struct CardSocketState : public V1_0::ICardSocketState {
    // Methods from ::vendor::hmd::hardware::card_socket_state::V1_0::ICardSocketState follow.
    Return<int32_t> getCardSocketState() override;
    Return<int32_t> setNotify(const sp<::vendor::hmd::hardware::card_socket_state::V1_0::ICardSocketStateCallback>& clientCallback) override;

    // Methods from ::android::hidl::base::V1_0::IBase follow.

public:
    static ICardSocketState* getInstance();

private:
    CardSocketState();
    CardSocketState(const CardSocketState&);
    CardSocketState& operator=(const CardSocketState&);

private:
    static CardSocketState* sInstance;
    sp<ICardSocketStateCallback> mClientCallback;

    std::thread *mDeviceReadThread;
    int mDevFd;
    int mEpollFd;
    int mCardSlotState;

};

// FIXME: most likely delete, this is only for passthrough implementations
// extern "C" ICardSocketState* HIDL_FETCH_ICardSocketState(const char* name);

}  // namespace vendor::hmd::hardware::card_socket_state::implementation
