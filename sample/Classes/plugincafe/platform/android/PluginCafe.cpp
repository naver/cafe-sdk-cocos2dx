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

void CafeSdk::initGlobal(std::string consummerKey, std::string consummerSecretKey, int communityNo, int loungeNo) {
    PluginJniMethodInfo t;
    if (getStaticMethod(t, "initGlobal", "(Ljava/lang/String;Ljava/lang/String;II)V")) {
        jstring _consummerKey = t.env->NewStringUTF(consummerKey.c_str());
        jstring _consummerSecretKey = t.env->NewStringUTF(consummerSecretKey.c_str());

        t.env->CallStaticVoidMethod(t.classID, t.methodID, _consummerKey, _consummerSecretKey, communityNo, loungeNo);

        t.env->DeleteLocalRef(_consummerKey);
        t.env->DeleteLocalRef(_consummerSecretKey);
        t.env->DeleteLocalRef(t.classID);
    }
}


  
void CafeSdk::setChannelCode(std::string channelCode) {
    PluginJniMethodInfo t;
    if (getStaticMethod(t, "setChannelCode", "(Ljava/lang/String;)V")) {
        jstring _channelCode = t.env->NewStringUTF(channelCode.c_str());

        t.env->CallStaticVoidMethod(t.classID, t.methodID, _channelCode);

        t.env->DeleteLocalRef(_channelCode);
        t.env->DeleteLocalRef(t.classID);
    }
}

std::string CafeSdk::getChannelCode() {
    std::string result;

    PluginJniMethodInfo t;
    if (getStaticMethod(t, "getChannelCode", "()Ljava/lang/String;")) {
        jstring jresult = (jstring) t.env->CallStaticObjectMethod(t.classID,
                t.methodID);
        result = PluginJniHelper::jstring2string(jresult);

        t.env->DeleteLocalRef(jresult);
        t.env->DeleteLocalRef(t.classID);
    }

    return result;
}

void CafeSdk::setThemeColor(std::string themeColorCSSString) {
    PluginJniMethodInfo t;
    if (getStaticMethod(t, "setThemeColor", "(Ljava/lang/String;)V")) {
        jstring _themeColorCSSString = t.env->NewStringUTF(
                themeColorCSSString.c_str());

        t.env->CallStaticVoidMethod(t.classID, t.methodID,
                _themeColorCSSString);

        t.env->DeleteLocalRef(_themeColorCSSString);
        t.env->DeleteLocalRef(t.classID);
    }
}

void CafeSdk::setThemeColor(std::string themeColorCSSString,
        std::string tabBackgroundColorCSSString) {
    PluginJniMethodInfo t;
    if (getStaticMethod(t, "setThemeColor",
            "(Ljava/lang/String;Ljava/lang/String;)V")) {
        jstring _themeColorCSSString = t.env->NewStringUTF(
                themeColorCSSString.c_str());
        jstring _tabBackgroundColorCSSString = t.env->NewStringUTF(
                tabBackgroundColorCSSString.c_str());

        t.env->CallStaticVoidMethod(t.classID, t.methodID, _themeColorCSSString,
                _tabBackgroundColorCSSString);

        t.env->DeleteLocalRef(_themeColorCSSString);
        t.env->DeleteLocalRef(_tabBackgroundColorCSSString);
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

void CafeSdk::startArticle(int articleId) {
    PluginJniMethodInfo t;
    if (getStaticMethod(t, "startArticle", "(I)V")) {
        t.env->CallStaticVoidMethod(t.classID, t.methodID, articleId);
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

void CafeSdk::startWrite() {
    PluginJniMethodInfo t;
    if (getStaticMethod(t, "startWrite", "()V")) {
        t.env->CallStaticVoidMethod(t.classID, t.methodID);
        t.env->DeleteLocalRef(t.classID);
    }
}

void CafeSdk::startImageWrite(std::string imageUri) {
    PluginJniMethodInfo t;
    if (getStaticMethod(t, "startImageWrite", "(Ljava/lang/String;)V")) {
        jstring _imageUri = t.env->NewStringUTF(imageUri.c_str());
        t.env->CallStaticVoidMethod(t.classID, t.methodID, _imageUri);
        t.env->DeleteLocalRef(_imageUri);
        t.env->DeleteLocalRef(t.classID);
    }
}

void CafeSdk::startVideoWrite(std::string videoUri) {
    PluginJniMethodInfo t;
    if (getStaticMethod(t, "startVideoWrite", "(Ljava/lang/String;)V")) {
        jstring _videoUri = t.env->NewStringUTF(videoUri.c_str());
        t.env->CallStaticVoidMethod(t.classID, t.methodID, _videoUri);
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

void CafeSdk::startWidget() {
    PluginJniMethodInfo t;
    if (getStaticMethod(t, "startWidget", "()V")) {
        t.env->CallStaticVoidMethod(t.classID, t.methodID);
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

void CafeSdk::showWidgetWhenUnloadSdk(bool use) {
    PluginJniMethodInfo t;
    if (getStaticMethod(t, "showWidgetWhenUnloadSdk", "(Z)V")) {
        t.env->CallStaticVoidMethod(t.classID, t.methodID, use);
        t.env->DeleteLocalRef(t.classID);
    }
}

void CafeSdk::setWidgetStartPosition(bool isLeft, int heightPercentage) {
    PluginJniMethodInfo t;
    if (getStaticMethod(t, "setWidgetStartPosition", "(ZI)V")) {
        t.env->CallStaticVoidMethod(t.classID, t.methodID, isLeft,
                heightPercentage);
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

void CafeSdk::setUseScreenShot(bool use) {
    PluginJniMethodInfo t;
    if (getStaticMethod(t, "setUseScreenshot", "(Z)V")) {
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

/**
 * 네이버 아이디 로그인.
 */

static NaverIdLoginListener* gNaverIdLoginListener = nullptr;
static NaverIdLoginGetProfileListener* gNaverIdLoginGetProfileListener = nullptr;

NaverIdLoginListener::~NaverIdLoginListener() {
    // do nothing.
}

NaverIdLoginGetProfileListener::~NaverIdLoginGetProfileListener() {
    // do nothing.
}

void NaverIdLogin::init(std::string clientId, std::string clientSecret) {
    CafeSdk::init(clientId, clientSecret, -1);
}

void NaverIdLogin::login(NaverIdLoginListener* listener) {
    gNaverIdLoginListener = listener;

    PluginJniMethodInfo t;
    if (getStaticMethod(t, "login", "()V")) {
        t.env->CallStaticVoidMethod(t.classID, t.methodID);
        t.env->DeleteLocalRef(t.classID);
    }
}

void NaverIdLogin::logout() {
    PluginJniMethodInfo t;
    if (getStaticMethod(t, "logout", "()V")) {
        t.env->CallStaticVoidMethod(t.classID, t.methodID);
        t.env->DeleteLocalRef(t.classID);
    }
}

bool NaverIdLogin::isLogin() {
    bool result = false;

    PluginJniMethodInfo t;
    if (getStaticMethod(t, "isLogin", "()Z")) {
        result = (bool) t.env->CallStaticBooleanMethod(t.classID, t.methodID);
        t.env->DeleteLocalRef(t.classID);
    }

    return result;
}

void NaverIdLogin::getProfile(NaverIdLoginGetProfileListener* listener) {
    gNaverIdLoginGetProfileListener = listener;

    PluginJniMethodInfo t;
    if (getStaticMethod(t, "getProfile", "()V")) {
        t.env->CallStaticVoidMethod(t.classID, t.methodID);
        t.env->DeleteLocalRef(t.classID);
    }
}

/**
 * 웹툰 통계 기능.
 */
void Statistics::sendNewUser(std::string gameUserId, std::string market) {
    PluginJniMethodInfo t;
    if (getStaticMethod(t, "sendNewUser",
            "(Ljava/lang/String;Ljava/lang/String;)V")) {
        jstring _gameUserId = t.env->NewStringUTF(gameUserId.c_str());
        jstring _market = t.env->NewStringUTF(market.c_str());

        t.env->CallStaticVoidMethod(t.classID, t.methodID, _gameUserId,
                _market);

        t.env->DeleteLocalRef(_gameUserId);
        t.env->DeleteLocalRef(_market);
        t.env->DeleteLocalRef(t.classID);
    }
}

void Statistics::sendPayUser(std::string gameUserId, double pay,
        std::string productCode, std::string currency, std::string market) {
    PluginJniMethodInfo t;
    if (getStaticMethod(t, "sendPayUser",
            "(Ljava/lang/String;DLjava/lang/String;Ljava/lang/String;Ljava/lang/String;)V")) {
        jstring _gameUserId = t.env->NewStringUTF(gameUserId.c_str());
        jstring _productCode = t.env->NewStringUTF(productCode.c_str());
        jstring _currency = t.env->NewStringUTF(currency.c_str());
        jstring _market = t.env->NewStringUTF(market.c_str());

        t.env->CallStaticVoidMethod(t.classID, t.methodID, _gameUserId, pay,
                _productCode, _currency, _market);

        t.env->DeleteLocalRef(_gameUserId);
        t.env->DeleteLocalRef(_productCode);
        t.env->DeleteLocalRef(_currency);
        t.env->DeleteLocalRef(_market);
        t.env->DeleteLocalRef(t.classID);
    }
}

/**
 * 녹화 기능.
 */

static RecordListener* gRecordListener = nullptr;

void Record::init() {
    // do nothing.
}

void Record::startRecord() {
    PluginJniMethodInfo t;
    if (getStaticMethod(t, "startRecord", "()V")) {
        t.env->CallStaticVoidMethod(t.classID, t.methodID);
        t.env->DeleteLocalRef(t.classID);
    }
}

void Record::stopRecord() {
    PluginJniMethodInfo t;
    if (getStaticMethod(t, "stopRecord", "()V")) {
        t.env->CallStaticVoidMethod(t.classID, t.methodID);
        t.env->DeleteLocalRef(t.classID);
    }
}

void Record::setRecordListener(RecordListener* listener) {
    gRecordListener = listener;
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

JNIEXPORT void JNICALL
Java_com_naver_cafe_CafeSdk_nativeOnLoggedIn(JNIEnv* env, jobject thiz, jboolean success) {
    if (gNaverIdLoginListener == nullptr) return;
    gNaverIdLoginListener->onNaverIdLoggedIn(success);
}

JNIEXPORT void JNICALL
Java_com_naver_cafe_CafeSdk_nativeOnGetProfileResult(JNIEnv* env, jobject thiz, jstring jsonString) {
    if (gNaverIdLoginGetProfileListener == nullptr) return;
    std::string _jsonString = PluginJniHelper::jstring2string(jsonString);
    gNaverIdLoginGetProfileListener->onNaverIdProfileResult(_jsonString);
}

JNIEXPORT void JNICALL
Java_com_naver_cafe_CafeSdk_nativeOnStartRecord(JNIEnv* env, jobject thiz) {
    if (gRecordListener == nullptr) return;
    gRecordListener->onSDKRecordStart();
}

JNIEXPORT void JNICALL
Java_com_naver_cafe_CafeSdk_nativeOnError(JNIEnv* env, jobject thiz) {
    if (gRecordListener == nullptr) return;
    gRecordListener->onSDKRecordError("");
}

JNIEXPORT void JNICALL
Java_com_naver_cafe_CafeSdk_nativeOnFinishRecord(JNIEnv* env, jobject thiz, jstring uriString) {
    if (gRecordListener == nullptr) return;
    std::string _uriString = PluginJniHelper::jstring2string(uriString);
    gRecordListener->onSDKRecordFinish(_uriString);
}
}

} /* namespace cafe */
