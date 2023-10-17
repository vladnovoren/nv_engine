#pragma once

#include <string>
#include <vector>
#include "Types.hpp"

namespace nv_engine::gl {
struct BufferAttribute {
  BufferAttribute(int index, eShaderDataT type, bool normalized = false);

  int index;
  eShaderDataT type;
  unsigned int size;
  size_t offset;
  bool normalized;
};

class BufferLayout {
 public:
  BufferLayout() = default;
  explicit BufferLayout(std::vector<BufferAttribute> attributes);

  void SetAttributes(std::vector<BufferAttribute> attributes);
  [[nodiscard]] const std::vector<BufferAttribute>& GetAttributes() const;

  [[nodiscard]] size_t GetStride() const;

 private:
  void CalcOffsetsAndStride();

 private:
  std::vector<BufferAttribute> attributes_;
  size_t stride_{};
};
}
