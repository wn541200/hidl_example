// FIXME: your file license if you have one

#include "CardSocketStateCallback.h"

namespace vendor::hmd::hardware::card_socket_state::implementation {

// Methods from ::vendor::hmd::hardware::card_socket_state::V1_0::ICardSocketStateCallback follow.
Return<void> CardSocketStateCallback::onStateChanged(int32_t isCardSlotInsert) {
    // TODO implement
    return Void();
}


// Methods from ::android::hidl::base::V1_0::IBase follow.

//ICardSocketStateCallback* HIDL_FETCH_ICardSocketStateCallback(const char* /* name */) {
    //return new CardSocketStateCallback();
//}
//
}  // namespace vendor::hmd::hardware::card_socket_state::implementation
