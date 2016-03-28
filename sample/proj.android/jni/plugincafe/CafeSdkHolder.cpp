/*
 * CafeSdkHolder.cpp
 *
 *  Created on: 2016. 3. 22.
 *      Author: naver
 */

#include "CafeSdkHolder.h"
#include "PluginJniHelper.h"
#include "PluginUtils.h"
#include "PluginCafe.h"

#define LOG(format, ...)	PluginUtils::outputLog("CafeSdk", format, ##__VA_ARGS__)

using namespace cocos2d;
using namespace cocos2d::plugin;

namespace cafe {

const char* kCafeSdkClass = "org/cocos2dx/plugin/CafeSdk";

CafeSdkHolder* CafeSdkHolder::sharedInstance_ = nullptr;
CafeSdkHolder* CafeSdkHolder::getInstance() {
	if (sharedInstance_ == nullptr) {
		sharedInstance_ = new (std::nothrow) CafeSdkHolder();
	}

	return sharedInstance_;
}

CafeSdkHolder::CafeSdkHolder() {
	PluginJniMethodInfo t;
	if (!PluginJniHelper::getStaticMethodInfo(t,
			"org/cocos2dx/plugin/PluginWrapper",
			"initPlugin",
			"(Ljava/lang/String;)Ljava/lang/Object;")) {
		return;
	}

	jstring name = t.env->NewStringUTF(kCafeSdkClass);
	jobject obj = t.env->CallStaticObjectMethod(t.classID, t.methodID, name);

	t.env->DeleteLocalRef(name);
	t.env->DeleteLocalRef(t.classID);

	success_ = obj != nullptr;
	if (success_) {
		PluginUtils::initJavaPlugin(this, obj, kCafeSdkClass);

		methods_.init = getMethodID("init", "(Ljava/lang/String;Ljava/lang/String;I)V");
		methods_.startImageWrite = getMethodID("startImageWrite", "(ILjava/lang/String;Ljava/lang/String;Ljava/lang/String;)V");
		methods_.showToast = getMethodID("showToast", "(Ljava/lang/String;)V");
	}
}

void CafeSdkHolder::callJavaMethod(std::string name) {
	if (success_) {
		PluginUtils::callJavaFunctionWithName(this, name.c_str());
	}
}

jobject CafeSdkHolder::getJavaObject() {
	return success_ ? PluginUtils::getPluginJavaData(this)->jobj : nullptr;
}

jmethodID CafeSdkHolder::getMethodID(std::string name, std::string signature) {
	PluginJniMethodInfo t;
	if (!PluginJniHelper::getMethodInfo(t, kCafeSdkClass, name.c_str(), signature.c_str())) {
		return 0;
	}

	t.env->DeleteLocalRef(t.classID);
	return t.methodID;
}

extern "C" {
	JNIEXPORT void JNICALL Java_org_cocos2dx_plugin_CafeSdk_nativeOnSdkStarted(JNIEnv*  env, jobject thiz) {
		auto cafeListener = CafeSdk::getCafeListener();
		if (cafeListener == nullptr) return;
		cafeListener->onCafeSdkStarted();
	}
}

} /* namespace cafe */
