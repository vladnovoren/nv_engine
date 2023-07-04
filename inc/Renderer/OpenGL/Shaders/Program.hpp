#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <cassert>
#include "Shaders/Shader.hpp"

namespace nv_engine::gl {
  class Program {
   public:
    Program(const std::filesystem::path& vert_path,
            const std::filesystem::path& frag_path);
    Program(const Shader& vert, const Shader& frag);

    void SetUniform(const std::string& name, int value);
    void SetUniform(const std::string& name, float value);
    void SetUniform(const std::string& name, const glm::vec2& value);
    void SetUniform(const std::string& name, const glm::vec3& value);
    void SetUniform(const std::string& name, const glm::vec4& value);
    void SetUniform(const std::string& name, const glm::mat3& value);
    void SetUniform(const std::string& name, const glm::mat4& value);

    int GetAttribLocation(const std::string& name);

    void Use();

   private:
    unsigned int GetUniform(const std::string& name);

    void AttachShader(const Shader& shader);
    void LinkProgram();
    void CheckErrors();

    unsigned int program_id_ = 0;
  };
} // namespace nv_engine::gl
