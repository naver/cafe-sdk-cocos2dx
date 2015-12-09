
#import "NativeUtils.h"
#import "cocos2d.h"
#import <NaverCafeSDK/NCSDKManager.h>

using namespace cocos2d;

NativeUtils::NativeUtils()
{
}

#pragma mark - Singleton
NativeUtils& NativeUtils::sharedInstance()
{
    static NativeUtils instance;
    return instance;
}

void NativeUtils::navercafe()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    UIWindow *window =  [[UIApplication sharedApplication] keyWindow];
    [[NCSDKManager getSharedInstance] setParentViewController:window.rootViewController];
    [[NCSDKManager getSharedInstance] presentMainViewController];
#endif
}
void NativeUtils::screenshot()
{
    CCSize screenSize = Director::getInstance()->getWinSize();
    RenderTexture * tex = RenderTexture::create(screenSize.width, screenSize.height);
    tex->setPosition(Vec2(screenSize.width / 2, screenSize.height / 2));
    
    tex->begin();
    Director::getInstance()->getRunningScene()->visit();
    tex->end();
    tex->saveToFile("GLAttachImage.png", Image::Format::PNG);
 
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    NSArray *paths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);
    NSString *documentsPath = [paths objectAtIndex:0]; //Get the docs directory
    NSString *filePath = [documentsPath stringByAppendingPathComponent:@"GLAttachImage.png"]; //Add the file name
    UIWindow *window =  [[UIApplication sharedApplication] keyWindow];
    [[NCSDKManager getSharedInstance] setParentViewController:window.rootViewController];
    [[NCSDKManager getSharedInstance] presentArticlePostViewControllerWithType:kGLArticlePostTypeImage menuId:10 subject:@"끝나지않는 터널" content:@"제 위치는요~" filePath:filePath];
#endif
}
