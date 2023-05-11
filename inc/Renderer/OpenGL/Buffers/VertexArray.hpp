#pragma once

#include "IndexBuffer.hpp"
#include "VertexBuffer.hpp"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include <stdexcept>

namespace nv_engine::gl {
  [[maybe_unused]] static unsigned int GetShaderDataAtomicType(
      eShaderDataT type) {
    switch (type) {
      case eShaderDataT::BOOL:
        return GL_BOOL;
      case eShaderDataT::FLOAT:
      case eShaderDataT::FLOAT2:
      case eShaderDataT::FLOAT3:
      case eShaderDataT::FLOAT4:
        return GL_FLOAT;
      case eShaderDataT::INT:
      case eShaderDataT::INT2:
      case eShaderDataT::INT3:
      case eShaderDataT::INT4:
        return GL_INT;
      case eShaderDataT::MAT3:
      case eShaderDataT::MAT4:
        return GL_FLOAT;
    }

    return 0;
  }

  class VertexArray : Bindable {
   public:
    VertexArray();
    ~VertexArray();

    void Bind() const override;
    void Unbind() const override;

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
