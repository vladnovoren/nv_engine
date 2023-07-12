#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>
#include "RenderResourceHandle.hpp"

namespace nv_engine::gl {
class IndexBuffer {
 public:
  IndexBuffer();
  ~IndexBuffer();

  template <typename T>
  void BufferData(const std::vector<T>& indices) {
    /*
      GL_ELEMENT_ARRAY_BUFFER is not valid without an active bound VAO
      GL_ARRAY_BUFFER allows to bind and buffer data regardless of VAO state
      then you can interpret it as GL_ELEMENT_ARRAY_BUFFER when some VAO
      will be bound
    **/
    glBindBuffer(GL_ARRAY_BUFFER, ebo_id_);
    glBufferData(GL_ARRAY_BUFFER, indices.size() * sizeof(T), indices.data(),
                 GL_STATIC_DRAW);
  }

  void Bind() const;
  void Unbind() const;

  operator unsigned int() const;

 protected:
  BufferHandle ebo_id_;
};
} // namespace nv_engine::gl

