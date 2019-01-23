//
// Created by panyi  on 2019/1/23.
//

#ifndef CUBEDEMO_APP_H
#define CUBEDEMO_APP_H

#include <android/log.h>
#include <GLES3/gl3.h>

#define DEBUG 1

#define LOG_TAG "GLES3JNI"
#define ALOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)
#if DEBUG
#define ALOGV(...) __android_log_print(ANDROID_LOG_VERBOSE, LOG_TAG, __VA_ARGS__)
#else
#define ALOGV(...)
#endif


class App{

protected:
    GLuint mProgramId;
    float mVertex[3 * 3]={
        -0.5f ,  0.0f,    0.0f,
        0.5f ,   0.0f,    0.0f,
        0.0f,    1.0f ,   0.0f
    };

    float mColors[3 * 3] = {
        1.0f , 0.0f , 0.0f,
        1.0f, 0.0f ,  0.0f,
        0.0f , 1.0f , 0.0f
    };

    GLuint loadShaderProgram(const GLchar *vShader ,const GLchar *fShader);

    GLuint createShader(GLenum shaderType, const char* src);
public:
    void init();

    void resize(int w ,int h);

    void render();

    void free();
};

#endif //CUBEDEMO_APP_H
