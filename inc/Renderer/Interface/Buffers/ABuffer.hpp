#pragma once

#include <cstddef>
#include "ABindable.hpp"

namespace nv_engine {
  class ABuffer : public ABindable {
   public:
    virtual ~ABuffer() = 0;

    virtual void BufferData(const void* data, size_t size) = 0;
  };
} // namespace nv_engine