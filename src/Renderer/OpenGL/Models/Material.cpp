#include "Models/Material.hpp"

using namespace nv_engine::gl;

const std::vector<Texture2D>& Material::GetTextures() const {
  return textures_;
}

