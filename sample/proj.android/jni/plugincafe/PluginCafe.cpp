/*
 * PluginCafe.cpp
 *
 *  Created on: 2016. 3. 22.
 *      Author: naver
 */

#include "PluginCafe.h"
#include "PluginJniHelper.h"

#define SDK AndroidJavaCafeSdk::sharedInstance()
#define ENV AndroidJavaCafeSdk::sharedInstance()->env_

#define CALL_VOID_METHOD(method, ...) \
    ENV->CallStaticVoidMethod(SDK->cafeSdkClass_, method.methodID, ##__VA_ARGS__)

using namespace cocos2d;

namespace cafe {

static CafeListener* gCafeListener = nullptr;

class AndroidJavaCafeSdk {
public:
    static AndroidJavaCafeSdk* sharedInstance();

    AndroidJavaCafeSdk();

    JNIEnv* env_;
    jclass cafeSdkClass_;

    cocos2d::PluginJniMethodInfo initMethod_;
    cocos2d::PluginJniMethodInfo sartHomeMethod_;
    cocos2d::PluginJniMethodInfo startNoticeMethod_;
    cocos2d::PluginJniMethodInfo startEventMethod_;
    cocos2d::PluginJniMethodInfo startMenuMethod_;
    cocos2d::PluginJniMethodInfo startProfileMethod_;
    cocos2d::PluginJniMethodInfo startMoreMethod_;
    cocos2d::PluginJniMethodInfo startWriteMethod_;
    cocos2d::PluginJniMethodInfo startImageWriteMethod_;
    cocos2d::PluginJniMethodInfo startVideoWriteMethod_;
    cocos2d::PluginJniMethodInfo syncGameUserIdMethod_;
    cocos2d::PluginJniMethodInfo showToastMethod_;
};

AndroidJavaCafeSdk* AndroidJavaCafeSdk::sharedInstance() {
    static AndroidJavaCafeSdk* sharedInstance_ = nullptr;
    if (sharedInstance_ == nullptr) {
        sharedInstance_ = new AndroidJavaCafeSdk();
    }

    return sharedInstance_;
}

static bool StaticMethod(PluginJniMethodInfo &methodinfo,
        const char *methodName, const char *paramCode) {
    static const char* kCafeSdkClass = "com/naver/cafe/CafeSdk";
    return PluginJniHelper::getStaticMethodInfo(methodinfo, kCafeSdkClass,
            methodName, paramCode);
}

AndroidJavaCafeSdk::AndroidJavaCafeSdk() {
    StaticMethod(initMethod_, "init",
            "(Ljava/lang/String;Ljava/lang/String;I)V");

    env_ = initMethod_.env;
    cafeSdkClass_ = (jclass) env_->NewGlobalRef(initMethod_.classID);

    StaticMethod(sartHomeMethod_, "startHome", "()V");
    StaticMethod(startNoticeMethod_, "startNotice", "()V");
    StaticMethod(startEventMethod_, "startEvent", "()V");
    StaticMethod(startProfileMethod_, "startProfile", "()V");
    StaticMethod(startMenuMethod_, "startMenu", "(I)V");
    StaticMethod(startMoreMethod_, "startMore", "()V");

    StaticMethod(startWriteMethod_, "startWrite",
            "(ILjava/lang/String;Ljava/lang/String;)V");

    StaticMethod(startImageWriteMethod_, "startImageWrite",
            "(ILjava/lang/String;Ljava/lang/String;Ljava/lang/String;)V");

    StaticMethod(startVideoWriteMethod_, "startVideoWrite",
            "(ILjava/lang/String;Ljava/lang/String;Ljava/lang/String;)V");

    StaticMethod(syncGameUserIdMethod_, "syncGameUserId", "(Ljava/lang/String;)V");
    StaticMethod(showToastMethod_, "showToast", "(Ljava/lang/String;)V");
}


CafeListener::~CafeListener() {
    // do nothing.
}

void CafeSdk::setCafeListener(CafeListener* listener) {
    gCafeListener = listener;
}

CafeListener* CafeSdk::getCafeListener() {
    return gCafeListener;
}

void CafeSdk::init(std::string clientId, std::string clientSecret, int cafeId) {
    jstring _clientId = ENV->NewStringUTF(clientId.c_str());
    jstring _clientSecret = ENV->NewStringUTF(clientSecret.c_str());

    CALL_VOID_METHOD(SDK->initMethod_, _clientId, _clientSecret, cafeId);

    ENV->DeleteLocalRef(_clientId);
    ENV->DeleteLocalRef(_clientSecret);
}

void CafeSdk::startHome() {
    CALL_VOID_METHOD(SDK->sartHomeMethod_);
}

void CafeSdk::startNotice() {
    CALL_VOID_METHOD(SDK->startNoticeMethod_);
}

void CafeSdk::startEvent() {
    CALL_VOID_METHOD(SDK->startEventMethod_);
}

void CafeSdk::startMenu() {
    startMenu(-1);
}

void CafeSdk::startMenu(int menuId) {
    CALL_VOID_METHOD(SDK->startMenuMethod_, menuId);
}

void CafeSdk::startProfile() {
    CALL_VOID_METHOD(SDK->startProfileMethod_);
}

void CafeSdk::startMore() {
    CALL_VOID_METHOD(SDK->startMoreMethod_);
}

void CafeSdk::startWrite(int menuId, std::string subject, std::string text) {
    jstring _subject = ENV->NewStringUTF(subject.c_str());
    jstring _text = ENV->NewStringUTF(text.c_str());

    CALL_VOID_METHOD(SDK->startWriteMethod_, menuId, _subject, _text);

    ENV->DeleteLocalRef(_subject);
    ENV->DeleteLocalRef(_text);
}

void CafeSdk::startImageWrite(int menuId, std::string subject, std::string text,
        std::string imageUri) {
    jstring _subject = ENV->NewStringUTF(subject.c_str());
    jstring _text = ENV->NewStringUTF(text.c_str());
    jstring _imageUri = ENV->NewStringUTF(imageUri.c_str());

    CALL_VOID_METHOD(SDK->startImageWriteMethod_, menuId, _subject, _text, _imageUri);

    ENV->DeleteLocalRef(_subject);
    ENV->DeleteLocalRef(_text);
    ENV->DeleteLocalRef(_imageUri);
}

void CafeSdk::startVideoWrite(int menuId, std::string subject, std::string text,
        std::string videoUri) {
    jstring _subject = ENV->NewStringUTF(subject.c_str());
    jstring _text = ENV->NewStringUTF(text.c_str());
    jstring _videoUri = ENV->NewStringUTF(videoUri.c_str());

    CALL_VOID_METHOD(SDK->startVideoWriteMethod_, menuId, _subject, _text, _videoUri);

    ENV->DeleteLocalRef(_subject);
    ENV->DeleteLocalRef(_text);
    ENV->DeleteLocalRef(_videoUri);
}

void CafeSdk::syncGameUserId(std::string gameUserId) {
    jstring _gameUserId = ENV->NewStringUTF(gameUserId.c_str());

    CALL_VOID_METHOD(SDK->syncGameUserIdMethod_, _gameUserId);

    ENV->DeleteLocalRef(_gameUserId);
}

void CafeSdk::showToast(std::string text) {
    jstring _text = ENV->NewStringUTF(text.c_str());

    CALL_VOID_METHOD(SDK->showToastMethod_, _text);

    ENV->DeleteLocalRef(_text);
}

extern "C" {

JNIEXPORT void JNICALL
Java_com_naver_cafe_CafeSdk_nativeOnSdkStarted(JNIEnv* env, jobject thiz) {
    auto cafeListener = CafeSdk::getCafeListener();
    if (cafeListener == nullptr) return;
    cafeListener->onCafeSdkStarted();
}

JNIEXPORT void JNICALL
Java_com_naver_cafe_CafeSdk_nativeOnSdkStopped(JNIEnv* env, jobject thiz) {
    auto cafeListener = CafeSdk::getCafeListener();
    if (cafeListener == nullptr) return;
    cafeListener->onCafeSdkStopped();
}

JNIEXPORT void JNICALL
Java_com_naver_cafe_CafeSdk_nativeOnClickAppSchemeBanner(JNIEnv* env, jobject thiz, jstring appScheme) {
    auto cafeListener = CafeSdk::getCafeListener();
    if (cafeListener == nullptr) return;
    std::string _appScheme = PluginJniHelper::jstring2string(appScheme);
    cafeListener->onCafeSdkClickAppSchemeBanner(_appScheme);
}

JNIEXPORT void JNICALL
Java_com_naver_cafe_CafeSdk_nativeOnJoined(JNIEnv* env, jobject thiz) {
    auto cafeListener = CafeSdk::getCafeListener();
    if (cafeListener == nullptr) return;
    cafeListener->onCafeSdkJoined();
}

JNIEXPORT void JNICALL
Java_com_naver_cafe_CafeSdk_nativeOnPostedArticle(JNIEnv* env, jobject thiz, jstring appScheme, jint menuId) {
    auto cafeListener = CafeSdk::getCafeListener();
    if (cafeListener == nullptr) return;
    cafeListener->onCafeSdkPostedArticle(menuId);
}

JNIEXPORT void JNICALL
Java_com_naver_cafe_CafeSdk_nativeOnPostedComment(JNIEnv* env, jobject thiz, jint articleId) {
    auto cafeListener = CafeSdk::getCafeListener();
    if (cafeListener == nullptr) return;
    cafeListener->onCafeSdkPostedComment(articleId);
}

}

} /* namespace cafe */
