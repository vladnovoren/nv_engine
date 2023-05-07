#pragma once

#include "AVertexBuffer.hpp"
#include "AIndexBuffer.hpp"

namespace nv_engine {
class AVertexArray : public ABindable {
 public:
  virtual ~AVertexArray() = 0;

  virtual void AddVertexBuffer(const AVertexBuffer& buffer) = 0;
  virtual void AddIndexBuffer(const AIndexBuffer& buffer) = 0;
};
} // namespace nv_engine