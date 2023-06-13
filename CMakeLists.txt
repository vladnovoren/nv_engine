cmake_minimum_required(VERSION 3.22.1)

project(nv_engine)

set(CMAKE_EXPORT_COMPILE_COMMANDS "ON")

add_subdirectory(third_party)

include_directories(
  third_party/AntTweakBar-1.16/include/
  third_party/glfw-3.1.2/include/
  third_party/glm-0.9.7.1/
  third_party/glew-1.13.0/include/
  third_party/assimp-3.0.1270/include/
  third_party/bullet-2.81-rev2613/src/
  inc/
  .
)

set(OpenGL_libs
  ${OPENGL_LIBRARY}
  glfw
  GLEW_1130
)

add_definitions(
  -DTW_STATIC
  -DTW_NO_LIB_PRAGMA
  -DTW_NO_DIRECT3D
  -DGLEW_STATIC
)

add_library(RendererOpenGL STATIC)

target_compile_options(RendererOpenGL PRIVATE
  -Wall
  -Wextra
  -Wpedantic
  -Werror
)

target_sources(RendererOpenGL PUBLIC
  src/Renderer/OpenGL/Buffers/Bindable.cpp
  src/Renderer/OpenGL/Buffers/BufferLayout.cpp

  src/Renderer/OpenGL/Buffers/IndexBuffer.cpp
  src/Renderer/OpenGL/Buffers/VertexArray.cpp
  src/Renderer/OpenGL/Buffers/VertexBuffer.cpp

  src/Renderer/OpenGL/Shaders/Program.cpp
  src/Renderer/OpenGL/Shaders/Shader.cpp

  src/Renderer/OpenGL/Window/Window.cpp
  src/Renderer/OpenGL/Window/Context.cpp
)

include_directories(
  inc/Renderer/
  inc/Renderer/Interface/
  inc/Renderer/OpenGL/

  inc/Tools
)


target_link_libraries(RendererOpenGL ${OpenGL_libs})

add_executable(test_VAO)

target_sources(test_VAO PUBLIC
  src/Tests/Renderer/TestVAO/TestVAO.cpp
)

target_link_libraries(test_VAO PUBLIC RendererOpenGL)
