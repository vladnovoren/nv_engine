#pragma once

#include "BufferLayout.hpp"
#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace nv_engine::gl {
  class VertexBuffer {
   public:
    VertexBuffer();
    ~VertexBuffer();

    void Bind() const;
    void Unbind() const;
    void BufferData(const void *data, size_t size);

    void SetLayout(BufferLayout layout);
    const BufferLayout& GetLayout() const;

   private:
    unsigned int vbo_id_;
    BufferLayout layout_;
  };
} // namespace nv_engine
