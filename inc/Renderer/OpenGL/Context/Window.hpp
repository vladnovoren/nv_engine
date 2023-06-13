#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>
#include <stdexcept>

namespace nv_engine::gl {
  class Context;

  class Window {
   public:
    Window(int width, int height, const std::string& title);

   private:
    GLFWwindow* gl_window_ = nullptr;

    friend class Context;
  };
} // namespace nv_engine::gl
