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

void VertexBuffer::SetLayout(BufferLayout layout) {
  layout_ = std::move(layout);
}

const BufferLayout& VertexBuffer::GetLayout() const {
  return layout_;
}
