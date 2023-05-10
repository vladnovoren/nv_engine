#include "Shaders/AShader.hpp"

using namespace nv_engine;

AShader::~AShader() = default;

std::string AShader::ReadSource(const std::filesystem::path& path) {
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
