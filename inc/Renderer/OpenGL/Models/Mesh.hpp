#pragma once

#include <filesystem>
#include <vector>
#include <glm/glm.hpp>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/GltfMaterial.h>
#include <assimp/postprocess.h>
#include <stdexcept>
#include "Core/Types.hpp"
#include "Material.hpp"
#include "Buffers/VertexArray.hpp"

namespace fs = std::filesystem;

namespace nv_engine::gl {
struct Vertex {
  glm::vec3 position;
  glm::vec2 uv;
  glm::vec3 normal;

  glm::vec3 tangent;
  glm::vec3 bitangent;
};

class Mesh {
 public:
  Mesh(aiMesh* ai_mesh, const aiScene* ai_scene);
  Mesh(const std::vector<Vertex>& vertices, const std::vector<IndexT>& indices);

  const std::vector<Vertex>& GetVertices() const;
  const std::vector<IndexT>& GetIndices() const;

  BufferHandle GetVertexBuffer() const;
  BufferHandle GetIndexBuffer() const;

 private:
  void InitVertices(aiMesh* ai_mesh);
  void InitIndices(aiMesh* ai_mesh);
  void InitMaterial(aiMesh* ai_mesh, const aiScene* ai_scene);
  Texture2D LoadMaterialTexture(aiMaterial* material,
                                aiTextureType ai_tex_type);

 private:
  std::vector<Vertex> vertices_;
  std::vector<IndexT> indices_;

  VertexArray vao_;
  VertexBuffer vbo_;
  IndexBuffer ebo_;

  Material material_;
};
} // namespace nv_engine::gl

