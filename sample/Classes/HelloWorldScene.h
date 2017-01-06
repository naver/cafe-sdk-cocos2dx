#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "PluginCafe.h"

class HelloWorld: public cocos2d::Layer,
        cafe::CafeListener,
        cafe::NaverIdLoginListener,
        cafe::NaverIdLoginGetProfileListener {
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);

    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);

private:
    void initCafeSdkButtons(cocos2d::Menu* menu);
    void initCafeSdkMenu(cocos2d::Menu* menu);

    void menuCallback(Ref* pSender);

    void onCafeSdkStarted();
    void onCafeSdkStopped();
    void onCafeSdkClickAppSchemeBanner(const std::string& appScheme);
    void onCafeSdkJoined();
    void onCafeSdkPostedArticle(int menuId, int imageCount, int videoCount);
    void onCafeSdkPostedComment(int articleId);
    void onCafeSdkDidVote(int articleId);
    void onCafeSdkWidgetScreenshotClick();
    void onCafeSdkOnRecordFinished(const std::string& fileUrl);

    void onNaverIdLoggedIn(bool success);
    void onNaverIdProfileResult(std::string jsonString);
};

#endif // __HELLOWORLD_SCENE_H__
