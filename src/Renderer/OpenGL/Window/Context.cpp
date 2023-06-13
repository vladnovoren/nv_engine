#include "Context/Context.hpp"

using namespace nv_engine::gl;

Context::Context(Window& window) : window_(window) {
}

void Context::SwitchTo() {
  glfwMakeContextCurrent(window_.gl_window_);

  glewExperimental = true;
  if (glewInit() != GLEW_OK) {
    throw std::runtime_error("glew init error");
  }
}

void Context::Clear(eBufferT buffer) {
  glClear(buffer);
}

void Context::ClearColor(glm::vec4 color) {
  glClearColor(color.r, color.g, color.b, color.a);
}

void Context::DrawArray(const VertexArray& vao, ePrimitive primitive,
                        size_t first, size_t count) {
  vao.Bind();
  glDrawArrays(primitive, first, count);
}

void Context::DrawElements(const VertexArray& vao, ePrimitive primitive,
                           size_t first, size_t count) {
  vao.Bind();
  glDrawElements(primitive, count, GL_UNSIGNED_INT, (unsigned int*)first);
}
