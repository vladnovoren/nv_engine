#include "Buffers/OpenGL_VertexArray.hpp"

using namespace nv_engine;

VertexArray_OpenGL::VertexArray_OpenGL() {
  glCreateVertexArrays(1, &vao_id_);
}

VertexArray_OpenGL::~VertexArray_OpenGL() {
  glDeleteVertexArrays(1, &vao_id_);
}

void VertexArray_OpenGL::Bind() const {
  glBindVertexArray(vao_id_);
}

void VertexArray_OpenGL::Unbind() const {
  glBindVertexArray(0);
}

void VertexArray_OpenGL::AddVertexBuffer(
    std::shared_ptr<const AVertexBuffer> buffer) {
  Bind();
  buffer->Bind();

  const auto &layout = buffer->GetLayout();
  const auto &attributes = layout.GetAttributes();
  size_t index = 0;
  for (const auto &attribute : attributes) {
    BindAttribute(attribute, index, layout.GetStride());
    ++index;
  }

  vertex_buffers_.push_back(buffer);
}

void VertexArray_OpenGL::SetIndexBuffer(
    std::shared_ptr<const AIndexBuffer> buffer) {
  Bind();
  buffer->Bind();

  index_buffer_ = buffer;
}

const std::vector<std::shared_ptr<const AVertexBuffer>>&
VertexArray_OpenGL::GetVertexBuffers() const {
  return vertex_buffers_;
}

std::shared_ptr<const AIndexBuffer> VertexArray_OpenGL::GetIndexBuffer() const {
  return index_buffer_;
}

void VertexArray_OpenGL::BindAttribute(const BufferAttribute &attribute,
                                       size_t index,
                                       size_t stride) {
  switch (attribute.type) {
    case eShaderDataT::FLOAT:
    case eShaderDataT::FLOAT2:
    case eShaderDataT::FLOAT3:
    case eShaderDataT::FLOAT4:
      BindFloatAttribute(attribute, index, stride);
      break;
    case eShaderDataT::BOOL:
    case eShaderDataT::INT:
    case eShaderDataT::INT2:
    case eShaderDataT::INT3:
    case eShaderDataT::INT4:
      BindIntAttribute(attribute, index, stride);
      break;
    default:
      throw std::runtime_error("unsupported shader data type for attribute");
      break;
  }
}

void VertexArray_OpenGL::BindFloatAttribute(const BufferAttribute& attribute,
                                            size_t index,
                                            size_t stride) {
  glEnableVertexAttribArray(index);
  glVertexAttribPointer(index, GetShaderDataCount(attribute.type),
                        OpenGL_GetShaderDataAtomicType(attribute.type),
                        attribute.normalized, stride, (void*)attribute.offset);
}

void VertexArray_OpenGL::BindIntAttribute(const BufferAttribute& attribute,
                                          size_t index,
                                          size_t stride) {
  glEnableVertexAttribArray(index);
  glVertexAttribIPointer(index, GetShaderDataCount(attribute.type),
                         OpenGL_GetShaderDataAtomicType(attribute.type),
                         stride, (uint8_t*)attribute.offset);
}
