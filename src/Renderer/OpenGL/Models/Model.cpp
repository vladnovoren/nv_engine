#include "Models/Model.hpp"
#include <assimp/Importer.hpp>

using namespace nv_engine::gl;

Model::Model(const fs::path& path) {
  LoadFromFile(path);
}

void Model::LoadFromFile(const fs::path& path) {
  Assimp::Importer importer;
  const aiScene* scene = importer.ReadFile(path,
                                           aiProcess_Triangulate |
                                           aiProcess_SortByPType |
                                           aiProcess_GenSmoothNormals |
                                           aiProcess_CalcTangentSpace |
                                           aiProcess_GenUVCoords);

  if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE ||
      !scene->mRootNode) {
    throw std::runtime_error(importer.GetErrorString());
  }

  ProcessNode(scene->mRootNode, scene);
}

void Model::ProcessNode(aiNode* node, const aiScene* scene) {
  assert(node  != nullptr);
  assert(scene != nullptr);

  for (size_t i = 0; i < node->mNumMeshes; ++i) {
    aiMesh* ai_mesh = scene->mMeshes[node->mMeshes[i]];
    meshes_.emplace_back(ai_mesh, scene);
  }

  for (size_t i = 0; i < node->mNumChildren; ++i) {
    ProcessNode(node->mChildren[i], scene);
  }
}

const std::vector<Mesh>& Model::GetMeshes() const {
  return meshes_;
}

