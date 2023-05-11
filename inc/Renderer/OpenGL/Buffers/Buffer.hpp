#pragma once

#include <cstddef>
#include "Bindable.hpp"

namespace nv_engine::gl {
  class Buffer : public Bindable {
   public:
    virtual ~Buffer() = 0;

    virtual void BufferData(const void* data, size_t size) = 0;
  };
} // namespace nv_engine
