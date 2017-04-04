# PLUG SDK

PLUG SDK는 모바일 게임 사용자가 게임 도중 게임을 벗어나지 않고 게임의 커뮤니티와 소통할 수 있도록 제공되는 인앱 커뮤니티 라이브러리입니다. 간단한 조작으로 프로젝트에 PLUG SDK를 추가할 수 있습니다.

이미 많은 게임에 적용돼 검증된 PLUG SDK를 사용하면 손쉽게 커뮤니케이션 기능을 게임 안에 넣을 수 있습니다.
 
![PLUG SDK](http://static.naver.net/m/cafe/glink/promotion/cafe_sdk_open/img_intro1_20151111.png)

## How To Get Started 

### 제휴 신청

PLUG SDK를 앱에 적용하려면 PLUG SDK 제휴를 신청해야 합니다. 제휴 양식을 작성해 PLUG 제휴 담당자에게 메일로 제휴를 신청합니다.

- [제휴 양식 다운로드](https://github.com/naver/cafe-sdk-android/raw/master/guide/alliance/%EB%84%A4%EC%9D%B4%EB%B2%84%EC%B9%B4%ED%8E%98SDK_%EC%A0%9C%ED%9C%B4%EC%96%91%EC%8B%9D_%EA%B2%8C%EC%9E%84%EC%82%AC%EB%AA%85_%EA%B2%8C%EC%9E%84%EB%AA%85_ver.2.0.0.xlsx)
- PLUG 제휴 담당자 메일 주소: <a href="mailto:dl_naverplugpartner@navercorp.com">dl_naverplugpartner@navercorp.com</a>

제휴 신청이 완료되면 PC의 카페 관리 페이지에서 네이버 PLUG SDK 콘텐츠를 관리할 수 있습니다.

### 적용 가이드

- [PLUG 적용 가이드](https://www.gitbook.com/book/plug/plug-sdk-ios/details)
- [최신 버전 및 샘플 프로젝트 다운로드](https://github.com/naver/cafe-sdk-ios/archive/master.zip )

## Communication 

개발과 관련된 문의 사항은 PLUG 공식 카페를 사용합니다.

- [PLUG 공식 카페](http://cafe.naver.com/navercafesdk)
- [PLUG 공식 카페의 개발 문의 게시판](http://cafe.naver.com/ArticleList.nhn?search.clubid=28285034&search.menuid=13&search.boardtype=L)

## Usages 

### 1. 프로젝트 설정

1. 다운로드한 샘플 프로젝트에 포함된 **sample/Classes/plugincafe** 폴더를 게임 프로젝트로 복사합니다.  
2. 운영체제에 맞는 PLUG SDK 프로젝트 게임 프로젝트에 추가합니다.  
   - Android: **lib/android** 폴더에 있는 PLUG SDK 프로젝트를 게임 프로젝트에 라이브러리로 추가합니다.  
   - iOS: **lib/iOS** 폴더에 있는 PLUG SDK 프로젝트를 게임 프로젝트에 추가합니다.

> 운영체제별 PLUG SDK에 관한 자세한 내용은 GitHub 저장소를 참고합니다.  
> - [Android용 PLUG SDK의 GitHub 저장소](https://github.com/naver/cafe-sdk-android)  
> - [iOS용 PLUG SDK의 GitHub 저장소](https://github.com/naver/cafe-sdk-ios)

### 2. 초기화

PLUG SDK가 지원하는 언어에 따라 다음과 같이 PLUG SDK를 초기화합니다.

#### 2.1 PLUG SDK 초기화(한국어만 지원 - 네이버 카페)

한국어만 지원하는 PLUG SDK를 초기화할 때는 다음과 같은 초기화 정보를 설정합니다.

- [네이버 아이디로 로그인 개발자 센터](https://developers.naver.com/apps/#/register?api=nvlogin)에서 애플리케이션을 등록하고 받은 클라이언트 아이디(ClientId)와 클라이언트 시크릿(ClientSecret)
- [네이버 카페](http://section.cafe.naver.com/)에서 카페를 개설하고 받은 카페 ID

```cpp
cafe::CafeSdk::init("U5ZHoj_OStOHOJ8mec_s", "piPHPA9i4E", 28334359 );
```

#### 2.2 PLUG SDK 초기화(외국어만 지원)

외국어만 지원하는 PLUG SDK를 초기화할 때는 다음과 같은 초기화 정보를 설정합니다.

- 커뮤니티를 개설하고 받은 컨슈머 키(Consumer Key)
- 커뮤니티를 개설하고 받은 커뮤니티 ID(Community ID)

```cpp
cafe::CafeSdk::initGlobal("IHCd_HmSiMcXOMC37xZ8", 1013329);
```

> **커뮤니티 ID와 컨슈머 키 확인**  
> 커뮤니티를 개설하고 받은 커뮤니티 ID와 컨슈머 키를 확인하려면 [커뮤니티 관리 페이지](http://g.cafe.naver.com/plugsample/manage/consumer)에 매니저 권한으로 접근하십시오.  
> 커뮤니티 관리 페이지에서 **Settings > Communities > In-App Community Settings** 메뉴를 선택하면 커뮤니티 ID와 컨슈머 키를 확인할 수 있습니다.     
> ![In-App Community Settings](https://plug.gitbooks.io/plug-sdk-android/content/assets/wiki-plug-setting.png)

### 3. PLUG SDK 시작

초기화가 완료되면 PLUG SDK를 실행합니다.

#### 3.1 startHome() 메서드

startHome() 메서드는 PLUG SDK를 시작하는 메서드입니다.

```cpp
cafe::CafeSdk::startHome();
```

## Files and Folders

|폴더 및 파일 이름	|설명|
|---|---|
|guide/	|PLUG SDK 적용 가이드가 있는 폴더|
|lib/	|Android 및 iOS용 PLUG SDK 라이브러리 파일이 있는 폴더|
|sample/Classes/plugincafe/platform/ios	|iOS용 플러그인이 있는 폴더|
|sample/Classes/plugincafe/platform/android	|Android용 플러그인이 있는 폴더|
|sample/proj.ios_mac	|iOS용 샘플 프로젝트가 있는 폴더|
|sample/proj.android	|Android용 샘플 프로젝트가 있는 폴더|
|LICENSE	|라이선스 파일|
|README.md	|리드미 파일|

## Dependent Libraries

PLUG SDK를 사용하려면 다음 라이브러리를 프로젝트에 추가해 함께 빌드해야 합니다. 라이브러리는 샘플 프로젝트에 포함돼 있습니다. 

### Android용 라이브러리

- Android Support Library v4
- [네이버 아이디 로그인](https://nid.naver.com/devcenter/docs.nhn?menu=Android)
- [NAVER Volleyer](http://mvnrepository.com/artifact/com.navercorp.volleyextensions/volleyer)(2.0.1 버전 사용 중)
- [Volley](http://mvnrepository.com/artifact/com.mcxiaoke.volley/library/)(1.0.2 버전 사용 중)
- [Google Gson](http://mvnrepository.com/artifact/com.google.code.gson/gson)(2.3.1 버전 사용 중)
- [Glide](http://mvnrepository.com/artifact/com.github.bumptech.glide/glide)(3.6.1 버전 사용 중)
- [Otto](http://mvnrepository.com/artifact/com.squareup/otto)(1.3.8 버전 사용 중 )  
- hmac(2.3.1 버전 사용중)

### iOS용 라이브러리 

- [네이버 아이디 로그인](https://nid.naver.com/devcenter/docs.nhn?menu=IOS)(4.0.7 버전)
- [AFNetworking](https://github.com/AFNetworking/AFNetworking)(3.1.0 버전 )

>  AFNetworking 2.x 버전과 3.x 버전 모두 사용할 수 있습니다. PLUG SDK 테스트는 AFNetworking 3.1.0 버전으로 진행했습니다.

- [SDWebImage](https://github.com/rs/SDWebImage)(3.8.2 버전)
- [FLAnimatedImage](https://github.com/Flipboard/FLAnimatedImage)(1.0.12 버전)
- ApiGateway-1.5.0 

## License 

PLUG SDK의 저작권은 네이버(주)에 있습니다.

```
NAVER Cafe SDK for Cocos2d-x

Copyright 2016 NAVER Corp.
All rights reserved.

Unauthorized use, modification and redistribution of this software are strongly prohibited.
```
