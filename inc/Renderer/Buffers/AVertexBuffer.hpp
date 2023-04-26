#pragma once

#include "BufferLayout.hpp"

namespace nv_engine {
class AVertexBuffer {
public:
  virtual ~AVertexBuffer() = 0;

  virtual void Bind() const = 0;
  virtual void Unbind() const = 0;
  virtual void BufferData(const void *data, size_t size) = 0;

  virtual void SetLayout(BufferLayout layout) = 0;
  virtual const BufferLayout& GetLayout() const = 0;

};
} // namespace nv_engine
