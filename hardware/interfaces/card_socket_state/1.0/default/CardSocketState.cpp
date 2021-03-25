// FIXME: your file license if you have one

#include "CardSocketState.h"
#include <stdio.h>
#include <android-base/file.h>
#include <sys/epoll.h>
#include <sstream>

namespace vendor::hmd::hardware::card_socket_state::implementation {

CardSocketState *CardSocketState::sInstance = nullptr;

CardSocketState::CardSocketState() {
    mClientCallback = nullptr;
    mDevFd = -1;
    mEpollFd = -1;
    mCardSlotState = -1;

    mDevFd = open("/dev/input/event2", O_RDONLY);
    if (mDevFd < 0) {
        printf("open device fail\n");
        return;
    }

    epoll_event event, events[1];
    mEpollFd = epoll_create(1);
    event.events = EPOLLIN | EPOLLWAKEUP;
    epoll_ctl(mEpollFd, EPOLL_CTL_ADD, mDevFd, &event);

    mDeviceReadThread = new std::thread([this,&events]{
	while (true) {
            epoll_wait(mEpollFd, events, 1, -1);
            //std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            printf("111111\n");
            char buf[128];
            read(mDevFd, buf, 128);
            std::stringstream ss;
            ss << std::string(buf);
            ss >> mCardSlotState;
            printf("222222 %d\n", mCardSlotState);

            if (mClientCallback != nullptr) {
                printf("Notify client %d\n", mCardSlotState);
                mClientCallback->onStateChanged(mCardSlotState);
            }
	}
    });

}

CardSocketState::CardSocketState(const CardSocketState&) {

}


// Methods from ::vendor::hmd::hardware::card_socket_state::V1_0::ICardSocketState follow.
Return<int32_t> CardSocketState::getCardSocketState() {
    return mCardSlotState;
}

Return<int32_t> CardSocketState::setNotify(const sp<::vendor::hmd::hardware::card_socket_state::V1_0::ICardSocketStateCallback>& clientCallback) {
    printf("Client set a callback \n");
    mClientCallback = clientCallback;
    return 0;
}

ICardSocketState* CardSocketState::getInstance()
{
    if (!sInstance) {
        sInstance = new CardSocketState();
    }
    return sInstance;
}
// Methods from ::android::hidl::base::V1_0::IBase follow.

//ICardSocketState* HIDL_FETCH_ICardSocketState(const char* /* name */) {
    //return new CardSocketState();
//}
//
}  // namespace vendor::hmd::hardware::card_socket_state::implementation
