#ifndef OPENGL_CUSTOM_SHADER_H
#define OPENGL_CUSTOM_SHADER_H

#include <cstdint>

class Shader {
public:
    void createShader(const char *vertexShaderSource, const char *fragmentShaderSource);
    void createShader(const char *computeShaderSource);

    void use();
    void bindBuffer(uint32_t bufferId, int location);

    uint32_t getProgramID();

private:
    bool glLoadShaderFile(const char *szFile, uint32_t shader);

    uint32_t m_program;
};

#endif
