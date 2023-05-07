#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Renderer.hpp"

namespace nv_engine {
  class RendererAPI_OpenGL : public Renderer {
   public:
    RendererAPI_OpenGL();
    ~RendererAPI_OpenGL() override;
};
} // namespace nv_engine
