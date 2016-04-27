/*
 * PluginCafe.cpp
 *
 *  Created on: 2016. 3. 22.
 *      Author: naver
 */

#import <NaverCafeSDK/NCSDKManager.h>

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
    [[NCSDKManager getSharedInstance] setNcSDKDelegate:cafeCallbackObject];
    [[NCSDKManager getSharedInstance] setOrientationIsLandscape:YES];
}

static CafeListener* gCafeListener = nullptr;

void CafeSdk::setCafeListener(CafeListener* listener) {
    // do nothing.
    gCafeListener = listener;
}

void CafeSdk::startHome() {
    UIWindow *window =  [[UIApplication sharedApplication] keyWindow];
    [[NCSDKManager getSharedInstance] setParentViewController:window.rootViewController];
    [[NCSDKManager getSharedInstance] presentMainViewController];
}

void CafeSdk::startNotice() {
    UIWindow *window =  [[UIApplication sharedApplication] keyWindow];
    [[NCSDKManager getSharedInstance] setParentViewController:window.rootViewController];
    [[NCSDKManager getSharedInstance] presentMainViewControllerWithTabIndex:1];
}

void CafeSdk::startEvent() {
    UIWindow *window =  [[UIApplication sharedApplication] keyWindow];
    [[NCSDKManager getSharedInstance] setParentViewController:window.rootViewController];
    [[NCSDKManager getSharedInstance] presentMainViewControllerWithTabIndex:2];
}

void CafeSdk::startMenu() {
    UIWindow *window =  [[UIApplication sharedApplication] keyWindow];
    [[NCSDKManager getSharedInstance] setParentViewController:window.rootViewController];
    [[NCSDKManager getSharedInstance] presentMainViewControllerWithTabIndex:3];
}

void CafeSdk::startMenu(int menuId) {
    UIWindow *window =  [[UIApplication sharedApplication] keyWindow];
    [[NCSDKManager getSharedInstance] setParentViewController:window.rootViewController];
    [[NCSDKManager getSharedInstance] presentMainViewControllerWithTabIndex:menuId];
}

void CafeSdk::startProfile() {
    UIWindow *window =  [[UIApplication sharedApplication] keyWindow];
    [[NCSDKManager getSharedInstance] setParentViewController:window.rootViewController];
    [[NCSDKManager getSharedInstance] presentMainViewControllerWithTabIndex:4];
}

void CafeSdk::startMore() {
    // do nothing.
}

void CafeSdk::startWrite(int menuId, std::string subject, std::string text) {
    UIWindow *window =  [[UIApplication sharedApplication] keyWindow];
    [[NCSDKManager getSharedInstance] setParentViewController:window.rootViewController];
    [[NCSDKManager getSharedInstance] presentArticlePostViewControllerWithMenuId:menuId
                                                                         subject:[NSString stringWithUTF8String:subject.c_str()]
                                                                         content:[NSString stringWithUTF8String:text.c_str()]];
}

void CafeSdk::startImageWrite(int menuId, std::string subject, std::string text,
        std::string imageUri) {
    UIWindow *window =  [[UIApplication sharedApplication] keyWindow];
    [[NCSDKManager getSharedInstance] setParentViewController:window.rootViewController];
    [[NCSDKManager getSharedInstance] presentArticlePostViewControllerWithType:kGLArticlePostTypeImage
                                                                        menuId:menuId
                                                                       subject:[NSString stringWithUTF8String:subject.c_str()]
                                                                       content:[NSString stringWithUTF8String:text.c_str()]
                                                                      filePath:[NSString stringWithUTF8String:imageUri.c_str()]];

}

void CafeSdk::startVideoWrite(int menuId, std::string subject, std::string text,
        std::string videoUri) {
    UIWindow *window =  [[UIApplication sharedApplication] keyWindow];
    [[NCSDKManager getSharedInstance] setParentViewController:window.rootViewController];
    [[NCSDKManager getSharedInstance] presentArticlePostViewControllerWithType:kGLArticlePostTypeVideo
                                                                        menuId:menuId
                                                                       subject:[NSString stringWithUTF8String:subject.c_str()]
                                                                       content:[NSString stringWithUTF8String:text.c_str()]
                                                                      filePath:[NSString stringWithUTF8String:videoUri.c_str()]];

}

void CafeSdk::syncGameUserId(std::string gameUserId) {
    [[NCSDKManager getSharedInstance] syncGameUserId:[NSString stringWithUTF8String:gameUserId.c_str()]];
}

void CafeSdk::showToast(std::string text) {
    [[NCSDKManager getSharedInstance] showToast:[NSString stringWithUTF8String:text.c_str()]];
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
- (void)ncSDKPostedArticleAtMenu:(NSInteger)menuId {
    dispatch_after(dispatch_time(DISPATCH_TIME_NOW, (int64_t)(0.6 * NSEC_PER_SEC)), dispatch_get_main_queue(), ^{
        cafe::gCafeListener->onCafeSdkPostedArticle((int)menuId);
    });
}
- (void)ncSDKPostedCommentAtArticle:(NSInteger)articleId {
    dispatch_after(dispatch_time(DISPATCH_TIME_NOW, (int64_t)(0.6 * NSEC_PER_SEC)), dispatch_get_main_queue(), ^{
        cafe::gCafeListener->onCafeSdkPostedComment((int)articleId);
    });
}
@end
