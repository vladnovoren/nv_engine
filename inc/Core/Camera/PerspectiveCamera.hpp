#pragma once

#include <glm/glm.hpp>
#include "Transform.hpp"

namespace nv_engine {
  class PerspectiveCamera {
   public:
    float fov;
    float aspect;
    float near;
    float far;

    Transform transform;

   public:
    PerspectiveCamera(float fov = glm::radians(60.0f), float aspect = 4.f/3.f,
        float near = 0.1f, float far = 1000.f,
        Transform transform = Transform());

    glm::mat4 CalculateViewMatrix() const;
    glm::mat4 CalculatePerspectiveMatrix() const;
  };
} // namespace nv_engine
