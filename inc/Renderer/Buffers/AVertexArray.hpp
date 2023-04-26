#pragma once

#include "AVertexBuffer.hpp"

namespace nv_engine {
class AVertexArray {
public:
  virtual ~AVertexArray() = 0;

  virtual void Bind() const = 0;
  virtual void Unbind() const = 0;

  virtual void AddVertexBuffer(const AVertexBuffer& buffer) = 0;

};
} // namespace nv_engine