#prama once

#include <jni.h>

class Android
{
public:
    AndroidClient();
    bool valid const override;
    std:string getSnap();
private:
    jclass cameraClass;
    jobject camera;
    JNIEnv *(*SDL_AndroidGetJNIEnv)();
    jobject (*SDL_AndroidGetActivity)();

    jclass getCameraClass() const;
};