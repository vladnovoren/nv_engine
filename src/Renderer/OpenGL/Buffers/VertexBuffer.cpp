#include "Buffers/VertexBuffer.hpp"

using namespace nv_engine::gl;

VertexBuffer::VertexBuffer() {
  glCreateBuffers(1, &vbo_id_);
}

VertexBuffer::~VertexBuffer() {
  glDeleteBuffers(1, &vbo_id_);
}

void VertexBuffer::Bind() const {
  glBindBuffer(GL_ARRAY_BUFFER, vbo_id_);
}

void VertexBuffer::Unbind() const {
  glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VertexBuffer::BufferData(const void *data, size_t size) {
  glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

void VertexBuffer::SetLayout(BufferLayout layout) {
  layout_ = std::move(layout);
}

const BufferLayout& VertexBuffer::GetLayout() const {
  return layout_;
}
