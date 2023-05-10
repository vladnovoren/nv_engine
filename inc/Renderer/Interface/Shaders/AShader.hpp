#pragma once

#include <filesystem>
#include <fstream>

namespace nv_engine {
  enum class ShaderType {
    VERTEX,
    FRAGMENT,
    GEOMETRY,
    COMPUTE
  };

  class AShader {
   public:
    virtual ~AShader() = 0;

   protected:
    virtual void Compile(std::string source) = 0;
    virtual void CheckErrors() = 0;

    static std::string ReadSource(const std::filesystem::path& path);
  };
} // namespace nv_engine
