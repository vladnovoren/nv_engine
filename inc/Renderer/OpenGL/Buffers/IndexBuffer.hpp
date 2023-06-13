#pragma once

#include "Bindable.hpp"
#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace nv_engine::gl {
  class IndexBuffer : Bindable {
   public:
    IndexBuffer();
    ~IndexBuffer();

    void BufferData(const unsigned int* data, size_t size);

    void Bind() const override;
    void Unbind() const override;

   protected:
    unsigned int ebo_id_;
  };
}
