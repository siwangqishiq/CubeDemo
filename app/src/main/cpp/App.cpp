//
// Created by panyi  on 2019/1/23.
//

#include "App.h"
#include <GLES3/gl3.h>
#include <malloc.h>


void App::init() {
    //init shader
    ALOGV("init");
    const char vertexShader[] =
            "#version 300 es                             \n"
                    "layout(location = 0) in vec3 a_position;    \n"
                    "layout(location = 1) in vec3 a_color;       \n"
                    "out vec3 f_color;                           \n"
                    "void main(){                                \n"
                    "   gl_Position = vec4(a_position.xyz ,1.0f);        \n"
                    "f_color = a_color;   \n"
                    "}                                           \n";

    const char fragShader[] =
            "#version 300 es                             \n"
                    "precision mediump float;\n"
                    "in vec3 f_color;\n"
                    "out vec4 out_color;\n"
                    "void main(){\n"
                    "out_color = vec4(f_color.xyz , 1.0f);\n"
                    "}\n";
    mProgramId = loadShaderProgram(vertexShader, fragShader);
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

        GLchar* infoLog = (GLchar*)malloc(infoLogLen);
        glGetShaderInfoLog(shader, infoLogLen, NULL, infoLog);
        ALOGE("Could not compile %s shader:\n%s\n",
              shaderType == GL_VERTEX_SHADER ? "vertex" : "fragment",
              infoLog);
        glDeleteShader(shader);
        return 0;
    }

    return shader;
}

void App::resize(int w, int h) {
    glViewport(0, 0, w, h);
}

void App::render() {
    ALOGV("%d" , mProgramId);
    glClearColor(1.0f, 1.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //
    glUseProgram(mProgramId);

    glVertexAttribPointer(0, 3, GL_FLOAT, false, 0, mVertex);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, false, 0, mColors);
    glEnableVertexAttribArray(1);

    glDrawArrays(GL_TRIANGLES, 0, 3);


    // render a cube

}

void App::free() {
    glDeleteProgram(mProgramId);
}
