#include "HelloWorldScene.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    /////////////////////////////
    // 3. add your codes below...
    auto navercafe = MenuItemImage::create(
                                           "icon1.png",
                                           "icon1.png",
                                           CC_CALLBACK_1(HelloWorld::menuNaverCafeSDK, this));

    navercafe->setPosition(Vec2(origin.x + navercafe->getContentSize().width,
                                origin.y + visibleSize.height - navercafe->getContentSize().height));
    menu->addChild(navercafe);

    auto screenshot = MenuItemImage::create(
                                           "icon2.png",
                                           "icon2.png",
                                           CC_CALLBACK_1(HelloWorld::menuNaverCafeScreenShot, this));

    screenshot->setPosition(Vec2(origin.x + screenshot->getContentSize().width,
                                origin.y + visibleSize.height - navercafe->getContentSize().height * 2));
    menu->addChild(screenshot);

    // add a label shows "Hello World"
    // create and initialize a label

    auto label = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);

    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(label, 1);

    // add "HelloWorld" splash screen"
    auto sprite = Sprite::create("HelloWorld.png");

    // position the sprite on the center of the screen
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    // add the sprite as a child to this layer
    this->addChild(sprite, 0);

    NativeUtils::sharedInstance();
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    initForAndroid(menu);
#endif

    return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

void HelloWorld::menuNaverCafeSDK(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    NativeUtils::sharedInstance().navercafe();
#endif
}

void HelloWorld::menuNaverCafeScreenShot(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    NativeUtils::sharedInstance().screenshot();
#endif
}

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)

static const std::string gActions[] = {
    "home",
    "notice",
    "event",
    "menu",
    "menu(id:7)",
    "profile",
    "write1",
    "write2",
};

void HelloWorld::menuCallback(Ref* pSender) {
    auto item = (MenuItemFont*) pSender;
    auto action = gActions[item->getTag()];

    if ("home" == action) {
        cafe::CafeSdk::startHome();
    } else if ("notice" == action) {
        cafe::CafeSdk::startNotice();
    } else if ("event" == action) {
        cafe::CafeSdk::startEvent();
    } else if ("menu" == action) {
        cafe::CafeSdk::startMenu();
    } else if ("menu(id:7)" == action) {
        cafe::CafeSdk::startMenu(7);
    } else if ("profile" == action) {
        cafe::CafeSdk::startProfile();
    } else if ("write1" == action) {
        cafe::CafeSdk::startWrite(-1, "subject", "text");
    } else if ("write2" == action) {
        CCSize screenSize = Director::getInstance()->getWinSize();
        RenderTexture* texture = RenderTexture::create(screenSize.width, screenSize.height);
        texture->setPosition(Vec2(screenSize.width / 2, screenSize.height / 2));

        texture->begin();
        Director::getInstance()->getRunningScene()->visit();
        texture->end();

        std::string fileName = "captured_image.png";
        if (texture->saveToFile(fileName, Image::Format::PNG)) {
            std::string imageUri = "file://" + FileUtils::getInstance()->getWritablePath() + fileName;
            cafe::CafeSdk::startImageWrite(5, "subject", "text", imageUri);
        }
    }
}

void HelloWorld::initForAndroid(Menu* menu) {
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    float columsPosX[] = {
        origin.x + visibleSize.width / 6,
        origin.x + (visibleSize.width * 3) / 6,
        origin.x + (visibleSize.width * 5) / 6
    };

    float step = 45.0f;
    float beginY = origin.y + visibleSize.height - step;

    int actionCount = sizeof(gActions) / sizeof(std::string);
    for (int i = 0; i < actionCount; ++i) {
        std::string action = gActions[i];
        auto item = MenuItemFont::create(action.c_str(), CC_CALLBACK_1(HelloWorld::menuCallback, this));
        item->setTag(i);
        item->setPosition(Point(columsPosX[i % 3], beginY - (i / 3) * step));
        menu->addChild(item);
    }

    cafe::CafeSdk::init("197CymaStozo7X5r2qR5", "evCgKH1kJL", 28290504);
    cafe::CafeSdk::setCafeListener(this);
}

void HelloWorld::onCafeSdkStarted() {
    cafe::CafeSdk::showToast("onCafeSdkStarted");
}

void HelloWorld::onCafeSdkStopped() {
    cafe::CafeSdk::showToast("onCafeSdkStopped");
}

void HelloWorld::onCafeSdkClickAppSchemeBanner(const std::string& appScheme) {
    cafe::CafeSdk::showToast(appScheme);
}

void HelloWorld::onCafeSdkJoined() {
    cafe::CafeSdk::showToast("onCafeSdkJoined");
}

void HelloWorld::onCafeSdkPostedArticle(int menuId) {
    cafe::CafeSdk::showToast("onCafeSdkPostedArticle");
}

void HelloWorld::onCafeSdkPostedComment(int articleId) {
    cafe::CafeSdk::showToast("onCafeSdkPostedComment");
}

#endif
