/*
 * PluginCafe.cpp
 *
 *  Created on: 2016. 3. 22.
 *      Author: naver
 */

#include "PluginCafe.h"
#include "PluginJniHelper.h"

#define SDK AndroidJavaCafeSdk::sharedInstance()
#define JNI_ENV SDK->env_

#define CALL_VOID_METHOD(method, ...) \
    JNI_ENV->CallStaticVoidMethod(SDK->class_, method.methodID, ##__VA_ARGS__)

using namespace cocos2d;

namespace cafe {

struct AndroidJavaCafeSdk {
    static AndroidJavaCafeSdk* sharedInstance();

    AndroidJavaCafeSdk();

    JNIEnv* env_;
    jclass class_;

    PluginJniMethodInfo initMethod_;
    PluginJniMethodInfo sartHomeMethod_;
    PluginJniMethodInfo startNoticeMethod_;
    PluginJniMethodInfo startEventMethod_;
    PluginJniMethodInfo startMenuMethod_;
    PluginJniMethodInfo startProfileMethod_;
    PluginJniMethodInfo startMoreMethod_;
    PluginJniMethodInfo startWriteMethod_;
    PluginJniMethodInfo startImageWriteMethod_;
    PluginJniMethodInfo startVideoWriteMethod_;
    PluginJniMethodInfo syncGameUserIdMethod_;
    PluginJniMethodInfo showToastMethod_;
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
    class_ = (jclass) env_->NewGlobalRef(initMethod_.classID);

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

void CafeSdk::init(std::string clientId, std::string clientSecret, int cafeId) {
    jstring _clientId = JNI_ENV->NewStringUTF(clientId.c_str());
    jstring _clientSecret = JNI_ENV->NewStringUTF(clientSecret.c_str());

    CALL_VOID_METHOD(SDK->initMethod_, _clientId, _clientSecret, cafeId);

    JNI_ENV->DeleteLocalRef(_clientId);
    JNI_ENV->DeleteLocalRef(_clientSecret);
}

static CafeListener* gCafeListener = nullptr;

void CafeSdk::setCafeListener(CafeListener* listener) {
    gCafeListener = listener;
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
    jstring _subject = JNI_ENV->NewStringUTF(subject.c_str());
    jstring _text = JNI_ENV->NewStringUTF(text.c_str());

    CALL_VOID_METHOD(SDK->startWriteMethod_, menuId, _subject, _text);

    JNI_ENV->DeleteLocalRef(_subject);
    JNI_ENV->DeleteLocalRef(_text);
}

void CafeSdk::startImageWrite(int menuId, std::string subject, std::string text,
        std::string imageUri) {
    jstring _subject = JNI_ENV->NewStringUTF(subject.c_str());
    jstring _text = JNI_ENV->NewStringUTF(text.c_str());
    jstring _imageUri = JNI_ENV->NewStringUTF(imageUri.c_str());

    CALL_VOID_METHOD(SDK->startImageWriteMethod_, menuId, _subject, _text, _imageUri);

    JNI_ENV->DeleteLocalRef(_subject);
    JNI_ENV->DeleteLocalRef(_text);
    JNI_ENV->DeleteLocalRef(_imageUri);
}

void CafeSdk::startVideoWrite(int menuId, std::string subject, std::string text,
        std::string videoUri) {
    jstring _subject = JNI_ENV->NewStringUTF(subject.c_str());
    jstring _text = JNI_ENV->NewStringUTF(text.c_str());
    jstring _videoUri = JNI_ENV->NewStringUTF(videoUri.c_str());

    CALL_VOID_METHOD(SDK->startVideoWriteMethod_, menuId, _subject, _text, _videoUri);

    JNI_ENV->DeleteLocalRef(_subject);
    JNI_ENV->DeleteLocalRef(_text);
    JNI_ENV->DeleteLocalRef(_videoUri);
}

void CafeSdk::syncGameUserId(std::string gameUserId) {
    jstring _gameUserId = JNI_ENV->NewStringUTF(gameUserId.c_str());

    CALL_VOID_METHOD(SDK->syncGameUserIdMethod_, _gameUserId);

    JNI_ENV->DeleteLocalRef(_gameUserId);
}

void CafeSdk::showToast(std::string text) {
    jstring _text = JNI_ENV->NewStringUTF(text.c_str());

    CALL_VOID_METHOD(SDK->showToastMethod_, _text);

    JNI_ENV->DeleteLocalRef(_text);
}

extern "C" {

JNIEXPORT void JNICALL
Java_com_naver_cafe_CafeSdk_nativeOnSdkStarted(JNIEnv* env, jobject thiz) {
    if (gCafeListener == nullptr) return;
    gCafeListener->onCafeSdkStarted();
}

JNIEXPORT void JNICALL
Java_com_naver_cafe_CafeSdk_nativeOnSdkStopped(JNIEnv* env, jobject thiz) {
    if (gCafeListener == nullptr) return;
    gCafeListener->onCafeSdkStopped();
}

JNIEXPORT void JNICALL
Java_com_naver_cafe_CafeSdk_nativeOnClickAppSchemeBanner(JNIEnv* env, jobject thiz, jstring appScheme) {
    if (gCafeListener == nullptr) return;
    std::string _appScheme = PluginJniHelper::jstring2string(appScheme);
    gCafeListener->onCafeSdkClickAppSchemeBanner(_appScheme);
}

JNIEXPORT void JNICALL
Java_com_naver_cafe_CafeSdk_nativeOnJoined(JNIEnv* env, jobject thiz) {
    if (gCafeListener == nullptr) return;
    gCafeListener->onCafeSdkJoined();
}

JNIEXPORT void JNICALL
Java_com_naver_cafe_CafeSdk_nativeOnPostedArticle(JNIEnv* env, jobject thiz, jstring appScheme, jint menuId) {
    if (gCafeListener == nullptr) return;
    gCafeListener->onCafeSdkPostedArticle(menuId);
}

JNIEXPORT void JNICALL
Java_com_naver_cafe_CafeSdk_nativeOnPostedComment(JNIEnv* env, jobject thiz, jint articleId) {
    if (gCafeListener == nullptr) return;
    gCafeListener->onCafeSdkPostedComment(articleId);
}

}

} /* namespace cafe */
