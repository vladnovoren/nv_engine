#include "Context/Window.hpp"

using namespace nv_engine::gl;

Window::Window(int width, int height, const std::string& title) {
  glfwInit();
  glfwWindowHint(GLFW_SAMPLES, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  gl_window_ = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
  if (gl_window_ == nullptr) {
    throw std::runtime_error("glfw window create error");
  }
}
