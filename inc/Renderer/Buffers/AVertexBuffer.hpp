#pragma once

#include "BufferLayout.hpp"
#include "ABuffer.hpp"

namespace nv_engine {
class AVertexBuffer : public ABuffer {
public:
  virtual ~AVertexBuffer() = 0;

  virtual void SetLayout(BufferLayout layout) = 0;
  virtual const BufferLayout& GetLayout() const = 0;

};
} // namespace nv_engine
