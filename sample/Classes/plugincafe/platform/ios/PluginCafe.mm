/*
 * PluginCafe.cpp
 *
 *  Created on: 2016. 3. 22.
 *      Author: naver
 */

#import <NaverCafeSDK/NCSDKManager.h>
#import <NaverCafeSDK/NCSDKStatistics.h>
#import <NaverCafeSDK/NCNaverLoginManager.h>
#import <NaverCafeSDK/NCSDKRecordManager.h>
@interface CafeCallbackObject : NSObject <NCSDKManagerDelegate, NCNaverLoginManagerDelegate, NCSDKRecordManagerDelegate>
@end

#include "PluginCafe.h"
using namespace cocos2d;

static CafeCallbackObject *cafeCallbackObject = nil;

namespace cafe {

CafeListener::~CafeListener() {
    // do nothing.
}

    
void CafeSdk::init(std::string clientId, std::string clientSecret, int cafeId) {
    cafeCallbackObject = [[CafeCallbackObject alloc] init];
    
    NSString *_clientId = [NSString stringWithUTF8String:clientId.c_str()];
    NSString *_clientSecret = [NSString stringWithUTF8String:clientSecret.c_str()];
    
    [[NCSDKManager getSharedInstance] setNaverLoginClientId:_clientId
                                     naverLoginClientSecret:_clientSecret
                                                     cafeId:cafeId];
    [[NCSDKManager getSharedInstance] setOrientationIsLandscape:YES];
}
    
void CafeSdk::initGlobal(std::string clientId, int communityId) {
    CafeSdk::initGlobal(clientId, communityId, 0);
}
    
void CafeSdk::initGlobal(std::string clientId, int communityId, int channelId) {
    NSString *_clientId = [NSString stringWithUTF8String:clientId.c_str()];
    [[NCSDKManager getSharedInstance] setNeoIdConsumerKey:_clientId
                                              communityId:communityId
                                                channelId:channelId];
}
    
void CafeSdk::setChannelCode(std::string channelCode) {
    [[NCSDKManager getSharedInstance] setChannelCode:[NSString stringWithUTF8String:channelCode.c_str()]];
}
    
std::string CafeSdk::getChannelCode() {
    return [[NCSDKManager getSharedInstance].currentChannelCode UTF8String];
}
void CafeSdk::setThemeColor(std::string themeColorCSSString) {
    [[NCSDKManager getSharedInstance] setThemeColor:[NSString stringWithUTF8String:themeColorCSSString.c_str()]];
}
void CafeSdk::setThemeColor(std::string themeColorCSSString,
                            std::string tabBackgroundColorCSSString) {
    [[NCSDKManager getSharedInstance] setThemeColor:[NSString stringWithUTF8String:themeColorCSSString.c_str()]
                              andTabBackgroundColor:[NSString stringWithUTF8String:tabBackgroundColorCSSString.c_str()]];
}
    
static CafeListener* gCafeListener = nullptr;

void CafeSdk::setCafeListener(CafeListener* listener) {
    // do nothing.
    gCafeListener = listener;
}
    
void setParentViewController() {
    UIWindow *window =  [[UIApplication sharedApplication] keyWindow];
    [[NCSDKManager getSharedInstance] setParentViewController:window.rootViewController];
    [[NCSDKManager getSharedInstance] setNcSDKDelegate:cafeCallbackObject];
}
    
void CafeSdk::startHome() {
    setParentViewController();
    [[NCSDKManager getSharedInstance] presentMainViewController];
}

void CafeSdk::startNotice() {
    setParentViewController();
    [[NCSDKManager getSharedInstance] presentMainViewControllerWithTabIndex:1];
}

void CafeSdk::startEvent() {
    setParentViewController();
    [[NCSDKManager getSharedInstance] presentMainViewControllerWithTabIndex:2];
}

void CafeSdk::startMenu() {
    setParentViewController();
    [[NCSDKManager getSharedInstance] presentMainViewControllerWithTabIndex:3];
}

void CafeSdk::startProfile() {
    setParentViewController();
    [[NCSDKManager getSharedInstance] presentMainViewControllerWithTabIndex:4];
}
void CafeSdk::startArticle(int articleId) {
    setParentViewController();
    [[NCSDKManager getSharedInstance] presentMainViewControllerWithArticleId:articleId];
}
void CafeSdk::startMore() {
    setParentViewController();
    [[NCSDKManager getSharedInstance] presentEtc];
}

void CafeSdk::startWrite() {
    setParentViewController();
    [[NCSDKManager getSharedInstance] presentArticlePostViewController];
}

void CafeSdk::startImageWrite(std::string imageUri) {
    setParentViewController();
    [[NCSDKManager getSharedInstance] presentArticlePostViewControllerWithType:kGLArticlePostTypeImage
                                                                      filePath:[NSString stringWithUTF8String:imageUri.c_str()]];

}

void CafeSdk::startVideoWrite(std::string videoUri) {
    setParentViewController();
    [[NCSDKManager getSharedInstance] presentArticlePostViewControllerWithType:kGLArticlePostTypeVideo
                                                                      filePath:[NSString stringWithUTF8String:videoUri.c_str()]];

}

void CafeSdk::syncGameUserId(std::string gameUserId) {
    [[NCSDKManager getSharedInstance] syncGameUserId:[NSString stringWithUTF8String:gameUserId.c_str()]];
}

void CafeSdk::showWidgetWhenUnloadSdk(bool use) {
    [[NCSDKManager getSharedInstance] setShowWidgetWhenUnloadSDK:use];
}
void CafeSdk::setWidgetStartPosition(bool isLeft, int heightPercentage) {
    [[NCSDKManager getSharedInstance] setWidgetStartPosition:isLeft andY:heightPercentage];
}
void CafeSdk::stopWidget() {
    [[NCSDKManager getSharedInstance] stopWidget];
}
void CafeSdk::setUseVideoRecord(bool use) {
    [[NCSDKManager getSharedInstance] setUseWidgetVideoRecord:use];
}
void CafeSdk::setUseScreenShot(bool use) {
    [[NCSDKManager getSharedInstance] setUseWidgetScreenShot:use];
}
void CafeSdk::showToast(std::string text) {
    [[NCSDKManager getSharedInstance] showToast:[NSString stringWithUTF8String:text.c_str()]];
}

void Statistics::sendNewUser(std::string gameUserId, std::string market) {
    [NCSDKStatistics sendNewUser:[NSString stringWithUTF8String:gameUserId.c_str()]
                       andMarket:[NSString stringWithUTF8String:market.c_str()]];
}

void Statistics::sendPayUser(std::string gameUserId, double pay,
                             std::string productCode, std::string currency, std::string market) {
    [NCSDKStatistics sendPayUser:[NSString stringWithUTF8String:gameUserId.c_str()]
                          andPay:pay
                  andProductCode:[NSString stringWithUTF8String:productCode.c_str()]
                     andCurrency:[NSString stringWithUTF8String:currency.c_str()]
                       andMarket:[NSString stringWithUTF8String:market.c_str()]];
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
        [[NCNaverLoginManager getSharedInstance] setNcNaverLoginManagerDelegate:cafeCallbackObject];
        [[NCNaverLoginManager getSharedInstance] naverIdLogin];
    }
    
    void NaverIdLogin::logout() {
        [[NCNaverLoginManager getSharedInstance] naverIdLogout];
    }
    
    bool NaverIdLogin::isLogin() {
        return [[NCNaverLoginManager getSharedInstance] isNaverIdLogin];
    }
    
    void NaverIdLogin::getProfile(NaverIdLoginGetProfileListener* listener) {
        gNaverIdLoginGetProfileListener = listener;
    }

    /*
     * Record
     */
    void Record::init() {
        UIWindow *window =  [[UIApplication sharedApplication] keyWindow];
        [[NCSDKRecordManager getSharedInstance] setBaseViewController:window.rootViewController];
        [NCSDKRecordManager getSharedInstance].ncSDKRecordDelegate = cafeCallbackObject;
    }
    void Record::startRecord() {
        [[NCSDKRecordManager getSharedInstance] startRecord];
    }
    
    void Record::stopRecord() {
        [[NCSDKRecordManager getSharedInstance] stopRecord];
    }

    static RecordListener* recordListener = nullptr;
    
    void Record::setRecordListener(RecordListener* listener) {
        recordListener = listener;
    }
    
    
} /* namespace cafe */


@implementation CafeCallbackObject
#pragma mark - NCSDKDelegate
- (void)ncSDKViewDidLoad {
    cafe::gCafeListener->onCafeSdkStarted();
}
- (void)ncSDKViewDidUnLoad {
    cafe::gCafeListener->onCafeSdkStopped();
}
- (void)ncSDKJoinedCafeMember {
    cafe::gCafeListener->onCafeSdkJoined();
}
- (void)ncSDKPostedArticleAtMenu:(NSInteger)menuId
                attachImageCount:(NSInteger)imageCount
                attachVideoCount:(NSInteger)videoCount {
    dispatch_after(dispatch_time(DISPATCH_TIME_NOW, (int64_t)(0.6 * NSEC_PER_SEC)), dispatch_get_main_queue(), ^{
        cafe::gCafeListener->onCafeSdkPostedArticle((int)menuId, (int)imageCount, (int)videoCount);
    });
}
- (void)ncSDKPostedCommentAtArticle:(NSInteger)articleId {
    dispatch_after(dispatch_time(DISPATCH_TIME_NOW, (int64_t)(0.6 * NSEC_PER_SEC)), dispatch_get_main_queue(), ^{
        cafe::gCafeListener->onCafeSdkPostedComment((int)articleId);
    });
}
- (void)ncSDKRequestScreenShot {
    cafe::gCafeListener->onCafeSdkWidgetScreenshotClick();
}
- (void)ncSDKDidVoteAtArticle:(NSInteger)articleId {
    cafe::gCafeListener->onCafeSdkDidVote((int)articleId);
}

- (void)ncSDKWidgetPostArticleWithImage {
    cafe::gCafeListener->onCafeSdkWidgetScreenshotClick();
}
- (void)ncSDKWidgetSuccessVideoRecord {
    cafe::gCafeListener->onCafeSdkOnRecordFinished("");
}
- (void)ncSDKAppSchemeBanner:(NSString *)appScheme {
    std::string appSchemeResult = std::string([appScheme UTF8String]);
    cafe::gCafeListener->onCafeSdkClickAppSchemeBanner(appSchemeResult);
}
#pragma mark - NCWidgetDelegate
- (void)ncWidgetPostArticle {
    cafe::CafeSdk::startWrite();
}
- (void)ncWidtetExecuteGLink {
    cafe::CafeSdk::startHome();
}
- (void)ncWidgetPostArticleWithImage {
    cafe::gCafeListener->onCafeSdkWidgetScreenshotClick();
}

#pragma mark - NCNaverLoginManagerDelegate
- (void)ncSDKLoginCallback {
    cafe::gNaverIdLoginListener->onNaverIdLoggedIn(true);
}
- (void)ncSDKGetProfile:(NSString *)result {
    std::string jsonResult = std::string([result UTF8String]);
    cafe::gNaverIdLoginGetProfileListener->onNaverIdProfileResult(jsonResult);
}

#pragma mark - NCSDKRecordDelegate
- (void)ncSDKRecordStart {
    cafe::recordListener->onSDKRecordStart();
}
- (void)ncSDKRecordError:(NSString *)errorMsg {
    std::string error = std::string([errorMsg UTF8String]);
    cafe::recordListener->onSDKRecordError(error);
}
- (void)ncSDKRecordFinish {
    cafe::recordListener->onSDKRecordFinish("");
}
- (void)ncSDKRecordFinishWithPreview {
    cafe::recordListener->onSDKRecordFinishWithPreview();
}

@end
