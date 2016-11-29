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
static const std::string kChannelCodeNone = ""; // 서버에서 설정한 디폴트 언어 사용.
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
static const std::string kChannelCodeIndonesian = "id";
static const std::string kChannelCodeVietnamese = "vi";
static const std::string kChannelCodeItalian = "it";
static const std::string kChannelCodePortuguese = "pt";
static const std::string kChannelCodeTurkish = "tr";

/* SDK 종료 버튼 타입 */
enum XButtonType {
    kXButtonTypeMinimize = 0, kXButtonTypeClose = 1
};

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

    static void initGlobal(std::string clientId, int plugId,
            std::string defaultChannelCode);

    static void setChannelCode(std::string channelCode);
    static std::string getChannelCode();

    static void setThemeColor(std::string themeColorCSSString);
    static void setThemeColor(std::string themeColorCSSString,
            std::string tabBackgroundColorCSSString);

    static void setCafeListener(CafeListener* listener);

    static void setXButtonType(XButtonType type);

    static void startHome();
    static void startNotice();
    static void startEvent();
    static void startMenu();
    static void startMenu(int menuId);
    static void startProfile();
    static void startMore();

    static void startWrite(int menuId, std::string subject, std::string text);
    static void startImageWrite(int menuId, std::string subject,
            std::string text, std::string imageUri);
    static void startVideoWrite(int menuId, std::string subject,
            std::string text, std::string videoUri);

    /* 게임 아이디와 카페 아이디를 연동합니다. */
    static void syncGameUserId(std::string gameUserId);

    static void showWidgetWhenUnloadSdk(bool use);
    static void stopWidget();
    static void setUseVideoRecord(bool use);

    static void showToast(std::string text);
};

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
} /* namespace cafe */

#endif /* JNI_PLUGINCAFE_PLUGINCAFE_H_ */
