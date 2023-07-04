#include "Buffers/Types.hpp"
#include "Renderer_OpenGL.hpp"
#include <glm/ext/matrix_transform.hpp>
#include <glm/geometric.hpp>
#include <iostream>
#include "Core/Camera/PerspectiveCamera.hpp"

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
    {{-10, 0, 0}, {1, 0, 0}},
    {{0, 10, 0}, {0, 1, 0}},
    {{10, 0, 0}, {0, 0, 1}}
  };

  std::vector<unsigned int> indices{
    0, 2, 1
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

  PerspectiveCamera camera;
  camera.transform.position = glm::vec3(0, 0, 100.f);
  //camera.transform.Rotate(glm::radians(180.0f), kUp);
  auto forward = camera.transform.CalculateForward();

  std::cout << forward.x << ' ' << forward.y << ' ' << forward.z << '\n';;

  float ds = 1;

  while (!window.ShouldClose() && !window.IsKeyDown(gl::eKey::ESCAPE)) {
    if (window.IsKeyDown(gl::eKey::W)) {
      camera.transform.position += camera.transform.CalculateForward() * ds;
    }
    if (window.IsKeyDown(gl::eKey::S)) {
      camera.transform.position -= camera.transform.CalculateForward() * ds;
    }
    if (window.IsKeyDown(gl::eKey::A)) {
      camera.transform.position -= camera.transform.CalculateRight() * ds;
    }
    if (window.IsKeyDown(gl::eKey::D)) {
      camera.transform.position += camera.transform.CalculateRight() * ds;
    }

    glm::mat4 mvp = camera.CalculatePerspectiveMatrix() *
                    camera.CalculateViewMatrix();

    program.SetUniform("mvp", mvp);

    context.PollEvents();
    context.Clear();
    context.DrawIndexed(vao, gl::ePrimitive::TRIANGLES, 0, vertices.size());
    window.SwapBuffers();
  }

  return 0;
}
