#include "Shaders/Program.hpp"

using namespace nv_engine::gl;

Program::Program(const std::filesystem::path& vert_path,
                 const std::filesystem::path& frag_path) :
  Program(Shader(ShaderType::VERTEX, vert_path),
          Shader(ShaderType::FRAGMENT, frag_path)) {
}

Program::Program(const Shader& vert, const Shader& frag) {
  assert(vert.Type() == ShaderType::VERTEX);
  assert(frag.Type() == ShaderType::FRAGMENT);

  program_id_ = glCreateProgram();

  AttachShader(vert);
  AttachShader(frag);

  LinkProgram();

  CheckErrors();
}

unsigned int Program::GetUniform(const std::string& name) {
  return glGetUniformLocation(program_id_, name.c_str());
}

void Program::SetUniform(const std::string& name, int value) {
  glUniform1i(GetUniform(name), value);
}

void Program::SetUniform(const std::string& name, float value) {
  glUniform1f(GetUniform(name), value);
}

void Program::SetUniform(const std::string& name, const glm::vec2& value) {
  glUniform2f(GetUniform(name), value.x, value.y);
}

void Program::SetUniform(const std::string& name, const glm::vec3& value) {
  glUniform3f(GetUniform(name), value.x, value.y, value.z);
}

void Program::SetUniform(const std::string& name, const glm::vec4& value) {
  glUniform4f(GetUniform(name), value.x, value.y, value.z, value.w);
}

void Program::SetUniform(const std::string& name, const glm::mat3& value) {
  glUniformMatrix3fv(GetUniform(name), 1, GL_FALSE, &value[0][0]);
}

void Program::SetUniform(const std::string& name, const glm::mat4& value) {
  glUniformMatrix4fv(GetUniform(name), 1, GL_FALSE, &value[0][0]);
}

void Program::AttachShader(const Shader& shader) {
  glAttachShader(program_id_, shader);
}

void Program::LinkProgram() {
  glLinkProgram(program_id_);
}

void Program::CheckErrors() {
  int result = GL_FALSE;
  int info_log_length = 0;
  glGetProgramiv(program_id_, GL_LINK_STATUS, &result);
  glGetProgramiv(program_id_, GL_INFO_LOG_LENGTH, &info_log_length);
  if (info_log_length > 0) {
    std::vector<char> ProgramErrorMessage(info_log_length + 1);
    glGetProgramInfoLog(program_id_, info_log_length, NULL,
                        &ProgramErrorMessage[0]);
    printf("%s\n", &ProgramErrorMessage[0]);
  }
}
