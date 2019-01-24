//
// Created by panyi  on 2019/1/23.
//

#ifndef CUBEDEMO_APP_H
#define CUBEDEMO_APP_H

#include <android/log.h>
#include <GLES3/gl3.h>

#define DEBUG 1

#define LOG_TAG "DemoShowLogTag"
#define ALOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)
#if DEBUG
#define ALOGV(...) __android_log_print(ANDROID_LOG_VERBOSE, LOG_TAG, __VA_ARGS__)
#else
#define ALOGV(...)
#endif


class App{

protected:
    GLuint mProgramId;
    float mCubeVertex[8 * 3] = {
            -1.0f, 1.0f, 1.0f,    //正面左上0
            -1.0f, -1.0f, 1.0f,   //正面左下1
            1.0f, -1.0f, 1.0f,    //正面右下2
            1.0f, 1.0f, 1.0f,     //正面右上3
            -1.0f, 1.0f, -1.0f,    //反面左上4
            -1.0f, -1.0f, -1.0f,   //反面左下5
            1.0f, -1.0f, -1.0f,    //反面右下6
            1.0f, 1.0f, -1.0f,     //反面右上7
    };

    unsigned short mCubeIndices[36] = {
            0, 3, 2, 0, 2, 1,    //正面
            0, 1, 5, 0, 5, 4,    //左面
            0, 7, 3, 0, 4, 7,    //上面
            6, 7, 4, 6, 4, 5,    //后面
            6, 3, 7, 6, 2, 3,    //右面
            6, 5, 1, 6, 1, 2     //下面
    };

    float mCubeColors [8 * 3] = {
            0.0f,1.0f,0.0f,
            0.0f,1.0f,0.0f,
            0.0f,1.0f,0.0f,
            0.0f,1.0f,0.0f,
            1.0f,0.0f,0.0f,
            1.0f,0.0f,0.0f,
            1.0f,0.0f,0.0f,
            1.0f,0.0f,0.0f,
    };

    float mModelMatrix[4 * 4];
    float mViewMatrix[4 * 4];//相机变换
    float mPrespectiveMatrix[4 * 4];

    float mMVPMatrix[4 * 4];//最终变换完成的矩阵
    GLint mMVPMatrixUniformIndex;

    float mAngle;

    void updateMVPMatrix();

    GLuint loadShaderProgram(const GLchar *vShader ,const GLchar *fShader);
    GLuint createShader(GLenum shaderType, const char* src);

    void debugShowMat(float *m);
public:
    void init();

    void resize(int w ,int h);

    void render();

    void free();
};


#endif //CUBEDEMO_APP_H
