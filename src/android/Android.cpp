#include <jni.h>
#include <dlfcn.h>
#include <string>
#include <sstream>
#include "Android.h"

#include <android/log.h>
#define LOG(...) __android_log_print(ANDROID_LOG_VERBOSE, "LuaCamera", __VA_ARGS__);

static std::string replace(const std::string &str, const std::string &from, const std::string &to) {
    std::stringstream ss;
    size_t oldpos = 0;

    while (true) {
    	size_t pos = str.find(from, oldpos);
	
    	if (pos == std::string::npos) {
	    ss << str.substr(oldpos);
	    break;
	}

	ss << str.substr(oldpos, pos - oldpos) << to;
	oldpos = pos + from.length();
    }

    return ss.str();
}
static jstring newStringUTF(JNIEnv *env, const std::string &str) {
    // We want std::string that contains null byte, hence length of 1.
    static std::string null("", 1);
    std::string newStr = replace(str, null, "\xC0\x80");
    jstring jstr = env->NewStringUTF(newStr.c_str());
    return jstr;
}

static std::string getStringUTF(JNIEnv *env, jstring str) {
    if (str == nullptr) {
	std::string sttr;
	return sttr;
    }
    static std::string null("", 1);
    const char *c = env->GetStringUTFChars(str, nullptr);
    std::string result = replace(c, "\xC0\x80", null);
    env->ReleaseStringUTFChars(str, c);
    return result;
};


Android::Android() : SDL_AndroidGetJNIEnv(nullptr) {
    // Look for SDL_AndroidGetJNIEnv
    SDL_AndroidGetJNIEnv = (decltype(SDL_AndroidGetJNIEnv)) dlsym(RTLD_DEFAULT, "SDL_AndroidGetJNIEnv");
    // Look for SDL_AndroidGetActivity
    SDL_AndroidGetActivity = (decltype(SDL_AndroidGetActivity)) dlsym(RTLD_DEFAULT, "SDL_AndroidGetActivity");
    cameraClass = getCameraClass();
    JNIEnv *env = SDL_AndroidGetJNIEnv();
    jmethodID constructor = env->GetMethodID(cameraClass, "<init>", "()V");
    camera = env->NewObject(cameraClass, constructor);
}

std::string Android::getSnap() {
    JNIEnv *env = SDL_AndroidGetJNIEnv();
    jmethodID getPicture = env->GetMethodID(cameraClass, "getPicture", "()Ljava/lang/String;");
    jstring str = (jstring) env->CallObjectMethod(camera, getPicture);
    std::string out = getStringUTF(env, str);
    env->DeleteLocalRef(str);
    return out;
};

void Android::activate() {
    JNIEnv *env = SDL_AndroidGetJNIEnv();
    jmethodID activate = env->GetMethodID(cameraClass, "activate", "()V");
    env->CallVoidMethod(camera, activate);
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
    return cameraClass;
};
