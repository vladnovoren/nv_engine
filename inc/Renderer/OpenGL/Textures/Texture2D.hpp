#pragma once

#include <GL/glew.h>
#include <filesystem>
#include <streambuf>
#include <assimp/material.h>

namespace fs = std::filesystem;

namespace nv_engine::gl {
  enum class TextureType {
    NONE,
    DIFFUSE,
    ALBEDO,
    SPECULAR,
    AMBIENT,
    NORMALS
  };

  TextureType AssimpToNVTextureType(aiTextureType type);

  class Texture2D {
   public:
    Texture2D(const fs::path& path, TextureType type);
    ~Texture2D();

    [[nodiscard]] uint32_t Width() const;
    [[nodiscard]] uint32_t Height() const;

    [[nodiscard]] uint32_t Id() const;

    void Bind(uint32_t unit);

    [[nodiscard]] std::string GetSamplerName() const;

   public:
    static fs::path GetDefaultTexturePath(TextureType type);

   private:
    uint32_t width_;
    uint32_t height_;

    uint32_t texture_id_;

    TextureType type_;

  };
} // namespace nv_engine::gl
