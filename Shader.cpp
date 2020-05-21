#include "Shader.h"
#include <GL/glew.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

void Shader::CreateShader(const char *VertexShaderSource, const char *FragmentShaderSource) {
    //渲染器設定
    GLuint vertexShader;
    GLuint fragmentShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    if (glLoadShaderFile(VertexShaderSource, vertexShader) == false)
        fprintf(stdout, "[%s] Load Vertex Shader Failed\n", __FILE__);
    if (glLoadShaderFile(FragmentShaderSource, fragmentShader) == false)
        fprintf(stdout, "[%s] Load Fragment Shader Failed\n", __FILE__);

    int success;
    char InfoLog[512];
    //編譯頂點渲染器
    glCompileShader(vertexShader);
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, NULL, InfoLog);
        fprintf(stdout, "[%s] Vertex Shader %s Error: %s\n", __FILE__, VertexShaderSource, InfoLog);
    }
    //編譯片段渲染器
    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        //InfoLog should be Get before we delete shader
        glGetShaderInfoLog(fragmentShader, 512, NULL, InfoLog);
        fprintf(stdout, "[%s] Fragment Shader %s Error: %s\n", __FILE__, FragmentShaderSource, InfoLog);
    }
    this->Program = glCreateProgram();
    glAttachShader(this->Program, vertexShader);
    glAttachShader(this->Program, fragmentShader);
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
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

void Shader::CreateShader(const char *ComputeShaderSource) {
    GLuint computeShader;
    computeShader = glCreateShader(GL_COMPUTE_SHADER);

    if (glLoadShaderFile(ComputeShaderSource, computeShader) == false)
        fprintf(stderr, "[%s] Load Compute Shader Failed\n", __FILE__);

    int success;
    char InfoLog[512];

    glCompileShader(computeShader);
    glGetShaderiv(computeShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(computeShader, 512, NULL, InfoLog);
        fprintf(stderr, "[%s] Compute Shader %s Error: %s\n", __FILE__, ComputeShaderSource, InfoLog);
    }
    this->Program = glCreateProgram();
    glAttachShader(this->Program, computeShader);
    //連結渲染器
    glLinkProgram(this->Program);
    //生成渲染器
    glGetProgramiv(this->Program, GL_LINK_STATUS, &success);
    if (!success) {
        glDeleteProgram(this->Program);
        glGetProgramInfoLog(this->Program, 1024, NULL, InfoLog);
        fprintf(stderr, "[%s] Shader Error: %s\n", __FILE__, InfoLog);
    }
    glDeleteShader(computeShader);
}

bool Shader::glLoadShaderFile(const char *szFile, GLuint Shader) {
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
        fprintf(stderr, "[%s] Shader file not success loaded\n", __FILE__);
        return false;
    }
    const char *ShaderSource = str.c_str();
    std::cout << ShaderSource << std::endl;
    glShaderSource(Shader, 1, &ShaderSource, NULL);
    return true;
}

void Shader::Use() {
    glUseProgram(this->Program);
}

GLuint Shader::GetProgramID() {
    return this->Program;
}
