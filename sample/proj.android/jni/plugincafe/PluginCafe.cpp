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

void CafeSdk::startEvent()  {
	holder()->callJavaMethod("startEvent");
}

void CafeSdk::startMenu()  {
	holder()->callJavaMethod("startMenu");
}

void CafeSdk::startProfile() {
	holder()->callJavaMethod("startProfile");
}

void CafeSdk::init(std::string clientId, std::string clientSecret, int cafeId) {
	JNIEnv *env = PluginJniHelper::getEnv();
	jstring _clientId = env->NewStringUTF(clientId.c_str());
	jstring _clientSecret = env->NewStringUTF(clientSecret.c_str());

	env->CallVoidMethod(holder()->getJavaObject(), holder()->methods_.init, _clientId, _clientSecret, cafeId);

	env->DeleteLocalRef(_clientId);
	env->DeleteLocalRef(_clientSecret);
}

void CafeSdk::startImageWrite(int menuId, std::string subject, std::string text, std::string imageUri) {
	JNIEnv *env = PluginJniHelper::getEnv();
	jstring _subject = env->NewStringUTF(subject.c_str());
	jstring _text = env->NewStringUTF(text.c_str());
	jstring _imageUri = env->NewStringUTF(imageUri.c_str());

	env->CallVoidMethod(holder()->getJavaObject(), holder()->methods_.startImageWrite, menuId, _subject, _text, _imageUri);

	env->DeleteLocalRef(_subject);
	env->DeleteLocalRef(_text);
	env->DeleteLocalRef(_imageUri);
}

void CafeSdk::showToast(std::string text) {
	JNIEnv *env = PluginJniHelper::getEnv();
	jstring _text = env->NewStringUTF(text.c_str());

	env->CallVoidMethod(holder()->getJavaObject(), holder()->methods_.showToast, _text);

	env->DeleteLocalRef(_text);
}

} /* namespace cafe */
