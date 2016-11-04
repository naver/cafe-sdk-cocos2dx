#include "HelloWorldScene.h"

USING_NS_CC;

enum CafeSdkTags {
    kTagCafeHome,
    kTagCafeNotice,
    kTagCafeEvent,
    kTagCafeMenu,
    kTagCafeMenuById,
    kTagCafeProfile,
    kTagCafeWrite1,
    kTagCafeWrite2,
    kTagShowRecord,
    kTagSendNewUser,
    kTagSendPayUser,
};

Scene* HelloWorld::createScene() {
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
bool HelloWorld::init() {
    //////////////////////////////
    // 1. super init first
    if (!Layer::init()) {
        return false;
    }

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create("CloseNormal.png",
            "CloseSelected.png",
            CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));

    closeItem->setPosition(
            Vec2(
                    origin.x + visibleSize.width
                            - closeItem->getContentSize().width / 2,
                    origin.y + closeItem->getContentSize().height / 2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);
//    initCafeSdkButtons(menu);
    initCafeSdkMenu(menu);

    // 국내 카페 초기화.
    cafe::CafeSdk::init("197CymaStozo7X5r2qR5", "evCgKH1kJL", 28290504);

    // 글로벌 카페 초기화. 국내 카페만 사용할 경우 initGlobal을 하지 않아도 됩니다.
    cafe::CafeSdk::initGlobal("IHCd_HmSiMcXOMC37xZ8", 1013329, cafe::kLangCodeNone);
    cafe::CafeSdk::setCafeListener(this);

    return true;
}

void HelloWorld::menuCloseCallback(Ref* pSender) {
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

void HelloWorld::initCafeSdkButtons(Menu* menu) {
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto navercafe = MenuItemImage::create("icon1.png", "icon1.png",
            CC_CALLBACK_1(HelloWorld::menuCallback, this));
    navercafe->setTag(kTagCafeHome);
    navercafe->setPosition(
            Vec2(origin.x + navercafe->getContentSize().width,
                    origin.y + visibleSize.height
                            - navercafe->getContentSize().height));
    menu->addChild(navercafe);

    auto screenshot = MenuItemImage::create("icon2.png", "icon2.png",
            CC_CALLBACK_1(HelloWorld::menuCallback, this));

    screenshot->setTag(kTagCafeWrite2);
    screenshot->setPosition(
            Vec2(origin.x + screenshot->getContentSize().width,
                    origin.y + visibleSize.height
                            - navercafe->getContentSize().height * 2));
    menu->addChild(screenshot);
}

void HelloWorld::initCafeSdkMenu(Menu* menu) {
    std::vector < std::pair<int, const char*> > items;
    items.push_back(std::make_pair(kTagCafeHome, "home"));
    items.push_back(std::make_pair(kTagCafeNotice, "notice"));
    items.push_back(std::make_pair(kTagCafeEvent, "event"));
    items.push_back(std::make_pair(kTagCafeMenu, "menu"));
    items.push_back(std::make_pair(kTagCafeMenuById, "menu(id:7)"));
    items.push_back(std::make_pair(kTagCafeProfile, "profile"));
    items.push_back(std::make_pair(kTagCafeWrite1, "write1"));
    items.push_back(std::make_pair(kTagCafeWrite2, "write2"));
    items.push_back(std::make_pair(kTagShowRecord, "show record"));
    items.push_back(std::make_pair(kTagSendNewUser, "send NU"));
    items.push_back(std::make_pair(kTagSendPayUser, "send PU"));

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    float columsPosX[] = { origin.x + visibleSize.width / 6, origin.x
            + (visibleSize.width * 3) / 6, origin.x
            + (visibleSize.width * 5) / 6 };

    float step = 45.0f;
    float beginY = origin.y + visibleSize.height - step;

    for (auto it = items.begin(); it != items.end(); ++it) {
        auto item = MenuItemFont::create(it->second,
                CC_CALLBACK_1(HelloWorld::menuCallback, this));
        item->setTag(it->first);

        auto i = std::distance(items.begin(), it);
        item->setPosition(Point(columsPosX[i % 3], beginY - (i / 3) * step));
        menu->addChild(item);
    }
}

void HelloWorld::menuCallback(Ref* pSender) {
    auto item = (MenuItemFont*) pSender;

    switch (item->getTag()) {
    case kTagCafeHome:
        cafe::CafeSdk::startHome();
        break;

    case kTagCafeNotice:
        cafe::CafeSdk::startNotice();
        break;

    case kTagCafeEvent:
        cafe::CafeSdk::startEvent();
        break;

    case kTagCafeMenu:
        cafe::CafeSdk::startMenu();
        break;

    case kTagCafeMenuById:
        cafe::CafeSdk::startMenu(7);
        break;

    case kTagCafeProfile:
        cafe::CafeSdk::startProfile();
        break;

    case kTagCafeWrite1:
        cafe::CafeSdk::startWrite(-1, "subject", "text");
        break;

    case kTagCafeWrite2: {
        CCSize screenSize = Director::getInstance()->getWinSize();
        RenderTexture* texture = RenderTexture::create(screenSize.width,
                screenSize.height);
        texture->setPosition(Vec2(screenSize.width / 2, screenSize.height / 2));

        texture->begin();
        Director::getInstance()->getRunningScene()->visit();
        texture->end();

        std::string fileName = "captured_image.png";
        if (texture->saveToFile(fileName, Image::Format::PNG)) {
            std::string imageUri = FileUtils::getInstance()->getWritablePath()
                    + fileName;
            cafe::CafeSdk::startImageWrite(6, "subject", "text", imageUri);
        }
    }
        break;

    case kTagShowRecord:
        cafe::CafeSdk::setUseVideoRecord(true);
        break;

    case kTagSendNewUser:
        cafe::Statistics::sendNewUser("user", cafe::kMarketOne);
        break;

    case kTagSendPayUser:
        cafe::Statistics::sendPayUser("user", 1.f, "product1",
                cafe::kCurrencyWon, cafe::kMarketOne);
        break;

    default:
        break;
    }
}

void HelloWorld::onCafeSdkStarted() {
//    cafe::CafeSdk::showToast("onCafeSdkStarted");
}

void HelloWorld::onCafeSdkStopped() {
//    cafe::CafeSdk::showToast("onCafeSdkStopped");
}

void HelloWorld::onCafeSdkClickAppSchemeBanner(const std::string& appScheme) {
//    cafe::CafeSdk::showToast(appScheme);
}

void HelloWorld::onCafeSdkJoined() {
//    cafe::CafeSdk::showToast("onCafeSdkJoined");
}

void HelloWorld::onCafeSdkPostedArticle(int menuId, int imageCount,
        int videoCount) {
//    cafe::CafeSdk::showToast(
//            "onCafeSdkPostedArticle "
//                    + StringUtils::format("%d, %d, %d", menuId, imageCount,
//                            videoCount));
}

void HelloWorld::onCafeSdkPostedComment(int articleId) {
//    cafe::CafeSdk::showToast(
//            "onCafeSdkPostedComment " + StringUtils::format("%d", articleId));
}

void HelloWorld::onCafeSdkDidVote(int articleId) {
//    cafe::CafeSdk::showToast(
//            "onCafeSdkDidVote " + StringUtils::format("%d", articleId));
}

void HelloWorld::onCafeSdkWidgetScreenshotClick() {
    CCSize screenSize = Director::getInstance()->getWinSize();
    RenderTexture* texture = RenderTexture::create(screenSize.width,
            screenSize.height);
    texture->setPosition(Vec2(screenSize.width / 2, screenSize.height / 2));

    texture->begin();
    Director::getInstance()->getRunningScene()->visit();
    texture->end();

    std::string fileName = "captured_image.png";
    if (texture->saveToFile(fileName, Image::Format::PNG)) {
        std::string imageUri = FileUtils::getInstance()->getWritablePath()
                + fileName;
        cafe::CafeSdk::startImageWrite(-1, "", "", imageUri);
    }
}

void HelloWorld::onCafeSdkOnRecordFinished(const std::string& fileUrl) {
    cafe::CafeSdk::startVideoWrite(-1, "", "", fileUrl);
}
