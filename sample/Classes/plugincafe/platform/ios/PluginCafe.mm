/*
 * PluginCafe.cpp
 *
 *  Created on: 2016. 3. 22.
 *      Author: naver
 */

#import <NaverCafeSDK/NCSDKManager.h>
#import <NaverCafeSDK/NCSDKStatistics.h>
@interface CafeCallbackObject : NSObject <NCSDKManagerDelegate>
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
    
void CafeSdk::initGlobal(std::string clientId, int cafeId, std::string defaultCafeLangCode) {
    NSString *_clientId = [NSString stringWithUTF8String:clientId.c_str()];
    NSString *_defaultCafeLangCode = [NSString stringWithUTF8String:defaultCafeLangCode.c_str()];
    
    [[NCSDKManager getSharedInstance] setCountry:_defaultCafeLangCode];
    [[NCSDKManager getSharedInstance] setNeoIdConsumerKey:_clientId
                                             globalCafeId:cafeId];
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

void CafeSdk::startMenu(int menuId) {
    setParentViewController();
    [[NCSDKManager getSharedInstance] presentArticleListViewControllerWithMenuId:menuId];
}

void CafeSdk::startProfile() {
    setParentViewController();
    [[NCSDKManager getSharedInstance] presentMainViewControllerWithTabIndex:4];
}

void CafeSdk::startMore() {
    // do nothing.
}

void CafeSdk::startWrite(int menuId, std::string subject, std::string text) {
    setParentViewController();
    [[NCSDKManager getSharedInstance] presentArticlePostViewControllerWithMenuId:menuId
                                                                         subject:[NSString stringWithUTF8String:subject.c_str()]
                                                                         content:[NSString stringWithUTF8String:text.c_str()]];
}

void CafeSdk::startImageWrite(int menuId, std::string subject, std::string text,
        std::string imageUri) {
    setParentViewController();
    [[NCSDKManager getSharedInstance] presentArticlePostViewControllerWithType:kGLArticlePostTypeImage
                                                                        menuId:menuId
                                                                       subject:[NSString stringWithUTF8String:subject.c_str()]
                                                                       content:[NSString stringWithUTF8String:text.c_str()]
                                                                      filePath:[NSString stringWithUTF8String:imageUri.c_str()]];

}

void CafeSdk::startVideoWrite(int menuId, std::string subject, std::string text,
        std::string videoUri) {
    setParentViewController();
    [[NCSDKManager getSharedInstance] presentArticlePostViewControllerWithType:kGLArticlePostTypeVideo
                                                                        menuId:menuId
                                                                       subject:[NSString stringWithUTF8String:subject.c_str()]
                                                                       content:[NSString stringWithUTF8String:text.c_str()]
                                                                      filePath:[NSString stringWithUTF8String:videoUri.c_str()]];

}

void CafeSdk::syncGameUserId(std::string gameUserId) {
    [[NCSDKManager getSharedInstance] syncGameUserId:[NSString stringWithUTF8String:gameUserId.c_str()]];
}

void CafeSdk::showWidgetWhenUnloadSdk(bool use) {
    [[NCSDKManager getSharedInstance] setShowWidgetWhenUnloadSDK:use];
}
void CafeSdk::stopWidget() {
    [[NCSDKManager getSharedInstance] stopWidget];
}
void CafeSdk::setUseVideoRecord(bool use) {
    [[NCSDKManager getSharedInstance] setUseWidgetVideoRecord:use];
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
    cafe::gCafeListener->onCafeSdkOnRecordFinished(nil);
}

#pragma mark - NCWidgetDelegate
- (void)ncWidgetPostArticle {
    cafe::CafeSdk::startWrite(10, "subject", "text");
}
- (void)ncWidtetExecuteGLink {
    cafe::CafeSdk::startHome();
}
- (void)ncWidgetPostArticleWithImage {
    cafe::gCafeListener->onCafeSdkWidgetScreenshotClick();
}
@end
