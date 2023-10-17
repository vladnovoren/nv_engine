#pragma once

#include "Renderer_OpenGL.hpp"

struct Vertex {
  glm::vec3 position;
  glm::vec2 texture_uv;
  glm::vec3 normal;
};
