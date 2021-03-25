#include <vendor/hmd/hardware/card_socket_state/1.0/ICardSocketState.h>
#include <hidl/Status.h>
#include <hidl/LegacySupport.h>
#include <utils/misc.h>
#include <hidl/HidlSupport.h>
#include <stdio.h>
 
using vendor::hmd::hardware::card_socket_state::V1_0::ICardSocketState;
using vendor::hmd::hardware::card_socket_state::V1_0::ICardSocketStateCallback;
using android::sp;
using android::hardware::hidl_string;

class test_client_callback: public ICardSocketStateCallback {
    ::android::hardware::Return<void> onStateChanged(int32_t isCardSlotInsert) override {
        printf("yyyyy=%d\n", isCardSlotInsert);
        return ::android::hardware::Void();
    }
};
 
int main()
{
    //int ret;
 
    android::sp<ICardSocketState> service = ICardSocketState::getService();
    if(service == nullptr) {
        printf("Failed to get service\n");
        return -1;
    }

    sp<test_client_callback> callback = new test_client_callback();
    service->setNotify(callback);
 
    printf("xxxxxxxxx=%d\n", static_cast<int>(service->getCardSocketState()));

    while (true);
    return 0;
}

