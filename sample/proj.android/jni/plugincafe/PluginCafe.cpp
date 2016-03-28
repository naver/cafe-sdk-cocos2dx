/*
 * PluginCafe.cpp
 *
 *  Created on: 2016. 3. 22.
 *      Author: naver
 */

#include "PluginCafe.h"
#include "PluginUtils.h"
#include "PluginJniHelper.h"
#include "CafeSdkHolder.h"

#define LOG(format, ...)	PluginUtils::outputLog("CafeSdk", format, ##__VA_ARGS__)

using namespace cocos2d;
using namespace cocos2d::plugin;

namespace cafe {

static CafeListener* gCafeListener = nullptr;

CafeListener::~CafeListener() {
	// do nothing.
}

static CafeSdkHolder* holder() {
	return CafeSdkHolder::getInstance();
}

void CafeSdk::setCafeListener(CafeListener *listener) {
	gCafeListener = listener;
}

CafeListener* CafeSdk::getCafeListener() {
	return gCafeListener;
}

void CafeSdk::startHome() {
	holder()->callJavaMethod("startHome");
}

void CafeSdk::startNotice() {
	holder()->callJavaMethod("startNotice");
}

void CafeSdk::startEvent() {
	holder()->callJavaMethod("startEvent");
}

void CafeSdk::startMenu() {
	holder()->callJavaMethod("startMenu");
}

void CafeSdk::startProfile() {
	holder()->callJavaMethod("startProfile");
}

void CafeSdk::init(std::string clientId, std::string clientSecret, int cafeId) {
	PluginJniMethodInfo t;
	if (holder()->getMethodInfo(t, "init",
			"(Ljava/lang/String;Ljava/lang/String;I)V")) {
		jstring _clientId = t.env->NewStringUTF(clientId.c_str());
		jstring _clientSecret = t.env->NewStringUTF(clientSecret.c_str());

		t.env->CallVoidMethod(holder()->getJavaObject(), t.methodID, _clientId,
				_clientSecret, cafeId);

		t.env->DeleteLocalRef(_clientId);
		t.env->DeleteLocalRef(_clientSecret);
		t.env->DeleteLocalRef(t.classID);
	}
}

void CafeSdk::startImageWrite(int menuId, std::string subject, std::string text,
		std::string imageUri) {
	PluginJniMethodInfo t;
	if (holder()->getMethodInfo(t, "startImageWrite",
			"(ILjava/lang/String;Ljava/lang/String;Ljava/lang/String;)V")) {
		jstring _subject = t.env->NewStringUTF(subject.c_str());
		jstring _text = t.env->NewStringUTF(text.c_str());
		jstring _imageUri = t.env->NewStringUTF(imageUri.c_str());

		t.env->CallVoidMethod(holder()->getJavaObject(), t.methodID, menuId,
				_subject, _text, _imageUri);

		t.env->DeleteLocalRef(_subject);
		t.env->DeleteLocalRef(_text);
		t.env->DeleteLocalRef(_imageUri);
		t.env->DeleteLocalRef(t.classID);
	}
}

void CafeSdk::showToast(std::string text) {
	PluginJniMethodInfo t;
	if (holder()->getMethodInfo(t, "showToast", "(Ljava/lang/String;)V")) {
		jstring _text = t.env->NewStringUTF(text.c_str());

		t.env->CallVoidMethod(holder()->getJavaObject(), t.methodID, _text);

		t.env->DeleteLocalRef(_text);
		t.env->DeleteLocalRef(t.classID);
	}
}

} /* namespace cafe */
