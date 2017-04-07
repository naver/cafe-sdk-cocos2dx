# PLUG SDK

The PLUG SDK is a dedicated in-app community library for mobile games, which lets mobile gamers use community features without leaving games while they are playing. It is easy to apply the PLUG SDK to your project.

As a proven SDK, which has been used in many mobile games, this lets you simply and quickly add community features in your game.
 
![PLUG SDK](http://static.naver.net/m/cafe/glink/promotion/cafe_sdk_open/img_intro1_20151111.png)

## How To Get Started 

### Become a Partner

You should apply to our partner program to apply the PLUG SDK to your app. Please fill out the form after downloads and send it via email.

- [Downloads of partnership registration form](https://github.com/naver/cafe-sdk-android/raw/master/guide/alliance/%EB%84%A4%EC%9D%B4%EB%B2%84%EC%B9%B4%ED%8E%98SDK_%EC%A0%9C%ED%9C%B4%EC%96%91%EC%8B%9D_%EA%B2%8C%EC%9E%84%EC%82%AC%EB%AA%85_%EA%B2%8C%EC%9E%84%EB%AA%85_ver.2.0.0.xlsx)
- Email address of a partnership contact: <a href="mailto:dl_naverplugpartner@navercorp.com">dl_naverplugpartner@navercorp.com</a>

You can manage the PLUG SDK content on the Settings page from your computer after the partnership process is completed.

### Documentation

- [PLUG documents](https://www.gitbook.com/book/plug/plug-sdk-ios/details/en)
- [Downloads of latest library and sample project files](https://github.com/naver/cafe-sdk-ios/archive/master.zip )

## Communication 

If you have any questions regarding working this SDK, please [visit our issue page for cocos2dx](https://github.com/naver/cafe-sdk-cocos2dx/issues).

## Usages 

### 1. Configure a Project

1. Go to the **sample/Classes** folder and copy and paste the **plugincafe** folder to your project. The folder is included in the sample project you downloaded. 
2. Add the PLUG SDK project to your game project depending on your operating system.  
   - Android: Go to the **lib/android** folder and add the PLUG SDK project to your game project as a library.  
   - iOS: Go to the **lib/iOS** folder and add the PLUG SDK project to your game project.

> For more information about the PLUG SDK for each operating system, visit the GitHub repository.  
> - [GitHub repository for Android PLUG SDK](https://github.com/naver/cafe-sdk-android)  
> - [GitHub repository for iOS PLUG SDK](https://github.com/naver/cafe-sdk-ios)

### 2. Initialize the PLUG SDK

Initializing the PLUG SDK will vary depending on the supported language.

#### 2.1 Support for Korean only (NAVER Cafe)

Configure the initialization information below to initialize the PLUG SDK that supports Korean only.

- Client ID (ClientId) and client secret (ClientSecret) you received after registering your application in [NAVER Login Developers](https://developers.naver.com/apps/#/register?api=nvlogin)
- Cafe ID you received after creating your Cafe in [NAVER Cafe](http://section.cafe.naver.com/)

```cpp
cafe::CafeSdk::init("U5ZHoj_OStOHOJ8mec_s", "piPHPA9i4E", 28334359 );
```

#### 2.2 Support for languages other than Korean

Configure the initialization information below to initialize the PLUG SDK that supports languages other than Korean.

- Consumer key you received after creating your community
- Community ID you received after creating your community

```cpp
cafe::CafeSdk::initGlobal("IHCd_HmSiMcXOMC37xZ8", 1013329);
```

> **How to check your community ID and consumer key**  
> Visit http://g.cafe.naver.com/plugsample/manage/consumer and log in to your community using the account with manager privileges.
> You can find the information in **Settings > Communities > In-App Community Settings** as shown in the image below.     
> ![In-App Community Settings](https://plug.gitbooks.io/plug-sdk-android/content/assets/wiki-plug-setting.png)

### 3. Start the PLUG SDK

Start the PLUG SDK after initialization is completed.

#### 3.1 startHome() method

The startHome() method starts the PLUG SDK.

```cpp
cafe::CafeSdk::startHome();
```

## Files and Folders 

|Name	|Description|
|---|---|
|guide/	|Folder for PLUG SDK documentation|
|lib/	|Folder for Android and iOS PLUG SDK libraries|
|sample/Classes/plugincafe/platform/ios	|Folder for iOS plugins|
|sample/Classes/plugincafe/platform/android	|Folder for Android plugins|
|sample/proj.ios_mac	|Folder for iOS sample project |
|sample/proj.android	|Folder for Android sample project|
|LICENSE	|License file|
|README.md	|Readme file|

## Dependent Libraries 

You should add the following libraries to your project and build together with the PLUG SDK in order to use the PLUG SDK. The libraries are included in the sample project. 

### For Android

- Android Support Library v4
- [NAVER Login](https://nid.naver.com/devcenter/docs.nhn?menu=Android)
- [NAVER Volleyer](http://mvnrepository.com/artifact/com.navercorp.volleyextensions/volleyer) (version 2.0.1)
- [Volley](http://mvnrepository.com/artifact/com.mcxiaoke.volley/library/) (version 1.0.2)
- [Google Gson](http://mvnrepository.com/artifact/com.google.code.gson/gson) (version 2.3.1)
- [Glide](http://mvnrepository.com/artifact/com.github.bumptech.glide/glide) (version 3.6.1)
- [Otto](http://mvnrepository.com/artifact/com.squareup/otto) (version 1.3.8)
- hmac (version 2.3.1)

### For iOS 

- [NAVER Login](https://nid.naver.com/devcenter/docs.nhn?menu=IOS) (version 4.0.7)
- [AFNetworking](https://github.com/AFNetworking/AFNetworking) (version 3.1.0)

>  Both 2.x and 3.x versions are available. The PLUG SDK is tested on AFNetworking 3.1.0.

- [SDWebImage](https://github.com/rs/SDWebImage) (version 3.8.2)
- [FLAnimatedImage](https://github.com/Flipboard/FLAnimatedImage) (version 1.0.12)
- ApiGateway-1.5.0

## License 

The intellectual property right of the PLUG SDK is owned by NAVER Corporation.

```
NAVER Cafe SDK for Cocos2d-x

Copyright 2016 NAVER Corp.
All rights reserved.

Unauthorized use, modification and redistribution of this software are strongly prohibited.
```
