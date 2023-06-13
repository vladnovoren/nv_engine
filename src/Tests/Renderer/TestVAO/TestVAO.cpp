#include "Renderer/OpenGL/Renderer_OpenGL.hpp"

struct Vertex {
  glm::vec3 pos;
  glm::vec3 color;
};

using namespace nv_engine;

int main() {
  gl::Window window(800, 600, "TestVAO");
  gl::Context context(window);

  std::vector<Vertex> vertices{
    {{0.5, 0, 0}, {1, 0, 0}},
    {{-0.5, 0, 0}, {0, 1, 0}},
    {{0, 0.5, 0}, {0, 0, 1}}
  };

  gl::VertexBuffer vbo;
  vbo.BufferData(vertices.data(), vertices.size() * sizeof(Vertex));

  gl::VertexArray vao;
  vao.AddVertexBuffer(vbo);

  vao.Bind();

  while (true) {

  }

  return 0;
}
