#pragma once

#include "Window.hpp"
#include "Buffers/VertexArray.hpp"

namespace nv_engine::gl {
  class Context {
   public:
    Context(Window& window);

    void SwitchTo();

    void Clear(eBufferT buffer = eBufferT::COLOR | eBufferT::DEPTH);

    void ClearColor(glm::vec4 color);

    void DrawArray(const VertexArray& vao, ePrimitive primitive, size_t first,
                   size_t n_vertices);

    void DrawIndexed(const VertexArray& vao, ePrimitive primitive,
                     size_t first, size_t n_vertices);

    void PollEvents();

   private:
    Window& window_;
  };
} // nv_engine::gl
