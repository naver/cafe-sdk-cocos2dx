#ifndef __NativeUtils_H__
#define __NativeUtils_H__

class NativeUtils {
public:
    static NativeUtils& sharedInstance();
    NativeUtils();
    
    void navercafe();
    void screenshot();
};

#endif
