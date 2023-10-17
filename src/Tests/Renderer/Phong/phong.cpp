#include "Renderer_OpenGL.hpp"
#include "Core/Camera/PerspectiveCamera.hpp"

using namespace nv_engine;

int main() {
  gl::Window window(800, 600, "Phong Cube");
  gl::Context context(window);
  context.SwitchTo();

  std::vector<glm::vec3> positions{
      {-1.0f, -1.0f, -1.0f}, {-1.0f, -1.0f, 1.0f},  {-1.0f, 1.0f, 1.0f},
      {1.0f, 1.0f, -1.0f},   {-1.0f, -1.0f, -1.0f}, {-1.0f, 1.0f, -1.0f},
      {1.0f, -1.0f, 1.0f},   {-1.0f, -1.0f, -1.0f}, {1.0f, -1.0f, -1.0f},
      {1.0f, 1.0f, -1.0f},   {1.0f, -1.0f, -1.0f},  {-1.0f, -1.0f, -1.0f},
      {-1.0f, -1.0f, -1.0f}, {-1.0f, 1.0f, 1.0f},   {-1.0f, 1.0f, -1.0f},
      {1.0f, -1.0f, 1.0f},   {-1.0f, -1.0f, 1.0f},  {-1.0f, -1.0f, -1.0f},
      {-1.0f, 1.0f, 1.0f},   {-1.0f, -1.0f, 1.0f},  {1.0f, -1.0f, 1.0f},
      {1.0f, 1.0f, 1.0f},    {1.0f, -1.0f, -1.0f},  {1.0f, 1.0f, -1.0f},
      {1.0f, -1.0f, -1.0f},  {1.0f, 1.0f, 1.0f},    {1.0f, -1.0f, 1.0f},
      {1.0f, 1.0f, 1.0f},    {1.0f, 1.0f, -1.0f},   {-1.0f, 1.0f, -1.0f},
      {1.0f, 1.0f, 1.0f},    {-1.0f, 1.0f, -1.0f},  {-1.0f, 1.0f, 1.0f},
      {1.0f, 1.0f, 1.0f},    {-1.0f, 1.0f, 1.0f},   {1.0f, -1.0f, 1.0f}};

  std::vector<glm::vec2> textures_uv = {
      {0.000059f, 1.0f - 0.000004f}, {0.000103f, 1.0f - 0.336048f},
      {0.335973f, 1.0f - 0.335903f}, {1.000023f, 1.0f - 0.000013f},
      {0.667979f, 1.0f - 0.335851f}, {0.999958f, 1.0f - 0.336064f},
      {0.667979f, 1.0f - 0.335851f}, {0.336024f, 1.0f - 0.671877f},
      {0.667969f, 1.0f - 0.671889f}, {1.000023f, 1.0f - 0.000013f},
      {0.668104f, 1.0f - 0.000013f}, {0.667979f, 1.0f - 0.335851f},
      {0.000059f, 1.0f - 0.000004f}, {0.335973f, 1.0f - 0.335903f},
      {0.336098f, 1.0f - 0.000071f}, {0.667979f, 1.0f - 0.335851f},
      {0.335973f, 1.0f - 0.335903f}, {0.336024f, 1.0f - 0.671877f},
      {1.000004f, 1.0f - 0.671847f}, {0.999958f, 1.0f - 0.336064f},
      {0.667979f, 1.0f - 0.335851f}, {0.668104f, 1.0f - 0.000013f},
      {0.335973f, 1.0f - 0.335903f}, {0.667979f, 1.0f - 0.335851f},
      {0.335973f, 1.0f - 0.335903f}, {0.668104f, 1.0f - 0.000013f},
      {0.336098f, 1.0f - 0.000071f}, {0.000103f, 1.0f - 0.336048f},
      {0.000004f, 1.0f - 0.671870f}, {0.336024f, 1.0f - 0.671877f},
      {0.000103f, 1.0f - 0.336048f}, {0.336024f, 1.0f - 0.671877f},
      {0.335973f, 1.0f - 0.335903f}, {0.667969f, 1.0f - 0.671889f},
      {1.000004f, 1.0f - 0.671847f}, {0.667979f, 1.0f - 0.335851f}};

  std::vector<glm::vec3> normals(positions.size());
  for (size_t i = 0; i < normals.size(); i += 3) {
    auto v1 = positions[i + 1] - positions[i];
    auto v2 = positions[i + 2] - positions[i];
    normals[i] = normals[i + 1] = normals[i + 2] =
        glm::normalize(glm::cross(v1, v2));
  }

  gl::Program program("../src/Tests/Renderer/Phong/phong.vert",
                      "../src/Tests/Renderer/Phong/phong.frag");
  program.Use();

  context.ClearColor(glm::vec4(0, 0, 0, 1));

  gl::VertexBuffer vbo_positions;
  vbo_positions.SetLayout(gl::BufferLayout({
      gl::BufferAttribute(program.GetAttribLocation("position"),
                          gl::eShaderDataT::FLOAT3)
  }));
  vbo_positions.BufferData(positions);

  gl::VertexBuffer vbo_textures_uv;
  vbo_textures_uv.SetLayout(gl::BufferLayout({
      gl::BufferAttribute(program.GetAttribLocation("uv"),
                          gl::eShaderDataT::FLOAT2)
  }));
  vbo_textures_uv.BufferData(textures_uv);

  gl::VertexBuffer vbo_normals;
  vbo_normals.SetLayout(gl::BufferLayout({
      gl::BufferAttribute(program.GetAttribLocation("normal"),
                          gl::eShaderDataT::FLOAT3)
  }));
  vbo_normals.BufferData(normals);

  gl::VertexArray vao_cube;
  vao_cube.AddVertexBuffer(vbo_positions);
  vao_cube.AddVertexBuffer(vbo_textures_uv);
  vao_cube.AddVertexBuffer(vbo_normals);

  gl::Texture2D texture("../src/Tests/Renderer/TestTextures/uvtemplate.bmp",
                        gl::TextureType::ALBEDO);
  program.SetUniform(texture.GetSamplerName(), 0);
  texture.Bind(0);

  PerspectiveCamera camera;
  camera.transform.position = glm::vec3(0, 0, 100.f);

  float ds = 0.5;
  float dphi = 0.012;

  glm::mat4 model = glm::scale(glm::identity<glm::mat4>(), glm::vec3(10));

  glm::vec3 light_color = glm::vec3(0.1, 0.1, 0.9);
  glm::vec3 light_position = glm::vec3(0, 100, 100);

  program.SetUniform("light_color", light_color);
  program.SetUniform("light_position", light_position);

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

    context.DrawArray(vao_cube, gl::ePrimitive::TRIANGLES, 0, positions.size());
    window.SwapBuffers();
  }

  return 0;
}