#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace nv_engine::gl {
  enum class eShaderDataT {
    BOOL,
    FLOAT,
    FLOAT2,
    FLOAT3,
    FLOAT4,
    INT,
    INT2,
    INT3,
    INT4,
    MAT3,
    MAT4
  };

  [[maybe_unused]] static unsigned int GetShaderDataTypeSize(eShaderDataT type) {
    switch (type) {
      case eShaderDataT::BOOL:
        return 1;
      case eShaderDataT::FLOAT:
        return 4;
      case eShaderDataT::FLOAT2:
        return 2 * 4;
      case eShaderDataT::FLOAT3:
        return 3 * 4;
      case eShaderDataT::FLOAT4:
        return 4 * 4;
      case eShaderDataT::INT:
        return 4;
      case eShaderDataT::INT2:
        return 2 * 4;
      case eShaderDataT::INT3:
        return 3 * 4;
      case eShaderDataT::INT4:
        return 4 * 4;
      case eShaderDataT::MAT3:
        return 3 * 3 * 4;
      case eShaderDataT::MAT4:
        return 4 * 4 * 4;
    }

    return 0;
  }

  [[maybe_unused]] static unsigned int GetShaderDataCount(eShaderDataT type) {
    switch (type) {
      case eShaderDataT::BOOL:
        return 1;
      case eShaderDataT::FLOAT:
        return 1;
      case eShaderDataT::FLOAT2:
        return 2;
      case eShaderDataT::FLOAT3:
        return 3;
      case eShaderDataT::FLOAT4:
        return 4;
      case eShaderDataT::INT:
        return 1;
      case eShaderDataT::INT2:
        return 2;
      case eShaderDataT::INT3:
        return 3;
      case eShaderDataT::INT4:
        return 4;
      case eShaderDataT::MAT3:
        return 3;
      case eShaderDataT::MAT4:
        return 4;
    }

    return 0;
  }

  enum ePrimitive {
    TRIANGLES = GL_TRIANGLES
  };

  [[maybe_unused]] static unsigned int GetShaderDataAtomicType(
      eShaderDataT type) {
    switch (type) {
      case eShaderDataT::BOOL:
        return GL_BOOL;
      case eShaderDataT::FLOAT:
      case eShaderDataT::FLOAT2:
      case eShaderDataT::FLOAT3:
      case eShaderDataT::FLOAT4:
        return GL_FLOAT;
      case eShaderDataT::INT:
      case eShaderDataT::INT2:
      case eShaderDataT::INT3:
      case eShaderDataT::INT4:
        return GL_INT;
      case eShaderDataT::MAT3:
      case eShaderDataT::MAT4:
        return GL_FLOAT;
    }

    return 0;
  }

  enum eBufferT : GLbitfield {
    COLOR = GL_COLOR_BUFFER_BIT,
    DEPTH = GL_DEPTH_BUFFER_BIT,
    STENCIL = GL_STENCIL_BUFFER_BIT
  };

  inline eBufferT operator|(eBufferT lhs, eBufferT rhs) {
    return (eBufferT)((int)lhs | (int)rhs);
  }

} // namespace nv_engine::gl
