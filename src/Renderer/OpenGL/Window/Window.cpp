#include "Context/Window.hpp"

using namespace nv_engine::gl;

Window::Window(int width, int height, const std::string& title) {
  glfwInit();
  glfwWindowHint(GLFW_SAMPLES, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  glfw_window_ = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
  if (glfw_window_ == nullptr) {
    throw std::runtime_error("glfw window create error");
  }
}

void Window::SwapBuffers() {
  glfwSwapBuffers(glfw_window_);
}

bool Window::ShouldClose() {
  return glfwWindowShouldClose(glfw_window_);
}

bool Window::IsKeyDown(eKey key) {
  int state = glfwGetKey(glfw_window_, (int)key);
  return state == GLFW_PRESS;
}
