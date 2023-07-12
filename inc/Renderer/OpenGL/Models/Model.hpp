#include "Mesh.hpp"
#include "Textures/Texture2D.hpp"

namespace fs = std::filesystem;

namespace nv_engine::gl {
class Model {
 public:
  Model(const fs::path& path);

  const std::vector<Mesh>& GetMeshes() const;

 private:
  void LoadFromFile(const fs::path& path);

  void ProcessNode(aiNode* node, const aiScene* scene);

 private:
  std::vector<Mesh> meshes_;
};
} // namespace nv_engine::gl

