#include "Buffers/Types.hpp"
#include "Renderer_OpenGL.hpp"
#include <glm/ext/matrix_transform.hpp>
#include <glm/geometric.hpp>
#include <iostream>
#include "Core/Camera/PerspectiveCamera.hpp"
#include "Textures/Texture2D.hpp"

using namespace nv_engine;

int main() {
  gl::Window window(800, 600, "TestVAO");
  gl::Context context(window);
  context.SwitchTo();

  std::vector<glm::vec3> positions{
    {-1.0f, -1.0f, -1.0f},
    {-1.0f, -1.0f,  1.0f},
    {-1.0f,  1.0f,  1.0f},
    { 1.0f,  1.0f, -1.0f},
    {-1.0f, -1.0f, -1.0f},
    {-1.0f,  1.0f, -1.0f},
    { 1.0f, -1.0f,  1.0f},
    {-1.0f, -1.0f, -1.0f},
    { 1.0f, -1.0f, -1.0f},
    { 1.0f,  1.0f, -1.0f},
    { 1.0f, -1.0f, -1.0f},
    {-1.0f, -1.0f, -1.0f},
    {-1.0f, -1.0f, -1.0f},
    {-1.0f,  1.0f,  1.0f},
    {-1.0f,  1.0f, -1.0f},
    { 1.0f, -1.0f,  1.0f},
    {-1.0f, -1.0f,  1.0f},
    {-1.0f, -1.0f, -1.0f},
    {-1.0f,  1.0f,  1.0f},
    {-1.0f, -1.0f,  1.0f},
    { 1.0f, -1.0f,  1.0f},
    { 1.0f,  1.0f,  1.0f},
    { 1.0f, -1.0f, -1.0f},
    { 1.0f,  1.0f, -1.0f},
    { 1.0f, -1.0f, -1.0f},
    { 1.0f,  1.0f,  1.0f},
    { 1.0f, -1.0f,  1.0f},
    { 1.0f,  1.0f,  1.0f},
    { 1.0f,  1.0f, -1.0f},
    {-1.0f,  1.0f, -1.0f},
    { 1.0f,  1.0f,  1.0f},
    {-1.0f,  1.0f, -1.0f},
    {-1.0f,  1.0f,  1.0f},
    { 1.0f,  1.0f,  1.0f},
    {-1.0f,  1.0f,  1.0f},
    { 1.0f, -1.0f,  1.0f}
  };

  std::vector<glm::vec2> textures_uv = {
    {0.000059f, 1.0f - 0.000004f},
    {0.000103f, 1.0f - 0.336048f},
    {0.335973f, 1.0f - 0.335903f},
    {1.000023f, 1.0f - 0.000013f},
    {0.667979f, 1.0f - 0.335851f},
    {0.999958f, 1.0f - 0.336064f},
    {0.667979f, 1.0f - 0.335851f},
    {0.336024f, 1.0f - 0.671877f},
    {0.667969f, 1.0f - 0.671889f},
    {1.000023f, 1.0f - 0.000013f},
    {0.668104f, 1.0f - 0.000013f},
    {0.667979f, 1.0f - 0.335851f},
    {0.000059f, 1.0f - 0.000004f},
    {0.335973f, 1.0f - 0.335903f},
    {0.336098f, 1.0f - 0.000071f},
    {0.667979f, 1.0f - 0.335851f},
    {0.335973f, 1.0f - 0.335903f},
    {0.336024f, 1.0f - 0.671877f},
    {1.000004f, 1.0f - 0.671847f},
    {0.999958f, 1.0f - 0.336064f},
    {0.667979f, 1.0f - 0.335851f},
    {0.668104f, 1.0f - 0.000013f},
    {0.335973f, 1.0f - 0.335903f},
    {0.667979f, 1.0f - 0.335851f},
    {0.335973f, 1.0f - 0.335903f},
    {0.668104f, 1.0f - 0.000013f},
    {0.336098f, 1.0f - 0.000071f},
    {0.000103f, 1.0f - 0.336048f},
    {0.000004f, 1.0f - 0.671870f},
    {0.336024f, 1.0f - 0.671877f},
    {0.000103f, 1.0f - 0.336048f},
    {0.336024f, 1.0f - 0.671877f},
    {0.335973f, 1.0f - 0.335903f},
    {0.667969f, 1.0f - 0.671889f},
    {1.000004f, 1.0f - 0.671847f},
    {0.667979f, 1.0f - 0.335851f}
  };

  gl::Program program("../src/Tests/Renderer/TestTextures/Vert.vert",
                      "../src/Tests/Renderer/TestTextures/Frag.frag");
  program.Use();

  context.ClearColor(glm::vec4(0, 0, 0, 1));

  gl::VertexBuffer vbo_positions;
  vbo_positions.SetLayout(gl::BufferLayout({
        gl::BufferAttribute(program.GetAttribLocation("in_position"),
                            gl::eShaderDataT::FLOAT3)})
  );
  vbo_positions.BufferData(positions);

  gl::VertexBuffer vbo_textures_uv;
  vbo_textures_uv.SetLayout(gl::BufferLayout({
            gl::BufferAttribute(program.GetAttribLocation("in_uv"),
                                gl::eShaderDataT::FLOAT2)})
  );
  vbo_textures_uv.BufferData(textures_uv);

  gl::VertexArray vao;
  vao.AddVertexBuffer(vbo_positions);
  vao.AddVertexBuffer(vbo_textures_uv);

  gl::Texture2D texture("../src/Tests/Renderer/TestTextures/uvtemplate.bmp",
                        gl::TextureType::NONE);
  program.SetUniform(texture.GetSamplerName(), 0);
  texture.Bind(0);

  PerspectiveCamera camera;
  camera.transform.position = glm::vec3(0, 0, 100.f);

  float ds = 0.5;
  float dphi = 0.012;

  glm::mat4 model = glm::scale(glm::identity<glm::mat4>(), glm::vec3(10));

  while (!window.ShouldClose() && !window.IsKeyDown(gl::eKey::ESCAPE)) {
    context.Clear();
    context.PollEvents();

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
      camera.transform.Rotate(dphi, kUp);
    }
    if (window.IsKeyDown(gl::eKey::RIGHT)) {
      camera.transform.Rotate(-dphi, kUp);
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

    context.DrawArray(vao, gl::ePrimitive::TRIANGLES, 0, positions.size());
    window.SwapBuffers();
  }

  return 0;
}
