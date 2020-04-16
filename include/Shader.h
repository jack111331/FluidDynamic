#ifndef OPENGL_CUSTOM_SHADER_H
  #define OPENGL_CUSTOM_SHADER_H

  #include <GL/glew.h>

  class Shader
  {
    public:
      void CreateShader(const char * VertexShaderSource, const char * FragmentShaderSource);
      void Use();
      GLuint GetProgramID();
    private:
      bool glLoadShaderFile(const char * szFile, GLuint Shader);
      GLuint Program;
  };
#endif
