#pragma once

#include "IndexBuffer.hpp"
#include "VertexBuffer.hpp"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include <stdexcept>
#include "Types.hpp"

namespace nv_engine::gl {
  class VertexArray {
   public:
    VertexArray();
    ~VertexArray();

    void Bind() const;
    void Unbind() const;

    void AddVertexBuffer(const VertexBuffer& buffer);
    void SetIndexBuffer(const IndexBuffer& buffer);

   private:
    void BindAttribute(const BufferAttribute& attribute, size_t index,
                       size_t stride);
    void BindFloatAttribute(const BufferAttribute& attribute, size_t index,
                            size_t stride);
    void BindIntAttribute(const BufferAttribute& attribute, size_t index,
                          size_t stride);

   private:
    unsigned int vao_id_;
  };
} // namespace nv_engine
