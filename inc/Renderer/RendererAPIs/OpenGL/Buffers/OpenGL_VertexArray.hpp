#pragma once

#include "AVertexArray.hpp"
#include "AIndexBuffer.hpp"
#include "BufferLayout.hpp"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include <stdexcept>

namespace nv_engine {
  [[maybe_unused]] static unsigned int OpenGL_GetShaderDataAtomicType(
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

  class VertexArray_OpenGL : public AVertexArray {
  public:
    VertexArray_OpenGL();
    ~VertexArray_OpenGL() override;

    void Bind() const override;
    void Unbind() const override;

    void AddVertexBuffer(const AVertexBuffer& buffer) override;
    void AddIndexBuffer(const AIndexBuffer& buffer) override;

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
