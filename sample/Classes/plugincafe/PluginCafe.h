/*
 * PluginCafe.h
 *
 *  Created on: 2016. 3. 22.
 *      Author: naver
 */

#ifndef JNI_PLUGINCAFE_PLUGINCAFE_H_
#define JNI_PLUGINCAFE_PLUGINCAFE_H_

#include <string>

namespace cafe {

/* 글로벌 채널 코드 상수 */
static const std::string kChannelCodeNone = ""; // 디바이스 언어로 세팅
static const std::string kChannelCodeKorean = "ko"; // 국내 카페로 초기화 된다.
static const std::string kChannelCodeEnglish = "en";
static const std::string kChannelCodeJapanese = "ja";
static const std::string kChannelCodeChineseSimplified = "zh_CN";
static const std::string kChannelCodeChineseTraditional = "zh_TW";
static const std::string kChannelCodeThai = "th";
static const std::string kChannelCodeSpanish = "es";
static const std::string kChannelCodeGerman = "de";
static const std::string kChannelCodeFrench = "fr";
static const std::string kChannelCodeRussian = "ru";
static const std::string kChannelCodeIndonesian = "in";
static const std::string kChannelCodeVietnamese = "vi";
static const std::string kChannelCodeItalian = "it";
static const std::string kChannelCodePortuguese = "pt";
static const std::string kChannelCodeTurkish = "tr";

class CafeListener {
public:
    virtual void onCafeSdkStarted() = 0;
    virtual void onCafeSdkStopped() = 0;
    virtual void onCafeSdkClickAppSchemeBanner(
            const std::string& appScheme) = 0;
    virtual void onCafeSdkJoined() = 0;
    virtual void onCafeSdkPostedArticle(int menuId, int imageCount,
            int videoCount) = 0;
    virtual void onCafeSdkPostedComment(int articleId) = 0;
    virtual void onCafeSdkDidVote(int articleId) = 0;
    virtual void onCafeSdkWidgetScreenshotClick() = 0;
    virtual void onCafeSdkOnRecordFinished(const std::string& fileUrl) = 0;
    virtual ~CafeListener();
};

class CafeSdk {
public:
    /* 네아로 정보와 카페 아이디로 sdk 초기화 합니다. */
    static void init(std::string clientId, std::string clientSecret,
            int cafeId);

    static void initGlobal(std::string consummerKey, std::string consummerSecretKey, int communityNo, int loungeNo);
    
    static void setChannelCode(std::string channelCode);
    static std::string getChannelCode();

    static void setThemeColor(std::string themeColorCSSString);
    static void setThemeColor(std::string themeColorCSSString,
            std::string tabBackgroundColorCSSString);

    static void setCafeListener(CafeListener* listener);

    static void startHome();
    static void startNotice();
    static void startEvent();
    static void startMenu();
    static void startProfile();
    static void startArticle(int articleId);
    static void startMore();

    static void startWrite();
    static void startImageWrite(std::string imageUri);
    static void startVideoWrite(std::string videoUri);

    /* 게임 아이디와 카페 아이디를 연동합니다. */
    static void syncGameUserId(std::string gameUserId);

    static void startWidget();
    static void stopWidget();
    static void showWidgetWhenUnloadSdk(bool use);
    static void setWidgetStartPosition(bool isLeft, int heightPercentage);

    static void setUseVideoRecord(bool use);
    static void setUseScreenShot(bool use);
    
    static void showToast(std::string text);
};

/**
 * 네이버 아이디 로그인.
 *
 * docs: https://developers.naver.com/docs/login/overview
 */
class NaverIdLoginListener {
public:
    virtual void onNaverIdLoggedIn(bool success) = 0;
    virtual ~NaverIdLoginListener();
};

class NaverIdLoginGetProfileListener {
public:
    virtual void onNaverIdProfileResult(std::string jsonString) = 0;
    virtual ~NaverIdLoginGetProfileListener();
};

class NaverIdLogin {
public:
    static void init(std::string clientId, std::string clientSecret);
    static void login(NaverIdLoginListener* listener);
    static void logout();
    static bool isLogin();

    /* docs: https://developers.naver.com/docs/login/profile */
    static void getProfile(NaverIdLoginGetProfileListener* listener);
};

/**
 * 웹툰 통계 기능.
 */

/* 통계 관련 상수. */
static const std::string kCurrencyNone = "NONE";
static const std::string kCurrencyWon = "WON";
static const std::string kCurrencyDollar = "DOLLAR";

static const std::string kMarketNone = "NONE";
static const std::string kMarketOne = "ONE";
static const std::string kMarketGoogle = "GOOGLE";
static const std::string kMarketApple = "APPLE";

class Statistics {
public:

    static void sendNewUser(std::string gameUserId, std::string market);

    static void sendPayUser(std::string gameUserId, double pay,
            std::string productCode, std::string currency, std::string market);
};
    
/**
 * 녹화 기능.
 */
class RecordListener {
public:
    virtual void onSDKRecordStart() = 0;
    virtual void onSDKRecordError(const std::string& errorMsg) = 0;
    virtual void onSDKRecordFinish(const std::string& uri) = 0;
    virtual void onSDKRecordFinishWithPreview() = 0;// 녹화 영상 프리뷰 화면이 닫힐때 호출됩니다.(iOS에서만 동작)
};

class Record {
public:
    static void init();
    static void startRecord();
    static void stopRecord();
    static void setRecordListener(RecordListener* listener);
};

} /* namespace cafe */

#endif /* JNI_PLUGINCAFE_PLUGINCAFE_H_ */
