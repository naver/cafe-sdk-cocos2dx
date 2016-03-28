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

static CafeSdkHolder* holder() {
	return CafeSdkHolder::getInstance();
}

void CafeSdk::init(std::string clientId, std::string clientSecret, int cafeId) {
	JNIEnv *env = PluginJniHelper::getEnv();
	jstring jClientId = env->NewStringUTF(clientId.c_str());
	jstring jClientSecret = env->NewStringUTF(clientSecret.c_str());

	env->CallVoidMethod(holder()->getJavaObject(), holder()->methods_.init, jClientId, jClientSecret, cafeId);

	env->DeleteLocalRef(jClientId);
	env->DeleteLocalRef(jClientSecret);
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

void CafeSdk::startImageWrite(int menuId, std::string subject, std::string text, std::string imageUri) {
	JNIEnv *env = PluginJniHelper::getEnv();
	jstring jSubject = env->NewStringUTF(subject.c_str());
	jstring jText = env->NewStringUTF(text.c_str());
	jstring jImageUri = env->NewStringUTF(imageUri.c_str());

	env->CallVoidMethod(holder()->getJavaObject(), holder()->methods_.startImageWrite, menuId, jSubject, jText, jImageUri);

	env->DeleteLocalRef(jSubject);
	env->DeleteLocalRef(jText);
	env->DeleteLocalRef(jImageUri);
}

void CafeSdk::showToast(std::string text) {
	JNIEnv *env = PluginJniHelper::getEnv();
	jstring jText = env->NewStringUTF(text.c_str());

	env->CallVoidMethod(holder()->getJavaObject(), holder()->methods_.showToast, jText);

	env->DeleteLocalRef(jText);
}

} /* namespace cafe */
