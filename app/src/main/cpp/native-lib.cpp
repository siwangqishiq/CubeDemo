#include <jni.h>
#include <string>
#include "App.h"



extern "C"
JNIEXPORT jstring JNICALL
Java_com_xinlan_cubedemo_NativeBridge_stringFromJNI(JNIEnv *env, jclass type) {
    std::string hello = "Hello from GeassPanyi";
    return env->NewStringUTF(hello.c_str());
}

static App *app;


extern "C"
JNIEXPORT void JNICALL
Java_com_xinlan_cubedemo_NativeBridge_init(JNIEnv *env, jclass type) {
    if(app != nullptr){
        delete app;
    }

    app = new App();
    app->init();
}


extern "C"
JNIEXPORT void JNICALL
Java_com_xinlan_cubedemo_NativeBridge_render(JNIEnv *env, jclass type) {
    if(app != nullptr){
        app->render();
    }
}

extern "C"
JNIEXPORT void JNICALL
Java_com_xinlan_cubedemo_NativeBridge_free(JNIEnv *env, jclass type) {
    if(app != nullptr){
        app->free();
    }
}

extern "C"
JNIEXPORT void JNICALL
Java_com_xinlan_cubedemo_NativeBridge_resize(JNIEnv *env, jclass type, jint width, jint height) {
    if(app != nullptr){
        app->resize(width , height);
    }
}