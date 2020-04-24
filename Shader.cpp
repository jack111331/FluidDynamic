#include "Shader.h"
#include <GL/glew.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

void Shader::CreateShader(const char *VertexShaderSource, const char *FragmentShaderSource) {
    //渲染器設定
    GLuint VertexShader;
    GLuint FragmentShader;
    VertexShader = glCreateShader(GL_VERTEX_SHADER);
    FragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    if (glLoadShaderFile(VertexShaderSource, VertexShader) == false)
        fprintf(stdout, "[%s] Load Vertex Shader Failed\n", __FILE__);
    if (glLoadShaderFile(FragmentShaderSource, FragmentShader) == false)
        fprintf(stdout, "[%s] Load Fragment Shader Failed\n", __FILE__);

    int success;
    char InfoLog[512];
    //編譯頂點渲染器
    glCompileShader(VertexShader);
    glGetShaderiv(VertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(VertexShader, 512, NULL, InfoLog);
        fprintf(stdout, "[%s] Vertex Shader %s Error: %s\n", __FILE__, VertexShaderSource, InfoLog);
    }
    //編譯顏色渲染器
    glCompileShader(FragmentShader);
    glGetShaderiv(FragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        //InfoLog should be Get before we delete shader
        glGetShaderInfoLog(FragmentShader, 512, NULL, InfoLog);
        fprintf(stdout, "[%s] Fragment Shader %s Error: %s\n", __FILE__, FragmentShaderSource, InfoLog);
    }
    this->Program = glCreateProgram();
    glAttachShader(this->Program, VertexShader);
    glAttachShader(this->Program, FragmentShader);
    glBindAttribLocation(this->Program, 0, "vertex");
    //連結渲染器
    glLinkProgram(this->Program);
    //生成渲染器
    glGetProgramiv(this->Program, GL_LINK_STATUS, &success);
    if (!success) {
        glDeleteProgram(this->Program);
        glGetProgramInfoLog(this->Program, 1024, NULL, InfoLog);
        fprintf(stdout, "[%s] Shader Error: %s\n", __FILE__, InfoLog);
    }
    glDeleteShader(VertexShader);
    glDeleteShader(FragmentShader);
}

bool Shader::glLoadShaderFile(const char *szFile, GLuint Shader) {
    //讀入渲染器檔案
    std::ifstream ShaderFile;
    ShaderFile.exceptions(std::ifstream::badbit);
    std::string str;
    try {
        ShaderFile.open(szFile);
        std::stringstream ss;
        ss << ShaderFile.rdbuf();
        ShaderFile.close();
        str = ss.str();
    }
    catch (std::ifstream::failure e) {
        fprintf(stdout, "[%s] Shader file not success loaded\n", __FILE__);
        return false;
    }
    const char *ShaderSource = str.c_str();
    glShaderSource(Shader, 1, &ShaderSource, NULL);
    return true;
}

void Shader::Use() {
    glUseProgram(this->Program);
}

GLuint Shader::GetProgramID() {
    return this->Program;
}
