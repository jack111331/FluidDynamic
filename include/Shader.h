#ifndef OPENGL_CUSTOM_SHADER_H
#define OPENGL_CUSTOM_SHADER_H

#include <cstdint>

class Shader {
public:
    void CreateShader(const char *VertexShaderSource, const char *FragmentShaderSource);

    void Use();

    uint32_t GetProgramID();

private:
    bool glLoadShaderFile(const char *szFile, uint32_t Shader);

    uint32_t Program;
};

#endif
