#include "Camera/PerspectiveCamera.hpp"

using namespace nv_engine;

PerspectiveCamera::PerspectiveCamera(float fov, float aspect, float near,
    float far, Transform transform) : fov(fov), aspect(aspect),
  near(near), far(far), transform(transform) {
}

glm::mat4 PerspectiveCamera::CalculateViewMatrix() const {
  return transform.CalculateInverseMatrix();
}

glm::mat4 PerspectiveCamera::CalculatePerspectiveMatrix() const {
  return glm::perspective(fov, aspect, near, far);
}
