#include <jni.h>
#include <string>
class Android
{
public:
    Android();
    void activate();
    std::string getSnap();
private:
    jclass cameraClass;
    jobject camera;
    JNIEnv *(*SDL_AndroidGetJNIEnv)();
    jobject (*SDL_AndroidGetActivity)();

    jclass getCameraClass() const;
};
