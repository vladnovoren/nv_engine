#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace nv_engine::gl {
  class IndexBuffer {
   public:
    IndexBuffer();
    ~IndexBuffer();

    void BufferData(const unsigned int* data, size_t size);

    void Bind() const;
    void Unbind() const;

   protected:
    unsigned int ebo_id_;
  };
}
