/*
 * PluginCafe.cpp
 *
 *  Created on: 2016. 3. 22.
 *      Author: naver
 */

#include "PluginCafe.h"
#include "PluginJniHelper.h"

using namespace cocos2d;

namespace cafe {

static bool getStaticMethod(PluginJniMethodInfo &methodinfo,
        const char *methodName, const char *paramCode) {
    static const char* kCafeSdkClass = "com/naver/cafe/CafeSdk";
    return PluginJniHelper::getStaticMethodInfo(methodinfo, kCafeSdkClass,
            methodName, paramCode);
}

CafeListener::~CafeListener() {
    // do nothing.
}

static CafeListener* gCafeListener = nullptr;

void CafeSdk::setCafeListener(CafeListener* listener) {
    gCafeListener = listener;
}

void CafeSdk::init(std::string clientId, std::string clientSecret, int cafeId) {
    PluginJniMethodInfo t;
    if (getStaticMethod(t, "init",
            "(Ljava/lang/String;Ljava/lang/String;I)V")) {
        jstring _clientId = t.env->NewStringUTF(clientId.c_str());
        jstring _clientSecret = t.env->NewStringUTF(clientSecret.c_str());

        t.env->CallStaticVoidMethod(t.classID, t.methodID, _clientId,
                _clientSecret, cafeId);

        t.env->DeleteLocalRef(_clientId);
        t.env->DeleteLocalRef(_clientSecret);
        t.env->DeleteLocalRef(t.classID);
    }
}

void CafeSdk::startHome() {
    PluginJniMethodInfo t;
    if (getStaticMethod(t, "startHome", "()V")) {
        t.env->CallStaticVoidMethod(t.classID, t.methodID);
        t.env->DeleteLocalRef(t.classID);
    }
}

void CafeSdk::startNotice() {
    PluginJniMethodInfo t;
    if (getStaticMethod(t, "startNotice", "()V")) {
        t.env->CallStaticVoidMethod(t.classID, t.methodID);
        t.env->DeleteLocalRef(t.classID);
    }
}

void CafeSdk::startEvent() {
    PluginJniMethodInfo t;
    if (getStaticMethod(t, "startEvent", "()V")) {
        t.env->CallStaticVoidMethod(t.classID, t.methodID);
        t.env->DeleteLocalRef(t.classID);
    }
}

void CafeSdk::startMenu() {
    startMenu(-1);
}

void CafeSdk::startMenu(int menuId) {
    PluginJniMethodInfo t;
    if (getStaticMethod(t, "startMenu", "(I)V")) {
        t.env->CallStaticVoidMethod(t.classID, t.methodID, menuId);
        t.env->DeleteLocalRef(t.classID);
    }
}

void CafeSdk::startProfile() {
    PluginJniMethodInfo t;
    if (getStaticMethod(t, "startProfile", "()V")) {
        t.env->CallStaticVoidMethod(t.classID, t.methodID);
        t.env->DeleteLocalRef(t.classID);
    }
}

void CafeSdk::startMore() {
    PluginJniMethodInfo t;
    if (getStaticMethod(t, "startMore", "()V")) {
        t.env->CallStaticVoidMethod(t.classID, t.methodID);
        t.env->DeleteLocalRef(t.classID);
    }
}

void CafeSdk::startWrite(int menuId, std::string subject, std::string text) {
    PluginJniMethodInfo t;
    if (getStaticMethod(t, "startWrite",
            "(ILjava/lang/String;Ljava/lang/String;)V")) {
        jstring _subject = t.env->NewStringUTF(subject.c_str());
        jstring _text = t.env->NewStringUTF(text.c_str());

        t.env->CallStaticVoidMethod(t.classID, t.methodID, menuId, _subject,
                _text);

        t.env->DeleteLocalRef(_subject);
        t.env->DeleteLocalRef(_text);
        t.env->DeleteLocalRef(t.classID);
    }
}

void CafeSdk::startImageWrite(int menuId, std::string subject, std::string text,
        std::string imageUri) {
    PluginJniMethodInfo t;
    if (getStaticMethod(t, "startImageWrite",
            "(ILjava/lang/String;Ljava/lang/String;Ljava/lang/String;)V")) {
        jstring _subject = t.env->NewStringUTF(subject.c_str());
        jstring _text = t.env->NewStringUTF(text.c_str());
        jstring _imageUri = t.env->NewStringUTF(imageUri.c_str());

        t.env->CallStaticVoidMethod(t.classID, t.methodID, menuId, _subject,
                _text, _imageUri);

        t.env->DeleteLocalRef(_subject);
        t.env->DeleteLocalRef(_text);
        t.env->DeleteLocalRef(_imageUri);
        t.env->DeleteLocalRef(t.classID);
    }
}

void CafeSdk::startVideoWrite(int menuId, std::string subject, std::string text,
        std::string videoUri) {
    PluginJniMethodInfo t;
    if (getStaticMethod(t, "startVideoWrite",
            "(ILjava/lang/String;Ljava/lang/String;Ljava/lang/String;)V")) {
        jstring _subject = t.env->NewStringUTF(subject.c_str());
        jstring _text = t.env->NewStringUTF(text.c_str());
        jstring _videoUri = t.env->NewStringUTF(videoUri.c_str());

        t.env->CallStaticVoidMethod(t.classID, t.methodID, menuId, _subject,
                _text, _videoUri);

        t.env->DeleteLocalRef(_subject);
        t.env->DeleteLocalRef(_text);
        t.env->DeleteLocalRef(_videoUri);
        t.env->DeleteLocalRef(t.classID);
    }
}

void CafeSdk::syncGameUserId(std::string gameUserId) {
    PluginJniMethodInfo t;
    if (getStaticMethod(t, "syncGameUserId", "(Ljava/lang/String;)V")) {
        jstring _gameUserId = t.env->NewStringUTF(gameUserId.c_str());

        t.env->CallStaticVoidMethod(t.classID, t.methodID, _gameUserId);

        t.env->DeleteLocalRef(_gameUserId);
        t.env->DeleteLocalRef(t.classID);
    }
}

void CafeSdk::showWidgetWhenUnloadSdk(bool use) {
    PluginJniMethodInfo t;
    if (getStaticMethod(t, "showWidgetWhenUnloadSdk", "(Z)V")) {
        t.env->CallStaticVoidMethod(t.classID, t.methodID, use);
        t.env->DeleteLocalRef(t.classID);
    }
}

void CafeSdk::stopWidget() {
    PluginJniMethodInfo t;
    if (getStaticMethod(t, "stopWidget", "()V")) {
        t.env->CallStaticVoidMethod(t.classID, t.methodID);
        t.env->DeleteLocalRef(t.classID);
    }
}

void CafeSdk::setUseVideoRecord(bool use) {
    PluginJniMethodInfo t;
    if (getStaticMethod(t, "setUseVideoRecord", "(Z)V")) {
        t.env->CallStaticVoidMethod(t.classID, t.methodID, use);
        t.env->DeleteLocalRef(t.classID);
    }
}

void CafeSdk::showToast(std::string text) {
    PluginJniMethodInfo t;
    if (getStaticMethod(t, "showToast", "(Ljava/lang/String;)V")) {
        jstring _text = t.env->NewStringUTF(text.c_str());

        t.env->CallStaticVoidMethod(t.classID, t.methodID, _text);

        t.env->DeleteLocalRef(_text);
        t.env->DeleteLocalRef(t.classID);
    }
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
Java_com_naver_cafe_CafeSdk_nativeOnPostedArticle(JNIEnv* env, jobject thiz, jint menuId, jint imageCount, jint videoCount) {
    if (gCafeListener == nullptr) return;
    gCafeListener->onCafeSdkPostedArticle(menuId, imageCount, videoCount);
}

JNIEXPORT void JNICALL
Java_com_naver_cafe_CafeSdk_nativeOnPostedComment(JNIEnv* env, jobject thiz, jint articleId) {
    if (gCafeListener == nullptr) return;
    gCafeListener->onCafeSdkPostedComment(articleId);
}

JNIEXPORT void JNICALL
Java_com_naver_cafe_CafeSdk_nativeOnVoted(JNIEnv* env, jobject thiz, jint articleId) {
    if (gCafeListener == nullptr) return;
    gCafeListener->onCafeSdkDidVote(articleId);
}

JNIEXPORT void JNICALL
Java_com_naver_cafe_CafeSdk_nativeOnWidgetScreenshotClick(JNIEnv* env, jobject thiz) {
    if (gCafeListener == nullptr) return;
    gCafeListener->onCafeSdkWidgetScreenshotClick();
}

JNIEXPORT void JNICALL
Java_com_naver_cafe_CafeSdk_nativeOnRecordFinished(JNIEnv* env, jobject thiz, jstring fileUri) {
    if (gCafeListener == nullptr) return;
    std::string _fileUri = PluginJniHelper::jstring2string(fileUri);
    gCafeListener->onCafeSdkOnRecordFinished(_fileUri);
}

}

} /* namespace cafe */
