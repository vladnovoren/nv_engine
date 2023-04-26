#include "OpenGL_VertexBuffer.hpp"

using namespace nv_engine;

OpenGL_VertexBuffer::OpenGL_VertexBuffer() { glCreateBuffers(1, &vbo_id_); }

OpenGL_VertexBuffer::~OpenGL_VertexBuffer() { glDeleteBuffers(1, &vbo_id_); }

void OpenGL_VertexBuffer::Bind() const {
  glBindBuffer(GL_ARRAY_BUFFER, vbo_id_);
}

void OpenGL_VertexBuffer::Unbind() const {
  glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void OpenGL_VertexBuffer::BufferData(const void *data, size_t size) {
  glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

void OpenGL_VertexBuffer::SetLayout(BufferLayout layout) {
  layout_ = std::move(layout);
}

const BufferLayout& OpenGL_VertexBuffer::GetLayout() const {
  return layout_;
}