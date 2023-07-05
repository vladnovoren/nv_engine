#include "Core/Transform.hpp"
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/quaternion_trigonometric.hpp>

using namespace nv_engine;

Transform::Transform() : scale(1.0), rotation(glm::angleAxis(0.0f, kForward)),
  position(0.0f) {
}

void Transform::Scale(const glm::vec3& add_scale) {
  scale *= add_scale;
}

void Transform::Rotate(float angle, const glm::vec3& axis) {
  rotation = glm::angleAxis(angle, axis) * rotation;
}

void Transform::Translate(const glm::vec3& delta_pos) {
  position += delta_pos;
}

glm::vec3 Transform::CalculateForward() const {
  return CalculateRotationMatrix() * glm::vec4(kForward, 1.0f);
}

glm::vec3 Transform::CalculateUp() const {
  return CalculateRotationMatrix() * glm::vec4(kUp, 1.0f);
}

glm::vec3 Transform::CalculateRight() const {
  return CalculateRotationMatrix() * glm::vec4(kRight, 1.0f);
}

glm::mat4 Transform::CalculateMatrix() const {
  return CalculateTranslationMatrix() *
         CalculateRotationMatrix() *
         CalculateScaleMatrix();
}

glm::mat4 Transform::CalculateInverseMatrix() const {
  return glm::scale(glm::identity<glm::mat4>(),
                    glm::vec3{1 / scale.x, 1 / scale.y, 1 / scale.z}) *
                    glm::transpose(CalculateRotationMatrix()) *
                    glm::translate(glm::identity<glm::mat4>(), -position);
}

glm::mat4 Transform::CalculateScaleMatrix() const {
  return glm::scale(glm::identity<glm::mat4>(), scale);
}

glm::mat4 Transform::CalculateRotationMatrix() const {
  return glm::mat4_cast(rotation);
}

glm::mat4 Transform::CalculateTranslationMatrix() const {
  return glm::translate(glm::identity<glm::mat4>(), position);
}
