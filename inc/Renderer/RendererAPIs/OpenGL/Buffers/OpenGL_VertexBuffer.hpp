#pragma once

#include "OpenGL_VertexArray.hpp"
#include "AVertexBuffer.hpp"

namespace nv_engine {
  class OpenGL_VertexBuffer : public AVertexBuffer {
   public:
    OpenGL_VertexBuffer();
    ~OpenGL_VertexBuffer() override;

    void Bind() const override;
    void Unbind() const override;
    void BufferData(const void *data, size_t size) override;

    void SetLayout(BufferLayout layout) override;
    const BufferLayout& GetLayout() const override;

   private:
    unsigned int vbo_id_;
    BufferLayout layout_;
  };
} // namespace nv_engine
