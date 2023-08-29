LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

LOCAL_MODULE := camera
LOCAL_MODULE_FILEMAKE := camera

LOCAL_CFLAGS := -DNOMINMAX
LOCAL_CPPFLAGS := -std=c++11

LOCAL_ARM_NEON= := true

LOCAL_C_INCLUDES := \
	${LOCAL_PATH}/src \
	${LOCAL_PATH}/src/android

LOCAL_SRC_FILES := \
	src/lua/main.cpp \
	src/android/Android.cpp

LOCAL_SHARED_LIBRARIES := liblove

include $(BUILD_SHARED_LIBRARY)
