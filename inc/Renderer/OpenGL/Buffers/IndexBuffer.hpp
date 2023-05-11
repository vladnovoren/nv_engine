#pragma once

#include "Buffer.hpp"
#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace nv_engine::gl {
  class IndexBuffer : Buffer {
   public:
    IndexBuffer();
    ~IndexBuffer();

    void BufferData(const void* data, size_t size) override;

    void Bind() const override;
    void Unbind() const override;

   protected:
    unsigned int ebo_id_;
  };
}
