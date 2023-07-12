#include "Textures/Texture2D.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

using namespace nv_engine::gl;

TextureType nv_engine::gl::AssimpToNVTextureType(aiTextureType type) {
  switch (type) {
    case aiTextureType_NONE:
      return TextureType::NONE;
    case aiTextureType_DIFFUSE:
      return TextureType::DIFFUSE;
    case aiTextureType_SPECULAR:
      return TextureType::SPECULAR;
    case aiTextureType_AMBIENT:
      return TextureType::AMBIENT;
    case aiTextureType_NORMALS:
      return TextureType::NORMALS;
    default:
      throw std::runtime_error("this texture type is not supported");
  };
}

Texture2D::Texture2D(const fs::path& path, TextureType type) : type_(type) {
  stbi_set_flip_vertically_on_load(1);

  int i_width = 0, i_height = 0, n_channels = 0;
  auto data = stbi_load(path.c_str(), &i_width, &i_height, &n_channels, 0);
  if (data == nullptr) {
    throw std::runtime_error("error loading texture file: " + path.string());
  }

  width_ = i_width;
  height_ = i_height;

  GLenum internalFormat = 0, dataFormat = 0;
  if (n_channels == 4) {
    internalFormat = GL_RGBA8;
    dataFormat = GL_RGBA;
  } else if (n_channels == 3) {
    internalFormat = GL_RGB8;
    dataFormat = GL_RGB;
  }

  glCreateTextures(GL_TEXTURE_2D, 1, &texture_id_);
  glTextureStorage2D(texture_id_, 1, internalFormat, width_, height_);

  glTextureParameteri(texture_id_, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTextureParameteri(texture_id_, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  glTextureParameteri(texture_id_, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTextureParameteri(texture_id_, GL_TEXTURE_WRAP_T, GL_REPEAT);

  glTextureSubImage2D(texture_id_, 0, 0, 0, width_, height_, dataFormat,
                      GL_UNSIGNED_BYTE, data);

  stbi_image_free(data);
}

Texture2D::~Texture2D() {
  glDeleteTextures(1, &texture_id_);
}

uint32_t Texture2D::Width() const {
  return width_;
}

uint32_t Texture2D::Height() const {
  return height_;
}

uint32_t Texture2D::Id() const {
  return texture_id_;
}

void Texture2D::Bind(uint32_t unit) {
  glBindTextureUnit(unit, texture_id_);
}

fs::path Texture2D::GetDefaultTexturePath(TextureType type) {
  switch (type) {
    case TextureType::NONE:
    case TextureType::DIFFUSE:
    case TextureType::SPECULAR:
    case TextureType::AMBIENT:
      return "../assets/textures/default/blank.png";
    case TextureType::NORMALS:
      return "../assets/textures/default/blank_normal.png";
  }
  return "";
}

std::string Texture2D::GetSamplerName() const {
  switch (type_) {
    case TextureType::NONE:
      return "uAmbientMap";
    case TextureType::DIFFUSE:
      return "uAmbientMap";
    case TextureType::SPECULAR:
      return "uAmbientMap";
    case TextureType::AMBIENT:
      return "uAmbientMap";
    case TextureType::NORMALS:
      return "uAmbientMap";
  }
  return "";
}
