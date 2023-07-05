#pragma once

#include <GL/glew.h>
#include <filesystem>
#include <streambuf>

namespace fs = std::filesystem;

namespace nv_engine::gl {
  class Texture2D {
   public:
    Texture2D(const fs::path& path);
    ~Texture2D();

    uint32_t Width() const;
    uint32_t Height() const;

    uint32_t Id() const;

    void Bind(uint32_t unit);

   private:
    uint32_t width_;
    uint32_t height_;

    uint32_t texture_id_;
    
  };
} // namespace nv_engine::gl
