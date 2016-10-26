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

/* 글로벌 언어 코드 상수 */
static const std::string kLangCodeNone = ""; // 서버에서 설정한 디폴트 언어 사용.
static const std::string kLangCodeKorean = "ko"; // 국내 카페로 초기화 된다.
static const std::string kLangCodeEnglish = "en";
static const std::string kLangCodeJapanese = "ja";
static const std::string kLangCodeChineseSimplified = "zh_CN";
static const std::string kLangCodeChineseTraditional = "zh_TW";
static const std::string kLangCodeThai = "th";
static const std::string kLangCodeSpanish = "es";
static const std::string kLangCodeGerman = "de";
static const std::string kLangCodeFrench = "fr";
static const std::string kLangCodeRussian = "ru";
static const std::string kLangCodeIndonesian = "id";
static const std::string kLangCodeVietnamese = "vi";
static const std::string kLangCodeItalian = "it";
static const std::string kLangCodePortuguese = "pt";
static const std::string kLangCodeTurkish = "tr";

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

    static void initGlobal(std::string clientId, int cafeId,
            std::string defaultCafeLangCode);

    static void setCafeLangCode(std::string cafeLangCode);
    static std::string getCafeLangCode();

    static void setCafeListener(CafeListener* listener);

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

} /* namespace cafe */

#endif /* JNI_PLUGINCAFE_PLUGINCAFE_H_ */
