#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>
#include <stdexcept>
#include "Input.hpp"

namespace nv_engine::gl {
class Context;

class Window {
 public:
  Window(int width, int height, const std::string& title);

  void SwapBuffers();

  bool ShouldClose();

  bool IsKeyDown(eKey key);

  bool IsMouseButtonDown(eMouseButton mouse_button);

 private:
  GLFWwindow* glfw_window_ = nullptr;

  friend class Context;
};
} // namespace nv_engine::gl
