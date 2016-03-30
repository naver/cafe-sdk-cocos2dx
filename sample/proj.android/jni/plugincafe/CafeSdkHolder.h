/*
 * CafeSdkHolder.h
 *
 *  Created on: 2016. 3. 22.
 *      Author: naver
 */

#ifndef JNI_CAFESDKHOLDER_PLUGINCAFE_H_
#define JNI_CAFESDKHOLDER_PLUGINCAFE_H_

#include "PluginProtocol.h"
#include "PluginJniHelper.h"

namespace cafe {

class CafeSdkHolder: public cocos2d::plugin::PluginProtocol {
public:
    CafeSdkHolder();
    jobject getJavaObject();
    void callJavaMethod(std::string name);

    bool getMethodInfo(cocos2d::PluginJniMethodInfo& methodinfo,
            std::string name, std::string signature);

    static CafeSdkHolder* getInstance();

private:
    bool success_;
    static CafeSdkHolder *sharedInstance_;
};

} /* namespace cafe */

#endif /* JNI_CAFESDKHOLDER_PLUGINCAFE_H_ */
