/*
 * PluginCafe.cpp
 *
 *  Created on: 2016. 3. 22.
 *      Author: naver
 */

#include "PluginCafe.h"
#include "NativeUtils.h"

using namespace cocos2d;

namespace cafe {

CafeListener::~CafeListener() {
    // do nothing.
}

void CafeSdk::init(std::string clientId, std::string clientSecret, int cafeId) {
    NativeUtils::sharedInstance().init(clientId, clientSecret, cafeId);
}

static CafeListener* gCafeListener = nullptr;

void CafeSdk::setCafeListener(CafeListener* listener) {
    // do nothing.
}

void CafeSdk::startHome() {
    NativeUtils::sharedInstance().navercafe();
}

void CafeSdk::startNotice() {
    // do nothing.
}

void CafeSdk::startEvent() {
    // do nothing.
}

void CafeSdk::startMenu() {
    // do nothing.
}

void CafeSdk::startMenu(int menuId) {
    // do nothing.
}

void CafeSdk::startProfile() {
    // do nothing.
}

void CafeSdk::startMore() {
    // do nothing.
}

void CafeSdk::startWrite(int menuId, std::string subject, std::string text) {
    // do nothing.
}

void CafeSdk::startImageWrite(int menuId, std::string subject, std::string text,
        std::string imageUri) {
    // do nothing.
}

void CafeSdk::startVideoWrite(int menuId, std::string subject, std::string text,
        std::string videoUri) {
    // do nothing.
}

void CafeSdk::syncGameUserId(std::string gameUserId) {
    // do nothing.
}

void CafeSdk::showToast(std::string text) {
    // do nothing.
}
    
} /* namespace cafe */
