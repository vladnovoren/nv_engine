#include "OpenGL_RendererAPI.hpp"

using namespace nv_engine;

RendererAPI_OpenGL::RendererAPI_OpenGL() {
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  glEnable(GL_DEPTH_TEST);
  glEnable(GL_LINE_SMOOTH);
}

RendererAPI_OpenGL::~RendererAPI_OpenGL() {}
