/*
 * PluginCafe.h
 *
 *  Created on: 2016. 3. 22.
 *      Author: naver
 */

#ifndef JNI_PLUGINCAFE_PLUGINCAFE_H_
#define JNI_PLUGINCAFE_PLUGINCAFE_H_

#include "PluginProtocol.h"

namespace cafe {

class CafeListener {
public:
	virtual void onCafeSdkStarted() = 0;
	virtual ~CafeListener();
};

class CafeSdk {
public:
	static void init(std::string clientId, std::string clientSecret, int cafeId);

	static void setCafeListener(CafeListener *listener);
	static CafeListener* getCafeListener();

	static void startHome();
	static void startNotice();
	static void startEvent();
	static void startMenu();
	static void startProfile();

	static void startImageWrite(int menuId, std::string subject, std::string text, std::string imageUri);

	static void showToast(std::string text);
};

} /* namespace cafe */

#endif /* JNI_PLUGINCAFE_PLUGINCAFE_H_ */
