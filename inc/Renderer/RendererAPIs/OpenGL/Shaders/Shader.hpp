#pragma once

#include "Shaders/AShader.hpp"
#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace nv_engine {
  [[maybe_unused]] static unsigned int GetShaderType_OpenGL(ShaderType type) {
    switch (type) {
      case ShaderType::VERTEX:
        return GL_VERTEX_SHADER;
      case ShaderType::FRAGMENT:
        return GL_FRAGMENT_SHADER;
      case ShaderType::GEOMETRY:
        return GL_GEOMETRY_SHADER;
      case ShaderType::COMPUTE:
        return GL_COMPUTE_SHADER;
    }
    return 0;
  }

  class Shader_OpenGL : public AShader {
   public:
    Shader_OpenGL(ShaderType type, const std::filesystem::path& path);
    ~Shader_OpenGL() override;

    operator unsigned int() const;

   protected:
    void Compile(std::string source) override;
    void CheckErrors() override;

    unsigned int shader_id_ = 0;
    unsigned int type_ = 0;
  };
} // namespace nv_engine
