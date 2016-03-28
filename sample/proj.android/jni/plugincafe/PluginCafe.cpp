/*
 * PluginCafe.cpp
 *
 *  Created on: 2016. 3. 22.
 *      Author: naver
 */

#include "PluginCafe.h"
#include "PluginUtils.h"
#include "PluginJniHelper.h"

#define LOG(format, ...)	PluginUtils::outputLog("CafeSdk", format, ##__VA_ARGS__)

using namespace cocos2d;
using namespace cocos2d::plugin;

namespace cafe {

const char* kCafeSdkClass = "org/cocos2dx/plugin/CafeSdk";
static CafeListener* gCafeListener = nullptr;

class CafeSdkHolder: public cocos2d::plugin::PluginProtocol {
public:
	CafeSdkHolder();
	void callJavaMethod(std::string name);
	jobject getJavaObject();

	static CafeSdkHolder* getInstance();
	static jmethodID getMethodID(std::string name, std::string signature);

	struct Methods {
		jmethodID init;
		jmethodID startImageWrite;
	};

private:
	friend CafeSdk;

	bool success_;
	Methods methods_;
	static CafeSdkHolder *sharedInstance_;
};

CafeSdkHolder* holder() {
	return CafeSdkHolder::getInstance();
}

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

void CafeSdk::startHome() {
	holder()->callJavaMethod("startHome");
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

extern "C" {
	JNIEXPORT void JNICALL Java_org_cocos2dx_plugin_CafeSdk_nativeOnSdkStarted(JNIEnv*  env, jobject thiz) {
		if (gCafeListener == nullptr) return;
		gCafeListener->onSdkStarted();
	}
}

} /* namespace cafe */
