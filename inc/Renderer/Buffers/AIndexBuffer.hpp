#pragma once

#include <cstddef>
#include "ABuffer.hpp"

namespace nv_engine {
class AIndexBuffer : public ABuffer {
public:
  virtual ~AIndexBuffer() override;
};
}