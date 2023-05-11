#pragma once

#include <string>
#include <vector>

namespace nv_engine::gl {
enum class eShaderDataT {
  BOOL,
  FLOAT,
  FLOAT2,
  FLOAT3,
  FLOAT4,
  INT,
  INT2,
  INT3,
  INT4,
  MAT3,
  MAT4
};

[[maybe_unused]] static unsigned int GetShaderDataTypeSize(eShaderDataT type) {
  switch (type) {
    case eShaderDataT::BOOL:
      return 1;
    case eShaderDataT::FLOAT:
      return 4;
    case eShaderDataT::FLOAT2:
      return 2 * 4;
    case eShaderDataT::FLOAT3:
      return 3 * 4;
    case eShaderDataT::FLOAT4:
      return 4 * 4;
    case eShaderDataT::INT:
      return 4;
    case eShaderDataT::INT2:
      return 2 * 4;
    case eShaderDataT::INT3:
      return 3 * 4;
    case eShaderDataT::INT4:
      return 4 * 4;
    case eShaderDataT::MAT3:
      return 3 * 3 * 4;
    case eShaderDataT::MAT4:
      return 4 * 4 * 4;
  }

  return 0;
}

[[maybe_unused]] static unsigned int GetShaderDataCount(eShaderDataT type) {
  switch (type) {
    case eShaderDataT::BOOL:
      return 1;
    case eShaderDataT::FLOAT:
      return 1;
    case eShaderDataT::FLOAT2:
      return 2;
    case eShaderDataT::FLOAT3:
      return 3;
    case eShaderDataT::FLOAT4:
      return 4;
    case eShaderDataT::INT:
      return 1;
    case eShaderDataT::INT2:
      return 2;
    case eShaderDataT::INT3:
      return 3;
    case eShaderDataT::INT4:
      return 4;
    case eShaderDataT::MAT3:
      return 3;
    case eShaderDataT::MAT4:
      return 4;
  }

  return 0;
}

struct BufferAttribute {
  BufferAttribute(std::string name, eShaderDataT type,
                         bool normalized = false);

  std::string name;
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
