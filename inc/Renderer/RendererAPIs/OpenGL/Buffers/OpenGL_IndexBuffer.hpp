#pragma once

#include "AIndexBuffer.hpp"
#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace nv_engine {
class OpenGL_IndexBuffer : public AIndexBuffer {
 public:
  OpenGL_IndexBuffer();
  ~OpenGL_IndexBuffer() override;

  void BufferData(const void* data, size_t size) override;

  void Bind() const override;
  void Unbind() const override;

 protected:
  unsigned int ebo_id_;
};
}
