#pragma once

#include "AVertexBuffer.hpp"
#include "AIndexBuffer.hpp"
#include <memory>

namespace nv_engine {
class AVertexArray : public ABindable {
 public:
  virtual ~AVertexArray() = 0;

  virtual void AddVertexBuffer(std::shared_ptr<const AVertexBuffer> buffer) = 0;
  virtual void SetIndexBuffer(std::shared_ptr<const AIndexBuffer> buffer) = 0;

  virtual const std::vector<std::shared_ptr<const AVertexBuffer>>&
  GetVertexBuffers() const = 0;

  virtual std::shared_ptr<const AIndexBuffer> GetIndexBuffer() const = 0;
};
} // namespace nv_engine
