#include "Models/Mesh.hpp"

using namespace nv_engine;
using namespace nv_engine::gl;

Mesh::Mesh(aiMesh* ai_mesh, const aiScene* ai_scene) {
  assert(ai_mesh  != nullptr);
  assert(ai_scene != nullptr);

  InitVertices(ai_mesh);
  InitIndices(ai_mesh);
  InitMaterial(ai_mesh, ai_scene);
}

Mesh::Mesh(const std::vector<Vertex>& vertices,
           const std::vector<IndexT>& indices) :
  vertices_(vertices), indices_(indices) {
}

const std::vector<Vertex>& Mesh::GetVertices() const {
  return vertices_;
}

const std::vector<IndexT>& Mesh::GetIndices() const {
  return indices_;
}

void Mesh::InitVertices(aiMesh* ai_mesh) {
  for (size_t i = 0; i < ai_mesh->mNumVertices; ++i) {
    Vertex vertex;

    vertex.position = {
      ai_mesh->mVertices[i].x,
      ai_mesh->mVertices[i].y,
      ai_mesh->mVertices[i].z
    };

    if (ai_mesh->HasNormals()) {
      vertex.normal = {
        ai_mesh->mNormals[i].x,
        ai_mesh->mNormals[i].y,
        ai_mesh->mNormals[i].z
      };
    }

    if (ai_mesh->mTextureCoords[0]) {
      vertex.uv = {
        ai_mesh->mTextureCoords[0][i].x,
        ai_mesh->mTextureCoords[0][i].y
      };

      vertex.tangent = {
        ai_mesh->mTangents[i].x,
        ai_mesh->mTangents[i].y,
        ai_mesh->mTangents[i].z
      };

      vertex.bitangent = {
        ai_mesh->mBitangents[i].x,
        ai_mesh->mBitangents[i].y,
        ai_mesh->mBitangents[i].z
      };
    }

    vertices_.push_back(vertex);
  }

  vbo_.BufferData(vertices_);
  vao_.AddVertexBuffer(vbo_);
}

void Mesh::InitIndices(aiMesh* ai_mesh) {
  for (size_t i = 0; i < ai_mesh->mNumFaces; ++i) {
    aiFace face = ai_mesh->mFaces[i];
    for (size_t j = 0; j < face.mNumIndices; ++j) {
      indices_.push_back(face.mIndices[j]);
    }
  }

  ebo_.BufferData(indices_);
  vao_.SetIndexBuffer(ebo_);
}

void Mesh::InitMaterial(aiMesh* ai_mesh, const aiScene* ai_scene) {
  aiMaterial* ai_material = ai_scene->mMaterials[ai_mesh->mMaterialIndex];

  material_.AddTexture(LoadMaterialTexture(ai_material,
                                           aiTextureType_DIFFUSE));
  material_.AddTexture(LoadMaterialTexture(ai_material,
                                           aiTextureType_SPECULAR));
  material_.AddTexture(LoadMaterialTexture(ai_material,
                                           aiTextureType_NORMALS));
  material_.AddTexture(LoadMaterialTexture(ai_material,
                                           aiTextureType_AMBIENT));
}

Texture2D Mesh::LoadMaterialTexture(aiMaterial* material,
                                    aiTextureType ai_tex_type) {
  assert(material != nullptr);

  aiString path;
  auto tex_type = AssimpToNVTextureType(ai_tex_type);
  if (material->GetTexture(ai_tex_type, 0, &path) == aiReturn_SUCCESS) {
    return Texture2D(path.C_Str(), tex_type);
  } else {
    return Texture2D(Texture2D::GetDefaultTexturePath(tex_type), tex_type);
  }
}

