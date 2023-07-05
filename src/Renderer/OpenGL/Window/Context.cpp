#include "Context/Context.hpp"

using namespace nv_engine::gl;

Context::Context(Window& window) : window_(window) {
}

void Context::SwitchTo() {
  glfwMakeContextCurrent(window_.glfw_window_);

  glewExperimental = true;
  if (glewInit() != GLEW_OK) {
    throw std::runtime_error("glew init error");
  }

  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);
}

void Context::Clear(eBufferT buffer) {
  glClear((GLbitfield)buffer);
}

void Context::ClearColor(glm::vec4 color) {
  glClearColor(color.r, color.g, color.b, color.a);
}

void Context::DrawArray(const VertexArray& vao, ePrimitive primitive,
                        size_t first, size_t n_vertices) {
  vao.Bind();
  glDrawArrays((GLenum)primitive, first, n_vertices);
}

void Context::DrawIndexed(const VertexArray& vao, ePrimitive primitive,
                          size_t first, size_t n_vertices) {
  vao.Bind();
  glDrawElements((GLenum)primitive, n_vertices, GL_UNSIGNED_INT,
                 (unsigned int*)first);
}

void Context::PollEvents() {
  glfwPollEvents();
}
