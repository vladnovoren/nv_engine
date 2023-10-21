#include "Buffers/BufferLayout.hpp"
#include "Renderer_OpenGL.hpp"
#include <iostream>
#include "Core/Camera/PerspectiveCamera.hpp"
#include <chrono>

using namespace nv_engine;

using hr_time = std::chrono::high_resolution_clock;
using ms = std::chrono::milliseconds;
using s = std::chrono::seconds;

struct Vertex {
  glm::vec3 position;
  glm::vec3 normal;
};

int main() {
  gl::Window window(800, 600, "Phong Cube");
  gl::Context context(window);
  context.SwitchTo();

  std::vector<Vertex> vertices{
    {{-0.5f, -0.5f, -0.5f}, {}},
    {{ 0.5f,  0.5f, -0.5f}, {}},
    {{ 0.5f, -0.5f, -0.5f}, {}},
    {{ 0.5f,  0.5f, -0.5f}, {}},
    {{-0.5f, -0.5f, -0.5f}, {}},
    {{-0.5f,  0.5f, -0.5f}, {}},

    {{-0.5f, -0.5f,  0.5f}, {}},
    {{ 0.5f, -0.5f,  0.5f}, {}},
    {{ 0.5f,  0.5f,  0.5f}, {}},
    {{ 0.5f,  0.5f,  0.5f}, {}},
    {{-0.5f,  0.5f,  0.5f}, {}},
    {{-0.5f, -0.5f,  0.5f}, {}},

    {{-0.5f,  0.5f,  0.5f}, {}},
    {{-0.5f,  0.5f, -0.5f}, {}},
    {{-0.5f, -0.5f, -0.5f}, {}},
    {{-0.5f, -0.5f, -0.5f}, {}},
    {{-0.5f, -0.5f,  0.5f}, {}},
    {{-0.5f,  0.5f,  0.5f}, {}},

    {{0.5f,  0.5f,  0.5f}, {}},
    {{0.5f, -0.5f, -0.5f}, {}},
    {{0.5f,  0.5f, -0.5f}, {}},
    {{0.5f, -0.5f, -0.5f}, {}},
    {{0.5f,  0.5f,  0.5f}, {}},
    {{0.5f, -0.5f,  0.5f}, {}},

    {{-0.5f, -0.5f, -0.5f}, {}},
    {{ 0.5f, -0.5f, -0.5f}, {}},
    {{ 0.5f, -0.5f,  0.5f}, {}},
    {{ 0.5f, -0.5f,  0.5f}, {}},
    {{-0.5f, -0.5f,  0.5f}, {}},
    {{-0.5f, -0.5f, -0.5f}, {}},

    {{-0.5f,  0.5f, -0.5f}, {}},
    {{ 0.5f,  0.5f,  0.5f}, {}},
    {{ 0.5f,  0.5f, -0.5f}, {}},
    {{ 0.5f,  0.5f,  0.5f}, {}},
    {{-0.5f,  0.5f, -0.5f}, {}},
    {{-0.5f,  0.5f,  0.5f}, {}},
  };

  for (size_t i = 0; i < vertices.size(); i += 3) {
    auto v1 = vertices[i + 1].position - vertices[i].position;
    auto v2 = vertices[i + 2].position - vertices[i].position;
    auto normal = glm::normalize(glm::cross(v1, v2));
    for (size_t j = i; j < i + 3; ++j) {
      vertices[j].normal = normal;
    }
  }

  gl::Program program("../src/Tests/Renderer/Phong/Mono/phong_mono.vert",
                      "../src/Tests/Renderer/Phong/Mono/phong_mono.frag");
  program.Use();

  gl::VertexBuffer vbo_vertices;
  vbo_vertices.SetLayout(gl::BufferLayout({
      gl::BufferAttribute(program.GetAttribLocation("position"),
                          gl::eShaderDataT::FLOAT3),
      gl::BufferAttribute(program.GetAttribLocation("normal"),
                          gl::eShaderDataT::FLOAT3)
  }));
  vbo_vertices.BufferData(vertices);


  gl::VertexArray vao_cube;
  vao_cube.AddVertexBuffer(vbo_vertices);

  PerspectiveCamera camera;
  camera.transform.position = glm::vec3(0, 0, 100.f);

  float speed = 2.5;
  float ds = 0.5 * speed, dphi = 0.012 * speed;

  glm::mat4 model = glm::scale(glm::identity<glm::mat4>(), glm::vec3(20));

  glm::vec3 light_color = glm::vec3(1, 1, 1);
  glm::vec3 light_position = glm::vec3(20, 20, 40);

  context.ClearColor(glm::vec4(0.0));

  float light_angle = 0.0f;
  auto prev_time(hr_time::now());

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

    glm::mat4 view = camera.CalculateViewMatrix();
    glm::mat4 projection = camera.CalculatePerspectiveMatrix();

    program.SetUniform("model", model);
    program.SetUniform("view", view);
    program.SetUniform("projection", projection);

    auto curr_time(hr_time::now());
    auto dur = curr_time - prev_time;
    light_angle += 0.001 * std::chrono::duration_cast<ms>(dur).count();
    if (light_angle > 2 * M_PI)
      light_angle -= 2 * M_PI;
    prev_time = curr_time;

    glm::mat4 rotateX = glm::rotate(glm::mat4(1), light_angle, glm::vec3(1, 0, 0));
    glm::mat4 rotateY = glm::rotate(glm::mat4(1), light_angle, glm::vec3(0, 1, 0));
    glm::mat4 rotateZ = glm::rotate(glm::mat4(1), light_angle, glm::vec3(0, 0, 1));

    glm::vec3 curr_light_position = rotateZ * rotateY * rotateX * glm::vec4(light_position, 1.0);
    curr_light_position = light_position;

    program.SetUniform("light_color", light_color);
    program.SetUniform("light_position", curr_light_position);

    program.SetUniform("view_position", camera.transform.position);

    context.DrawArray(vao_cube, gl::ePrimitive::TRIANGLES, 0, vertices.size());
    window.SwapBuffers();
  }

  return 0;
}
