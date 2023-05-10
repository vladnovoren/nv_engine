#pragma once

namespace nv_engine {
  class ABindable {
   public:
    virtual ~ABindable() = 0;

   public:
    virtual void Bind() const = 0;
    virtual void Unbind() const = 0;
  };
}
