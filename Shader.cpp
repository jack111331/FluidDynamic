#include "Shader.h"
#include <GL/glew.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

void Shader::createShader(const char *vertexShaderSource, const char *fragmentShaderSource) {
    //渲染器設定
    int success;
    char InfoLog[512];
    uint32_t vertexShader = glCreateShader(GL_VERTEX_SHADER);
    uint32_t fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    if (glLoadShaderFile(vertexShaderSource, vertexShader) == false) {
        fprintf(stdout, "[%s] Load vertex shader failed\n", __FILE__);
        exit(1);
    }
    if (glLoadShaderFile(fragmentShaderSource, fragmentShader) == false) {
        fprintf(stdout, "[%s] Load fragment shader failed\n", __FILE__);
        exit(1);
    }

    glCompileShader(vertexShader);
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertexShader, sizeof(InfoLog), NULL, InfoLog);
        fprintf(stdout, "[%s] Vertex Shader %s:\n%s\n", __FILE__, vertexShaderSource, InfoLog);
        exit(1);
    }
    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        //InfoLog should be Get before we delete shader
        glGetShaderInfoLog(fragmentShader, sizeof(InfoLog), NULL, InfoLog);
        fprintf(stdout, "[%s] Fragment Shader %s:\n%s\n", __FILE__, fragmentShaderSource, InfoLog);
        exit(1);
    }

    this->m_program = glCreateProgram();
    glAttachShader(this->m_program, vertexShader);
    glAttachShader(this->m_program, fragmentShader);

    glLinkProgram(this->m_program);

    glGetProgramiv(this->m_program, GL_LINK_STATUS, &success);
    if (!success) {
        glDeleteProgram(this->m_program);
        glGetProgramInfoLog(this->Program, sizeof(InfoLog), NULL, InfoLog);
        fprintf(stdout, "[%s] Shader Error: %s\n", __FILE__, InfoLog);
        exit(1);
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

void Shader::createShader(const char *computeShaderSource) {
    int success;
    char InfoLog[512];
    GLuint computeShader = glCreateShader(GL_COMPUTE_SHADER);


    if (glLoadShaderFile(computeShaderSource, computeShader) == false)
        fprintf(stderr, "[%s] Load Compute Shader Failed\n", __FILE__);


    glCompileShader(computeShader);
    glGetShaderiv(computeShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(computeShader, sizeof(InfoLog), NULL, InfoLog);
        fprintf(stderr, "[%s] Compute Shader %s:\n%s\n", __FILE__, ComputeShaderSource, InfoLog);
    }
    this->m_program = glCreateProgram();
    glAttachShader(this->m_program, computeShader);

    glLinkProgram(this->m_program);

    glGetProgramiv(this->m_program, GL_LINK_STATUS, &success);
    if (!success) {
        glDeleteProgram(this->m_program);
        glGetProgramInfoLog(this->Program, sizeof(InfoLog), NULL, InfoLog);
        fprintf(stderr, "[%s] Shader Error: %s\n", __FILE__, InfoLog);
    }

    glDeleteShader(computeShader);
}

bool Shader::glLoadShaderFile(const char *szFile, GLuint shader) {
    std::ifstream ShaderFile;
    shaderFile.exceptions(std::ifstream::badbit);
    std::string str;
    try {
        shaderFile.open(szFile);
        std::stringstream ss;
        ss << shaderFile.rdbuf();
        shaderFile.close();
        str = ss.str();
    } catch (std::ifstream::failure e) {
        fprintf(stderr, "[%s] Shader file not success loaded\n", __FILE__);
        return false;
    }
    const char *shaderSource = str.c_str();
    glShaderSource(shader, 1, &shaderSource, NULL);
    return true;
}

void Shader::bind() {
    glUseProgram(this->program);
}

void Shader::bindBuffer(uint32_t bufferId, int location) {
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, location, bufferId);
}

void Shader::dispatch() {
    glDispatchCompute(1, 1, 1);
}

GLuint Shader::getProgramID() {
    return this->m_program;
}
