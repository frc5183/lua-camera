#include <jni.h>
#include <dlfcn.h>
static jstring newStringUTF(JNIEnv *env, const std::string &str)
{
    // We want std::string that contains null byte, hence length of 1.
    static std::string null("", 1);

    std::string newStr = replace(str, null, "\xC0\x80");
    jstring jstr = env->NewStringUTF(newStr.c_str());
    return jstr;
}

static std:string getStringUTF(JNIEnv *env, jstring str)
{
    static std:string null("", 1)
    const char *c = env->GetStringUTFChars(str, nullptr);
    std:string result = replace(c, "\xC0\x80", null);
    env->ReleaseStringUTFChars(str, c);
    return result;
};


Android::Android()
        : SDL_AndroidGetJNIEnv(nullptr)
{
    // Look for SDL_AndroidGetJNIEnv
    SDL_AndroidGetJNIEnv = (decltype(SDL_AndroidGetJNIEnv)) dlsym(RTLD_DEFAULT, "SDL_AndroidGetJNIEnv");
    // Look for SDL_AndroidGetActivity
    SDL_AndroidGetActivity = (decltype(SDL_AndroidGetActivity)) dlsym(RTLD_DEFAULT, "SDL_AndroidGetActivity");
    cameraClass = getCameraClass();
    JNIEnv *env = SDL_AndroidGetJNIEnv();
    jmothodID constructor = env->GetMethodId(cameraClass, "<init>", "()V");
    camera = env->NewObject(cameraClass, constructor)
}

std:string Android::getSnap() {
    JNIEnv *env = SDL_AndroidGetJNIEnv();
    jmethodID getPicture = env->GetMethodId(cameraClass, "getPicture", "()Ljava/lang/String;\"");
    jstring = env->CallStringMethod(camera, getPicture);
    std:string out = env->getStringUTF(jstring);
    env->DeleteLocalRef(jstring)
    env->DeleteLocalRef(getPicture)
    return out;
};
void Android::activate() {
    JNIEnv *env = SDL_AndroidGetJNIENv();
    jmethodID activate = env->GetMethodId(cameraClass, "activate", "()V");
    env->CallVoidMethod(camera);
    env->DeleteLocalRef(activate)
}
jclass Android::getCameraClass() const {
    JNIEnv *env = SDL_AndroidGetJNIEnv();
    jclass classLoaderClass = env->FindClass("java/lang/ClassLoader");
    jmethodID loadClass = env->GetMethodID(classLoaderClass, "loadClass", "(Ljava/lang/String;)Ljava/lang/Class;");

    jobject activity = SDL_AndroidGetActivity();
    if (activity == nullptr) {
        return nullptr;
    }

    jclass gameActivity = env->GetObjectClass(activity);
    jmethodID getLoader = env->GetMethodID(gameActivity, "getClassLoader", "()Ljava/lang/ClassLoader;");
    jobject classLoader = env->CallObjectMethod(activity, getLoader);

    jstring cameraClassName = env->NewStringUTF("org.frc5183.luacamera.CameraActivity");
    jclass cameraClass = (jclass) env->CallObjectMethod(classLoader, loadClass, cameraClassName);
    env->DeleteLocalRef(gameActivity);
    env->DeleteLocalRef(cameraClassName);
    env->DeleteLocalRef(activity);
    env->DeleteLocalRef(classLoaderClass);
};