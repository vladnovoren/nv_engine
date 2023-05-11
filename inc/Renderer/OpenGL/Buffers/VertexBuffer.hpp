#pragma once

#include "Buffer.hpp"
#include "BufferLayout.hpp"
#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace nv_engine::gl {
  class VertexBuffer : Buffer {
   public:
    VertexBuffer();
    ~VertexBuffer();

    void Bind() const override;
    void Unbind() const override;
    void BufferData(const void *data, size_t size) override;

    void SetLayout(BufferLayout layout);
    const BufferLayout& GetLayout() const;

   private:
    unsigned int vbo_id_;
    BufferLayout layout_;
  };
} // namespace nv_engine
