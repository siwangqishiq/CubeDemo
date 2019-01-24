//
// Created by panyi  on 2019/1/23.
//

#include "App.h"
#include <GLES3/gl3.h>
#include <malloc.h>
#include "utils.hpp"

void App::init() {
    //init shader
    ALOGV("init");
    const char vertexShader[] =
            "#version 300 es                             \n"
                    "layout(location = 0) in vec4 a_position;    \n"
                    "layout(location = 1) in vec3 a_color;       \n"
                    "uniform mat4 a_mvp_matrix;                  \n"
                    "out vec3 f_color;                           \n"
                    "void main(){                                \n"
                    "   gl_Position = a_mvp_matrix * a_position; \n"
                    "   f_color = a_color;                       \n"
                    "}                                           \n";

    const char fragShader[] =
            "#version 300 es                             \n"
                    "precision mediump float;                    \n"
                    "in vec3 f_color;                            \n"
                    "out vec4 out_color;                         \n"
                    "void main(){                                \n"
                    "out_color = vec4(f_color.xyz , 1.0f);       \n"
                    "}                                           \n";
    mProgramId = loadShaderProgram(vertexShader, fragShader);
    mMVPMatrixUniformIndex = glGetUniformLocation(mProgramId, "a_mvp_matrix");
    ALOGV("mvp matix pos = %d", mMVPMatrixUniformIndex);

    matrixLookAtM(mViewMatrix,
                  0.0f, 5.0f, 10.0f, //相机位置
                  0.0f, 0.0f, 0.0f,//朝向
                  0.0f, 1.0f, 0.0f //正上方坐标
    );
}


void App::resize(int w, int h) {
    ALOGV("screen width = %d , height = %d", w, h);

    glEnable(GL_DEPTH_TEST);
    glViewport(0, 0, w, h);

    float ratio = (float) w / h;
    matrixSetIdentityM(mPrespectiveMatrix);
    matrixFrustumM(mPrespectiveMatrix, -ratio, ratio, -1, 1, 3, 100);
}

GLuint App::loadShaderProgram(const char *vShaderSrc, const GLchar *fShaderSrc) {
    GLuint vtxShader = 0;
    GLuint fragShader = 0;
    GLuint program = 0;
    GLint linked = GL_FALSE;

    vtxShader = createShader(GL_VERTEX_SHADER, vShaderSrc);
    if (!vtxShader)
        return 0;

    fragShader = createShader(GL_FRAGMENT_SHADER, fShaderSrc);
    if (!fragShader)
        return 0;

    program = glCreateProgram();
    if (!program) {
        return 0;
    }

    glAttachShader(program, vtxShader);
    glAttachShader(program, fragShader);

    glLinkProgram(program);
    glGetProgramiv(program, GL_LINK_STATUS, &linked);
    if (!linked) {
        GLint infoLogLen = 0;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLogLen);
        glDeleteProgram(program);
        return 0;
    }

    return program;
}

GLuint App::createShader(GLenum shaderType, const char *src) {
    GLuint shader = glCreateShader(shaderType);
    if (!shader) {
        return 0;
    }
    glShaderSource(shader, 1, &src, NULL);

    GLint compiled = GL_FALSE;
    glCompileShader(shader);
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
    if (!compiled) {
        GLint infoLogLen = 0;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLen);

        GLchar *infoLog = (GLchar *) malloc(infoLogLen);
        glGetShaderInfoLog(shader, infoLogLen, NULL, infoLog);
        ALOGE("Could not compile %s shader:\n%s\n",
              shaderType == GL_VERTEX_SHADER ? "vertex" : "fragment",
              infoLog);
        glDeleteShader(shader);
        return 0;
    }

    return shader;
}

void App::updateMVPMatrix() {
    matrixSetIdentityM(mModelMatrix);//模型单位
    matrixTranslateM(mModelMatrix , 0, 0 ,0 );
    float modelRoateM[16];
    matrixSetRotateM(modelRoateM, mAngle, 0, 1, 0);
    matrixMultiplyMM(mModelMatrix, mModelMatrix ,modelRoateM);

    matrixSetIdentityM(mMVPMatrix);
    matrixMultiplyMM(mMVPMatrix, mViewMatrix ,mModelMatrix);
    matrixMultiplyMM(mMVPMatrix, mPrespectiveMatrix , mMVPMatrix);
    //debugShowMat(mMVPMatrix);
}

void App::render() {
    ALOGV("render");

    if (mAngle > 360) {
        mAngle = -360;
    }
    mAngle++;
    this->updateMVPMatrix();

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    // render a cube
    glUseProgram(mProgramId);
    glUniformMatrix4fv(mMVPMatrixUniformIndex, 1, false, mMVPMatrix);

    //设置数据
    glVertexAttribPointer(0, 3, GL_FLOAT, false, 0, mCubeVertex);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, false, 0, mCubeColors);
    glEnableVertexAttribArray(1);

    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_SHORT, mCubeIndices);
}

void App::free() {
    glDeleteProgram(mProgramId);
}

void App::debugShowMat(float *mat) {
    ALOGE("%f %f %f %f", mat[0], mat[1], mat[2], mat[3]);
    ALOGE("%f %f %f %f", mat[4], mat[5], mat[6], mat[7]);
    ALOGE("%f %f %f %f", mat[8], mat[9], mat[10], mat[11]);
    ALOGE("%f %f %f %f", mat[12], mat[13], mat[14], mat[15]);
}
