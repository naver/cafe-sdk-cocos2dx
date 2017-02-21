# PLUG SDK

![http://static.naver.net/m/cafe/glink/promotion/cafe_sdk_open/img_intro1_20151111.png](http://static.naver.net/m/cafe/glink/promotion/cafe_sdk_open/img_intro1_20151111.png)

PLUG SDK는 모바일 게임에서 이탈하지 않고 커뮤니케이션이 가능한 IN-GAME COMMUNITY 라이브러리 입니다. 간단한 조작으로 프로젝트에 PLUG SDK를 추가 할 수 있습니다.

이미 많은 게임에 적용되어 검증되어 있는 PLUG SDK는 손쉽게 커뮤니케이션 기능을 게임 안에 넣을 수 있습니다.

# How To Get Started
- 제휴신청을 위해 [첨부된 파일](https://github.com/naver/cafe-sdk-android/raw/master/guide/alliance/%EB%84%A4%EC%9D%B4%EB%B2%84%EC%B9%B4%ED%8E%98SDK_%EC%A0%9C%ED%9C%B4%EC%96%91%EC%8B%9D_%EA%B2%8C%EC%9E%84%EC%82%AC%EB%AA%85_%EA%B2%8C%EC%9E%84%EB%AA%85_ver.2.0.0.xlsx)을 작성하여
[PLUG_제휴 dl_naverplugpartner@navercorp.com](dl_naverplugpartner@navercorp.com)로 메일을 보낸다.
- 최신 버전을 [다운로드](https://github.com/naver/cafe-sdk-ios/archive/master.zip)하면 샘플 프로젝트를 실행할 수 있다.
- 프로젝트에 적용하기 위한 [위키 가이드](https://www.gitbook.com/book/plug/plug-sdk-ios/details)가 작성 되어 있다.

# Communication
- [개발 문의 사항](http://cafe.naver.com/ArticleList.nhn?search.clubid=28285034&search.menuid=13&search.boardtype=L)에 있는 질문과 답변이 적용하는데 도움이 될 수 있다.
- 문의 사항이 있는 경우 [카페](http://cafe.naver.com/navercafesdk)를 사용한다.

# Usages
- [iOS GitHub](https://github.com/naver/cafe-sdk-ios)
- [Android GitHub](https://github.com/naver/cafe-sdk-android)

## 1. 프로젝트 설정
sample/Classes/plugincafe 폴더를 게임 프로젝트로 복사한다.

### 1-1. Android
- lib/android에 있는 PLUG SDK 프로젝트를 게임 프로젝트에 Library로 추가한다.

### 1-2. iOS
- lib/iOS에 있는 PLUG SDK 프로젝트를 게임 프로젝트에 추가한다.

## 2. Initialize
### 2-1. 한국 채널(네이버 카페) - 글로벌 채널만 사용하는 경우 세팅하지 않는다.

[네이버 아이디로 로그인 애플리케이션 등록](https://developers.naver.com/apps/#/register?api=nvlogin)에서 받은 ClientId, ClientSecret 값을 세팅한다.

[네이버 카페를 개설](http://section.cafe.naver.com/)하고 얻은 카페 ID를 세팅한다.

[네이버 아이디로 로그인 어플리케이션](https://developers.naver.com/apps/#/myapps) 설정에 등록한 iOS URL Scheme을 세팅한다.

```cpp
cafe::CafeSdk::init("U5ZHoj_OStOHOJ8mec_s", "piPHPA9i4E", 28334359);
```



### 2-2. 글로벌 채널 - 한국 채널만 사용하는 경우 세팅하지 않는다.

개설된 커뮤니티에 매니저 권한으로 접속한 후, [setting > Communities > In-App Community Setting](http://g.cafe.naver.com/plugsample/manage/consumer)으로 진입하여 '커뮤니티 ID 및 Consumer Key, Consumer Secret'를 발급받는다.

![](https://plug.gitbooks.io/plug-sdk-android/content/assets/wiki-plug-setting.png)


ConsumerKey, communityId 값을 세팅한다.

```cpp
cafe::CafeSdk::initGlobal("IHCd_HmSiMcXOMC37xZ8", 1013329);
```

## 3. UCafeSdkBlueprintLibrary

### StartHome
PLUG를 실행한다.

```cpp
cafe::CafeSdk::startHome();
```

폴더 구조
-------------

file | 설명
---	| ---
guide/ | 가이드 문서 및 CafeSDK 설명
lib/ | CafeSDK Android, iOS 라이브러리 파일
sample/Classes/plugincafe/platform/ios | iOS Plugin
sample/Classes/plugincafe/platform/android | Android Plugin
sample/proj.ios_mac		| iOS 샘플
sample/proj.android		| Android 샘플
LICENSE | 라이선스 파일
README.md | readme 파일


의존 라이브러리 iOS
-------------

1. [네이버 아이디 로그인-4.0.7](https://nid.naver.com/devcenter/docs.nhn?menu=IOS)
2. [AFNetworking](https://github.com/AFNetworking/AFNetworking)
<br>2.x, 3.x 모두 사용 가능하며 3.1.0에서 테스트 진행했습니다.
3. [SDWebImage-3.8.2](https://github.com/rs/SDWebImage)
4. [FLAnimatedImage-1.0.12](https://github.com/Flipboard/FLAnimatedImage)
5. ApiGateway-1.5.0

의존 라이브러리 Android
-------------

1. [네이버 아이디 로그인](https://nid.naver.com/devcenter/docs.nhn?menu=Android)
2. android support library v4
3. [naver volleyer](http://mvnrepository.com/artifact/com.navercorp.volleyextensions/volleyer)   (2.0.1 사용 중)
4. [volley](http://mvnrepository.com/artifact/com.mcxiaoke.volley/library/) (1.0.2사용 중)
5. [google gson](http://mvnrepository.com/artifact/com.google.code.gson/gson)  (2.3.1 사용 중)
6. [glide](http://mvnrepository.com/artifact/com.github.bumptech.glide/glide)  (3.6.1 사용 중)
7. [otto](http://mvnrepository.com/artifact/com.squareup/otto)  (1.3.8 사용 중)

라이선스
-------------
NAVER Cafe SDK for cocos2dx

Copyright 2016 NAVER Corp.
All rights reserved.

Unauthorized use, modification and redistribution of this software are strongly prohibited.
