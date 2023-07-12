#include "Buffers/VertexArray.hpp"

using namespace nv_engine::gl;

VertexArray::VertexArray() {
  glCreateVertexArrays(1, &vao_id_);
}

VertexArray::~VertexArray() {
  glDeleteVertexArrays(1, &vao_id_);
}

void VertexArray::Bind() const {
  glBindVertexArray(vao_id_);
}

void VertexArray::Unbind() const {
  glBindVertexArray(0);
}

void VertexArray::AddVertexBuffer(const VertexBuffer& buffer) {
  Bind();
  buffer.Bind();

  const auto &layout = buffer.GetLayout();
  const auto &attributes = layout.GetAttributes();
  for (const auto &attribute : attributes) {
    BindAttribute(attribute, layout.GetStride());
  }
}

void VertexArray::SetIndexBuffer(const IndexBuffer& buffer) {
  Bind();
  buffer.Bind();
}

void VertexArray::BindAttribute(const BufferAttribute& attribute,
                                size_t stride) {
  switch (attribute.type) {
    case eShaderDataT::FLOAT:
    case eShaderDataT::FLOAT2:
    case eShaderDataT::FLOAT3:
    case eShaderDataT::FLOAT4:
      BindFloatAttribute(attribute, stride);
      break;
    case eShaderDataT::BOOL:
    case eShaderDataT::INT:
    case eShaderDataT::INT2:
    case eShaderDataT::INT3:
    case eShaderDataT::INT4:
      BindIntAttribute(attribute, stride);
      break;
    default:
      throw std::runtime_error("unsupported shader data type for attribute");
      break;
  }
}

void VertexArray::BindFloatAttribute(const BufferAttribute& attribute,
                                     size_t stride) {
  glVertexAttribPointer(attribute.index, GetShaderDataCount(attribute.type),
                        GetShaderDataAtomicType(attribute.type),
                        attribute.normalized, stride, (void*)attribute.offset);
  glEnableVertexAttribArray(attribute.index);
}

void VertexArray::BindIntAttribute(const BufferAttribute& attribute,
                                   size_t stride) {
  glVertexAttribIPointer(attribute.index, GetShaderDataCount(attribute.type),
                         GetShaderDataAtomicType(attribute.type),
                         stride, (uint8_t*)attribute.offset);
  glEnableVertexAttribArray(attribute.index);
}
