#include "Context/Context.hpp"

using namespace nv_engine::gl;

Context::Context(Window& window) : window_(window) {
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);
}

void Context::SwitchTo() {
  glfwMakeContextCurrent(window_.glfw_window_);

  glewExperimental = true;
  if (glewInit() != GLEW_OK) {
    throw std::runtime_error("glew init error");
  }
}

void Context::Clear(eBufferT buffer) {
  glClear((GLbitfield)buffer);
}

void Context::ClearColor(glm::vec4 color) {
  glClearColor(color.r, color.g, color.b, color.a);
}

void Context::DrawArray(const VertexArray& vao, ePrimitive primitive,
                        size_t first, size_t count) {
  vao.Bind();
  glDrawArrays((GLenum)primitive, first, count);
}

void Context::DrawElements(const VertexArray& vao, ePrimitive primitive,
                           size_t first, size_t count) {
  vao.Bind();
  glDrawElements((GLenum)primitive, count, GL_UNSIGNED_INT, (unsigned int*)first);
}

void Context::PollEvents() {
  glfwPollEvents();
}
