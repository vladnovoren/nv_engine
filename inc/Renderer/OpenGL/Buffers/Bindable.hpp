#pragma once

namespace nv_engine::gl {
  class Bindable {
   public:
    virtual ~Bindable() = 0;

   public:
    virtual void Bind() const = 0;
    virtual void Unbind() const = 0;
  };
}
