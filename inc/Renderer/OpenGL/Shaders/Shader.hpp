#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <filesystem>
#include <string>
#include <fstream>

namespace nv_engine::gl {
  enum class ShaderType {
    VERTEX,
    FRAGMENT,
    GEOMETRY,
    COMPUTE
  };

  [[maybe_unused]] static unsigned int GetGLShaderType(ShaderType type) {
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

  class Shader {
   public:
    Shader(ShaderType type, const std::filesystem::path& path);
    ~Shader();

    operator unsigned int() const;
    ShaderType Type() const;

   protected:
    static std::string ReadSource(const std::filesystem::path& path);

    void Compile(std::string source);
    void CheckErrors();

    unsigned int shader_id_ = 0;
    ShaderType type_;
  };
} // namespace nv_engine::gl
