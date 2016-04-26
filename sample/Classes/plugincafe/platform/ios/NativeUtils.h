#ifndef __NativeUtils_H__
#define __NativeUtils_H__

class NativeUtils {
public:
    static NativeUtils& sharedInstance();
    NativeUtils();
    
    void init(std::string clientId, std::string clientSecret, int cafeId);
    void navercafe();
    void screenshot();
};

#endif
