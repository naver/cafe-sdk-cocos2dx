/*
 * CafeSdkHolder.h
 *
 *  Created on: 2016. 3. 22.
 *      Author: naver
 */

#ifndef JNI_CAFESDKHOLDER_PLUGINCAFE_H_
#define JNI_CAFESDKHOLDER_PLUGINCAFE_H_

#include <jni.h>
#include "PluginProtocol.h"

namespace cafe {

class CafeSdk;
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
		jmethodID showToast;
	};

private:
	friend CafeSdk;

	bool success_;
	Methods methods_;
	static CafeSdkHolder *sharedInstance_;
};

} /* namespace cafe */

#endif /* JNI_CAFESDKHOLDER_PLUGINCAFE_H_ */
