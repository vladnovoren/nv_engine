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
    {{-1.0f, -1.0f, -1.0f}, {}}, 
    {{-1.0f, -1.0f,  1.0f}, {}},
    {{-1.0f,  1.0f,  1.0f}, {}},
    {{ 1.0f,  1.0f, -1.0f}, {}},
    {{-1.0f, -1.0f, -1.0f}, {}},
    {{-1.0f,  1.0f, -1.0f}, {}},
    {{ 1.0f, -1.0f,  1.0f}, {}},
    {{-1.0f, -1.0f, -1.0f}, {}},
    {{ 1.0f, -1.0f, -1.0f}, {}},
    {{ 1.0f,  1.0f, -1.0f}, {}},
    {{ 1.0f, -1.0f, -1.0f}, {}},
    {{-1.0f, -1.0f, -1.0f}, {}},
    {{-1.0f, -1.0f, -1.0f}, {}},
    {{-1.0f,  1.0f,  1.0f}, {}},
    {{-1.0f,  1.0f, -1.0f}, {}},
    {{ 1.0f, -1.0f,  1.0f}, {}},
    {{-1.0f, -1.0f,  1.0f}, {}},
    {{-1.0f, -1.0f, -1.0f}, {}},
    {{-1.0f,  1.0f,  1.0f}, {}},
    {{-1.0f, -1.0f,  1.0f}, {}},
    {{ 1.0f, -1.0f,  1.0f}, {}},
    {{ 1.0f,  1.0f,  1.0f}, {}},
    {{ 1.0f, -1.0f, -1.0f}, {}},
    {{ 1.0f,  1.0f, -1.0f}, {}},
    {{ 1.0f, -1.0f, -1.0f}, {}},
    {{ 1.0f,  1.0f,  1.0f}, {}},
    {{ 1.0f, -1.0f,  1.0f}, {}},
    {{ 1.0f,  1.0f,  1.0f}, {}},
    {{ 1.0f,  1.0f, -1.0f}, {}},
    {{-1.0f,  1.0f, -1.0f}, {}},
    {{ 1.0f,  1.0f,  1.0f}, {}},
    {{-1.0f,  1.0f, -1.0f}, {}},
    {{-1.0f,  1.0f,  1.0f}, {}},
    {{ 1.0f,  1.0f,  1.0f}, {}},
    {{-1.0f,  1.0f,  1.0f}, {}},
    {{ 1.0f, -1.0f,  1.0f}, {}}
  };

  for (auto& v : vertices) {
    v.color.r = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
    v.color.g = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
    v.color.b = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
  }

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

/*  gl::IndexBuffer ebo;*/
  /*ebo.BufferData(indices);*/

  gl::VertexArray vao;
  vao.AddVertexBuffer(vbo);
  //vao.SetIndexBuffer(ebo);

  PerspectiveCamera camera;
  camera.transform.position = glm::vec3(0, 0, 100.f);

  float ds = 0.5;
  float dphi = 0.012;

/*  glEnable(GL_DEPTH_TEST);*/
  /*glDepthFunc(GL_LESS);*/

  glm::mat4 model = glm::scale(glm::identity<glm::mat4>(), glm::vec3(10));

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

    if (window.IsKeyDown(gl::eKey::LEFT)) {
      camera.transform.Rotate(dphi, camera.transform.CalculateUp());
    }
    if (window.IsKeyDown(gl::eKey::RIGHT)) {
      camera.transform.Rotate(-dphi, camera.transform.CalculateUp());
    }
    if (window.IsKeyDown(gl::eKey::UP)) {
      camera.transform.Rotate(dphi, camera.transform.CalculateRight());
    }
    if (window.IsKeyDown(gl::eKey::DOWN)) {
      camera.transform.Rotate(-dphi, camera.transform.CalculateRight());
    }

    glm::mat4 mvp = camera.CalculatePerspectiveMatrix() *
                    camera.CalculateViewMatrix() * model;

    program.SetUniform("mvp", mvp);

    context.PollEvents();
    context.Clear();
    context.DrawArray(vao, gl::ePrimitive::TRIANGLES, 0, vertices.size());
    window.SwapBuffers();
  }

  return 0;
}
