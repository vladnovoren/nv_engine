#include "Shaders/Shader.hpp"

using namespace nv_engine;

Shader_OpenGL::Shader_OpenGL(ShaderType type,
                             const std::filesystem::path& path)
  : type_(GetShaderType_OpenGL(type)) {
  auto source = ReadSource(path);
}

void Shader_OpenGL::Compile(std::string source) {
  shader_id_ = glCreateShader(type_);

  const char* c_shader_source = source.c_str();
  glShaderSource(shader_id_, 1, &c_shader_source, NULL);
  glCompileShader(shader_id_);
  CheckErrors();
}
