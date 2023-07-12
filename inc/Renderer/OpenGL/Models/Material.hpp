#pragma once

#include "Textures/Texture2D.hpp"
#include <vector>
#include <utility>

namespace nv_engine::gl {
class Material {
 public:
  template <typename... ArgsT>
  void AddTexture(ArgsT&&... args);

  const std::vector<Texture2D>& GetTextures() const;

 private:
  std::vector<Texture2D> textures_;
};
} // namespace nv_engine::gl

#define MATERIAL_IMPL
#include "Material.ipp"
#undef MATERIAL_IMPL

