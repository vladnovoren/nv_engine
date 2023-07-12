#pragma once

#include "BufferLayout.hpp"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "RenderResourceHandle.hpp"

namespace nv_engine::gl {
class VertexBuffer {
 public:
  VertexBuffer();
  ~VertexBuffer();

  void Bind() const;
  void Unbind() const;

  template <typename T>
  void BufferData(const std::vector<T>& vertices) {
    Bind();
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(T), vertices.data(),
                 GL_STATIC_DRAW);
  }

  void SetLayout(BufferLayout layout);
  const BufferLayout& GetLayout() const;

 private:
  BufferHandle vbo_id_;
  BufferLayout layout_;
};
} // namespace nv_engine
