#ifndef MATERIAL_IMPL
#error Do not include this file directly
#endif

namespace nv_engine::gl {
template <typename... ArgsT>
void Material::AddTexture(ArgsT&&... args) {
  textures_.emplace_back(std::forward<ArgsT>(args)...);
}
} // namespace nv_engine::gl

