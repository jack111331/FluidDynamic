#ifndef OPENGL_CUSTOM_SHADER_H
#define OPENGL_CUSTOM_SHADER_H

#include <cstdint>
#include <vector>

class Shader {
public:
//    template <uint32_t shaderType, const char *source>
//    Shader();

    Shader(const char *vertexShaderSource, const char *fragmentShaderSource);

    explicit Shader(const char *computeShaderSource);

    Shader() = default;

    virtual ~Shader();

    void addShader(uint32_t shaderType, const char *source);

    Shader &addAttachShader(const Shader *source);

    void attachToProgram(uint32_t program) const;

    Shader &buildShader();

    void bind() const;

    void bindBuffer(uint32_t bufferId, int location) const;

    void dispatch() const;

    void uniform1f(const char* uniformName, float val) const;

    uint32_t getProgramId();

private:
    bool glLoadShaderFile(const char *szFile, uint32_t shader) const;

    std::vector<uint32_t> m_shaderList;

    std::vector<const Shader *> m_attachShaderList;

    uint32_t m_program;

};

#endif
