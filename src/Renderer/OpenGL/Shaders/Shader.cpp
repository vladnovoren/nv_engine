#include "Shaders/Shader.hpp"

using namespace nv_engine::gl;

Shader::Shader(ShaderType type, const std::filesystem::path& path)
  : type_(GetShaderType(type)) {
  auto source = ReadSource(path);
}

std::string Shader::ReadSource(const std::filesystem::path& path) {
  std::ifstream in_file_stream(path.string(), std::ios::in);

  std::string shader_source;

  if (in_file_stream.is_open()) {
    std::stringstream str_stream;
    str_stream << in_file_stream.rdbuf();
    shader_source = str_stream.str();
    in_file_stream.close();
  } else {
    throw std::runtime_error("unable to open file [" + path.string() +
                             "] for compiling shaders");
  }

  return shader_source;
}

void Shader::Compile(std::string source) {
  shader_id_ = glCreateShader(type_);

  const char* c_shader_source = source.c_str();
  glShaderSource(shader_id_, 1, &c_shader_source, NULL);
  glCompileShader(shader_id_);
  CheckErrors();
}

void Shader::CheckErrors() {
  int result = GL_FALSE;
  int info_log_length = 0;
  glGetShaderiv(shader_id_, GL_COMPILE_STATUS, &result);
  glGetShaderiv(shader_id_, GL_INFO_LOG_LENGTH, &info_log_length);
  if (info_log_length > 0) {
    std::vector<char> shader_error_msg(info_log_length + 1);
    glGetShaderInfoLog(shader_id_, info_log_length, NULL, &shader_error_msg[0]);
    printf("%s\n", &shader_error_msg[0]);
    throw std::runtime_error("Shader compiling errors occured");
  }
}
