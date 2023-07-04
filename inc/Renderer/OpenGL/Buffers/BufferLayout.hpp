#pragma once

#include <string>
#include <vector>
#include "Types.hpp"

namespace nv_engine::gl {
  struct BufferAttribute {
    BufferAttribute(int index, eShaderDataT type,
                    bool normalized = false);

    int index;
    eShaderDataT type;
    unsigned int size;
    size_t offset;
    bool normalized;
  };

  class BufferLayout {
  public:
    BufferLayout() = default;
    BufferLayout(std::vector<BufferAttribute> attributes);

    void SetAttributes(std::vector<BufferAttribute> attributes);
    const std::vector<BufferAttribute>& GetAttributes() const;

    size_t GetStride() const;

  private:
    void CalcOffsetsAndStride();

  private:
    std::vector<BufferAttribute> attributes_;
    size_t stride_;
  };
} // namespace nv_engine
