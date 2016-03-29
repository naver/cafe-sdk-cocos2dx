#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#include "NativeUtils.h"
namespace cafe { class CafeListener{ /* empty. */ }; }
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "PluginCafe.h"
#endif

class HelloWorld : public cocos2d::Layer, cafe::CafeListener
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    void menuNaverCafeSDK(cocos2d::Ref* pSender);
    void menuNaverCafeScreenShot(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);

private:

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    void initForAndroid(cocos2d::Menu* menu);
    void menuCallback(Ref* pSender);

    void onCafeSdkStarted();
    void onCafeSdkStopped();
    void onCafeSdkClickAppSchemeBanner(const std::string& appScheme);
    void onCafeSdkJoined();
    void onCafeSdkPostedArticle(int menuId);
    void onCafeSdkPostedComment(int articleId);
#endif

};

#endif // __HELLOWORLD_SCENE_H__
