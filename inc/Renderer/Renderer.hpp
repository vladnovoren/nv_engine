#pragma once

namespace nv_engine {
enum class eRendererAPI { OpenGL };

class Renderer {
public:
  Renderer() = default;
  virtual ~Renderer() = default;

  static eRendererAPI GetRendererAPI();

private:
#ifndef RENDERER_API
  static constexpr eRendererAPI renderer_API_ = eRendererAPI::OpenGL;
#else
  static constexpr eRendererAPI renderer_API_ = eRendererAPI::RENDERER_API;
#endif
};
} // namespace nv_engine