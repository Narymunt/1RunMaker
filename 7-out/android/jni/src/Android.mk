LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := main

SDL_PATH := ../SDL
SDL_IMG_PATH := ../SDL_image
SDL_MIXER_PATH := ../SDL_mixer

LOCAL_C_INCLUDES := $(LOCAL_PATH)/$(SDL_PATH)/include \
					$(LOCAL_PATH)/$(SDL_IMG_PATH) \
					$(LOCAL_PATH)/$(SDL_MIXER_PATH) 
										

# Add your application source files here...
LOCAL_SRC_FILES := $(SDL_PATH)/src/main/android/SDL_android_main.c \
	Main.cpp \
	GameObject.cpp \
	application/Ingame.cpp \
	application/State.cpp \
	application/Intro.cpp \
	application/MainMenu.cpp \
	control/Touch.cpp \
	system/AndroidFile.cpp \
	system/Profile.cpp \
	gfx/Button.cpp \
	gfx/Screen.cpp \
	gfx/Sprite.cpp \
	gfx/OGL.cpp \
	gfx/SpriteFont.cpp \
	gfx/MobileKeyboard.cpp \
	gfx/Particle2D.cpp \
	gfx/Particle2DManager.cpp \
	gfx/FXManager.cpp \
	gfx\Animation.cpp \
	gfx\Popup.cpp \
	math/Bezier.cpp \
	math/CRSpline.cpp \
	math/Tween.cpp

LOCAL_SHARED_LIBRARIES := SDL2 SDL2_image SDL2_mixer

LOCAL_LDLIBS := -lGLESv1_CM -llog -landroid

include $(BUILD_SHARED_LIBRARY)
