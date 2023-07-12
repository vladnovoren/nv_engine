#include "Buffers/IndexBuffer.hpp"

using namespace nv_engine::gl;

IndexBuffer::IndexBuffer() {
  glCreateBuffers(1, &ebo_id_);
}

IndexBuffer::~IndexBuffer() {
  glDeleteBuffers(1, &ebo_id_);
}

void IndexBuffer::Bind() const {
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo_id_);
}

void IndexBuffer::Unbind() const {
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

