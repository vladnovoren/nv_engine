#include "Buffers/BufferLayout.hpp"

using namespace nv_engine::gl;

BufferAttribute::BufferAttribute(int in_index, eShaderDataT in_type,
                                 bool in_normalized)
    : index(in_index), type(in_type),
      size(GetShaderDataTypeSize(in_type)), offset(0),
      normalized(in_normalized) {}

BufferLayout::BufferLayout(std::vector<BufferAttribute> attributes) {
  SetAttributes(std::move(attributes));
}

void BufferLayout::SetAttributes(std::vector<BufferAttribute> attributes) {
  attributes_ = std::move(attributes);
  CalcOffsetsAndStride();
}

const std::vector<BufferAttribute>& BufferLayout::GetAttributes() const {
  return attributes_;
}

size_t BufferLayout::GetStride() const {
  return stride_;
}

void BufferLayout::CalcOffsetsAndStride() {
  size_t offset = 0;
  for (size_t attr_num = 0; attr_num < attributes_.size(); ++attr_num) {
    attributes_[attr_num].offset = offset;
    offset += attributes_[attr_num].size;
  }
  stride_ = offset;
}
