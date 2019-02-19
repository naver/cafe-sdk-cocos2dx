#include "HelloWorldScene.h"

USING_NS_CC;

enum CafeSdkTags {
    kTagHome,
    kTagNotice,
    kTagEvent,
    kTagMenu,
    kTagProfile,
    kTagArticle,
    kTagWrite1,
    kTagWrite2,
    kTagLogin,
    kTagLogout,
    kTagIsLogin,
    kTagGetProfile,
    kTagShowRecord,
    kTagShowScreenShot,
    kTagSendNewUser,
    kTagSendPayUser,
};

static void showToast(std::string text) {
    // cafe::CafeSdk::showToast(text);
}

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
    this->addChild(menu, 0);
    //initCafeSdkButtons(menu);
    initCafeSdkMenu(menu);

    // 국내 카페 초기화.
    cafe::CafeSdk::init("197CymaStozo7X5r2qR5", "evCgKH1kJL", 28290504);

    // 글로벌 카페 초기화. 국내 카페만 사용할 경우 initGlobal을 하지 않아도 됩니다.
    cafe::CafeSdk::initGlobal("PLUGTESTKEY", "PLUGTESTSECRET", 1, 58);
    cafe::CafeSdk::setCafeListener(this);

    /*
     * 테마 설정.
     * - theme color는 css color 포맷으로 설정하시면 됩니다.
     * - 다만, theme color에 alpha값이 없어야 합니다.
     */
    cafe::CafeSdk::setThemeColor("#2e65d9", "#44484e");

    /*
     * 녹화 API
     */
    cafe::Record::init();
    cafe::Record::setRecordListener(this);

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
    navercafe->setTag(kTagHome);
    navercafe->setPosition(
            Vec2(origin.x + navercafe->getContentSize().width,
                    origin.y + visibleSize.height
                            - navercafe->getContentSize().height));
    menu->addChild(navercafe);

//    auto screenshot = MenuItemImage::create("icon2.png", "icon2.png",
//            CC_CALLBACK_1(HelloWorld::menuCallback, this));
//
//    screenshot->setTag(kTagWrite2);
//    screenshot->setPosition(
//            Vec2(origin.x + screenshot->getContentSize().width,
//                    origin.y + visibleSize.height
//                            - navercafe->getContentSize().height * 2));
//    menu->addChild(screenshot);
}

void HelloWorld::initCafeSdkMenu(Menu* menu) {
    std::vector < std::pair<int, const char*> > items;
    items.push_back(std::make_pair(kTagHome, "home"));
    items.push_back(std::make_pair(kTagNotice, "notice"));
    items.push_back(std::make_pair(kTagEvent, "event"));
    items.push_back(std::make_pair(kTagMenu, "menu"));
    items.push_back(std::make_pair(kTagProfile, "profile"));
    items.push_back(std::make_pair(kTagArticle, "article"));
    items.push_back(std::make_pair(kTagWrite1, "write1"));
    items.push_back(std::make_pair(kTagWrite2, "write2"));
    items.push_back(std::make_pair(kTagLogin, "login"));
    items.push_back(std::make_pair(kTagLogout, "logout"));
    items.push_back(std::make_pair(kTagIsLogin, "is login"));
    items.push_back(std::make_pair(kTagGetProfile, "get profile"));
    items.push_back(std::make_pair(kTagShowRecord, "show record"));
    items.push_back(std::make_pair(kTagSendNewUser, "send NU"));
    items.push_back(std::make_pair(kTagSendPayUser, "send PU"));

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    float columsPosX[] = { origin.x + visibleSize.width / 6, origin.x
            + (visibleSize.width * 3) / 6, origin.x
            + (visibleSize.width * 5) / 6 };

    float step = 38.0f;
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
    case kTagHome:
        cafe::CafeSdk::startHome();
        break;

    case kTagNotice:
        cafe::CafeSdk::startNotice();
        break;

    case kTagEvent:
        cafe::CafeSdk::startEvent();
        break;

    case kTagMenu:
        cafe::CafeSdk::startMenu(9);
        break;

    case kTagProfile:
        cafe::CafeSdk::startProfile();
        break;

    case kTagArticle:
        cafe::CafeSdk::startArticle(1);
        break;

    case kTagWrite1:
        cafe::CafeSdk::startWrite();
        break;

    case kTagWrite2: {
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
            cafe::CafeSdk::startImageWrite(imageUri);
        }
    }
        break;

    case kTagLogin:
        cafe::NaverIdLogin::login(this);
        break;

    case kTagLogout:
        cafe::NaverIdLogin::logout();
        break;

    case kTagIsLogin:
        showToast(StringUtils::format("%d", cafe::NaverIdLogin::isLogin()));
        break;

    case kTagGetProfile:
        cafe::NaverIdLogin::getProfile(this);
        break;

    case kTagShowRecord:
        cafe::CafeSdk::setUseVideoRecord(true);
        break;
            
    case kTagShowScreenShot:
        cafe::CafeSdk::setUseScreenShot(true);
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
    showToast("onCafeSdkStarted");
}

void HelloWorld::onCafeSdkStopped() {
    showToast("onCafeSdkStopped");
}

void HelloWorld::onCafeSdkClickAppSchemeBanner(const std::string& appScheme) {
    showToast(appScheme);
}

void HelloWorld::onCafeSdkJoined() {
    showToast("onCafeSdkJoined");
}

void HelloWorld::onCafeSdkPostedArticle(int menuId, int imageCount,
        int videoCount) {
    showToast(
            "onCafeSdkPostedArticle "
                    + StringUtils::format("%d, %d, %d", menuId, imageCount,
                            videoCount));
}

void HelloWorld::onCafeSdkPostedComment(int articleId) {
    showToast("onCafeSdkPostedComment " + StringUtils::format("%d", articleId));
}

void HelloWorld::onCafeSdkDidVote(int articleId) {
    showToast("onCafeSdkDidVote " + StringUtils::format("%d", articleId));
}

void HelloWorld::onCafeSdkWidgetScreenshotClick() {
    Size screenSize = Director::getInstance()->getWinSize();
    RenderTexture* texture = RenderTexture::create(screenSize.width,
            screenSize.height);
    texture->setPosition(Vec2(screenSize.width / 2, screenSize.height / 2));
    
    texture->begin();
    this->getParent()->visit();
//    this->getScene()->visit();
//    Director::getInstance()->getRunningScene()->visit();
    texture->end();

    std::string fileName = "captured_image.png";
    if (texture->saveToFile(fileName, Image::Format::PNG)) {
        std::string imageUri = FileUtils::getInstance()->getWritablePath()
                + fileName;
        cafe::CafeSdk::startImageWrite(imageUri);
    }
}

void HelloWorld::onCafeSdkOnRecordFinished(const std::string& fileUrl) {
    cafe::CafeSdk::startVideoWrite(fileUrl);
}

void HelloWorld::onNaverIdLoggedIn(bool success) {
    showToast("onNaverIdLoggedIn " + StringUtils::format("%d", success));
}

void HelloWorld::onNaverIdProfileResult(std::string jsonString) {
    showToast("onNaverIdLoggedIn " + jsonString);
}

void HelloWorld::onSDKRecordStart() {
}
void HelloWorld::onSDKRecordError(const std::string& errorMsg) {
}
void HelloWorld::onSDKRecordFinish(const std::string& uri) {
    cafe::CafeSdk::startVideoWrite(uri);
}
void HelloWorld::onSDKRecordFinishWithPreview() {
}
