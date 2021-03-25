// FIXME: your file license if you have one

#pragma once

#include <vendor/hmd/hardware/card_socket_state/1.0/ICardSocketStateCallback.h>
#include <hidl/MQDescriptor.h>
#include <hidl/Status.h>

namespace vendor::hmd::hardware::card_socket_state::implementation {

using ::android::hardware::hidl_array;
using ::android::hardware::hidl_memory;
using ::android::hardware::hidl_string;
using ::android::hardware::hidl_vec;
using ::android::hardware::Return;
using ::android::hardware::Void;
using ::android::sp;

struct CardSocketStateCallback : public V1_0::ICardSocketStateCallback {
    // Methods from ::vendor::hmd::hardware::card_socket_state::V1_0::ICardSocketStateCallback follow.
    Return<void> onStateChanged(int32_t isCardSlotInsert) override;

    // Methods from ::android::hidl::base::V1_0::IBase follow.

};

// FIXME: most likely delete, this is only for passthrough implementations
// extern "C" ICardSocketStateCallback* HIDL_FETCH_ICardSocketStateCallback(const char* name);

}  // namespace vendor::hmd::hardware::card_socket_state::implementation
