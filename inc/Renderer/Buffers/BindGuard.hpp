#pragma once

#include "Guard.hpp"
#include "AVertexArray.hpp"
#include "AVertexBuffer.hpp"

namespace nv_engine {
  using VAO_BindGuard = tools::Guard<AVertexArray,
                                     &AVertexArray::Bind,
                                     &AVertexArray::Unbind>;

  using VBO_BindGuard = tools::Guard<AVertexBuffer,
                                     &AVertexBuffer::Bind,
                                     &AVertexBuffer::Unbind>;
}