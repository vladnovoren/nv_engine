#include "Buffers/Types.hpp"
#include "Renderer_OpenGL.hpp"
#include <iostream>

struct Vertex {
  glm::vec3 pos;
  glm::vec3 color;
};

using namespace nv_engine;

int main() {
  gl::Window window(800, 600, "TestVAO");
  gl::Context context(window);
  context.SwitchTo();

  std::vector<Vertex> vertices{
    {{-1, 0, 0}, {1, 0, 0}},
    {{-0.5, 0.5, 0}, {0, 1, 0}},
    {{0, 0, 0}, {0, 0, 1}},

    {{0, 0, 0}, {1, 0, 0}},
    {{0.5, 0.5, 0}, {0, 1, 0}},
    {{1, 0, 0}, {0, 0, 1}}
  };

  std::vector<unsigned int> indices{
    0, 2, 1,

    3, 5, 4
  };

  gl::Program program("../src/Tests/Renderer/TestVAO/Vert.vert",
                      "../src/Tests/Renderer/TestVAO/Frag.frag");
  program.Use();

  context.ClearColor(glm::vec4(0, 0, 0, 1));

  gl::VertexBuffer vbo;
  vbo.SetLayout(gl::BufferLayout({
        gl::BufferAttribute(program.GetAttribLocation("in_position"),
                            gl::eShaderDataT::FLOAT3),
        gl::BufferAttribute(program.GetAttribLocation("in_color"),
                            gl::eShaderDataT::FLOAT3)}));
  vbo.BufferData(vertices);

  gl::IndexBuffer ebo;
  ebo.BufferData(indices);

  gl::VertexArray vao;
  vao.AddVertexBuffer(vbo);
  vao.SetIndexBuffer(ebo);

  while (!window.ShouldClose() && !window.IsKeyDown(gl::eKey::ESCAPE)) {
    context.PollEvents();
    context.Clear();
    context.DrawIndexed(vao, gl::ePrimitive::TRIANGLES, 0, vertices.size());
    window.SwapBuffers();
  }

  return 0;
}
