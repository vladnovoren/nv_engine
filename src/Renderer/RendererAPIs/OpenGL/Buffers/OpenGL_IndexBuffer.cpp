#include "Buffers/OpenGL_IndexBuffer.hpp"

using namespace nv_engine;

OpenGL_IndexBuffer::OpenGL_IndexBuffer() {
  glCreateBuffers(1, &ebo_id_);
}

OpenGL_IndexBuffer::~OpenGL_IndexBuffer() {
  glDeleteBuffers(1, &ebo_id_);
}

void OpenGL_IndexBuffer::Bind() const {
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo_id_);
}

void OpenGL_IndexBuffer::Unbind() const {
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void OpenGL_IndexBuffer::BufferData(const void* data, size_t size) {
  /*
    GL_ELEMENT_ARRAY_BUFFER is not valid without an active bound VAO
    GL_ARRAY_BUFFER allows to bind and buffer data regardless of VAO state
    then you can interpret it as GL_ELEMENT_ARRAY_BUFFER when some VAO will be bound
  **/
  glBindBuffer(GL_ARRAY_BUFFER, ebo_id_);
  glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}
