# cocos2d-x Cafe SDK 

> 본 저장소는 Cafe SDK를 사용하기위한 library 및 관련 파일들을 포함하고 있습니다.

Cafe SDK에 대하여 자세히 알고싶으시면 [네이버 CafeSDK 공식카페](http://cafe.naver.com/navercafesdk)를 참조해 주세요.

![Overviw](/guide/images/widget_screenshot.gif)

v.2.0.1
####fixed iOS####
- 채널 정보 조회하는 api 추가. 
  (NSString *)currentCountry; 
- 한국어로 실행했을때 채널 변경 버튼이 노출되지 않는 이슈 수정 

####fixed Android####
- 채널 정보 설정하는 api 추가. 
  Glink#setCafeLangCode(String cafeLangCode);
- 채널 정보 조회하는 api 추가.
  Glink#getCafeLangCode();
- 국내 카페만 설정할 경우 크래쉬 발생하는 이슈 가드 처리.


v.2.0.0
-------------
####updated
1. 영어, 중국어, 일본어, 태국어 채널 지원.

####fixed####
1. iOS 10 관련 이슈 수정.

####issue####
1. 세로모드 2.0.1에서 지원 예정.
2. 언어 설정 중국어인 경우 위젯 동영상 녹화 기능 안되는 이슈.

폴더 구조
-------------

file      | 설명 		
---			| ---		
guide/			| 가이드 문서 및 CafeSDK 설명
lib/		 	| CafeSDK Android, iOS 라이브러리 파일
sample/Classes/plugincafe/platform/ios | iOS Plugin
sample/Classes/plugincafe/platform/android | Android Plugin
sample/proj.ios_mac		| iOS 샘플
sample/proj.android		| Android 샘플
LICENSE     | 라이선스 파일
README.md   | readme 파일


의존 라이브러리 iOS
-------------

1. [네이버 아이디 로그인-4.0.7](https://nid.naver.com/devcenter/docs.nhn?menu=IOS)
2. [AFNetworking](https://github.com/AFNetworking/AFNetworking)
<br>2.x 모두 사용 가능하며 2.6.3에서 테스트 진행했습니다.
3. [SDWebImage-3.8.2](https://github.com/rs/SDWebImage)
4. [FLAnimatedImage-1.0.12](https://github.com/Flipboard/FLAnimatedImage)


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
