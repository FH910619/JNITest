LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := jnitest
LOCAL_SRC_FILES := jnitest.c
LOCAL_LDLIBS += -L$(SYSROOT)/usr/lib -llog
LOCAL_SHARED_LIBRARIES := libdvm
include $(BUILD_SHARED_LIBRARY)
