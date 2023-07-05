#pragma once

#include <glm/ext/matrix_transform.hpp>
#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>

namespace nv_engine {
  static constexpr glm::vec3 kUp{0.0f, 1.0f, 0.0f};
  static constexpr glm::vec3 kRight{1.0f, 0.0f, 0.0f};
  static constexpr glm::vec3 kForward{0.0f, 0.0f, -1.0f};

  struct Transform {
    Transform();

    void Scale(const glm::vec3& add_scale);
    void Rotate(float angle, const glm::vec3& axis);
    void Translate(const glm::vec3& delta_pos);

    glm::vec3 CalculateForward() const;
    glm::vec3 CalculateUp() const;
    glm::vec3 CalculateRight() const;

    glm::mat4 CalculateMatrix() const;
    glm::mat4 CalculateInverseMatrix() const;

    glm::mat4 CalculateScaleMatrix() const;
    glm::mat4 CalculateRotationMatrix() const;
    glm::mat4 CalculateTranslationMatrix() const; 

    glm::vec3 scale;
    glm::quat rotation;
    glm::vec3 position;
  };
} // namespace nv_engine
