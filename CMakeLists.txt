cmake_minimum_required(VERSION 3.22.1)

project(nv_engine)

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

add_library(Renderer STATIC)
add_library(RendererInterface STATIC)
add_library(RendererOpenGL STATIC)

target_compile_options(Renderer PRIVATE
  -Wall
  -Wextra
  -Wpedantic
  -Werror
)

target_sources(RendererInterface PUBLIC
  src/Renderer/Interface/Renderer.cpp

  src/Renderer/Interface/Buffers/ABindable.cpp
  src/Renderer/Interface/Buffers/ABuffer.cpp
  src/Renderer/Interface/Buffers/AIndexBuffer.cpp
  src/Renderer/Interface/Buffers/AVertexArray.cpp
  src/Renderer/Interface/Buffers/AVertexBuffer.cpp
  src/Renderer/Interface/Buffers/BufferLayout.cpp

  src/Renderer/Interface/Shaders/AShader.cpp
)

target_sources(RendererOpenGL PUBLIC
  src/Renderer/RendererAPIs/OpenGL/OpenGL_RendererAPI.cpp

  src/Renderer/RendererAPIs/OpenGL/Buffers/OpenGL_IndexBuffer.cpp
  src/Renderer/RendererAPIs/OpenGL/Buffers/OpenGL_VertexArray.cpp
  src/Renderer/RendererAPIs/OpenGL/Buffers/OpenGL_VertexBuffer.cpp

  src/Renderer/RendererAPIs/OpenGL/Shaders/OpenGL_Shader.cpp
)

include_directories(
  inc/Renderer/
  inc/Renderer/Interface/

  inc/Renderer/RendererAPIs/
  inc/Renderer/RendererAPIs/OpenGL/

  inc/Tools
)


target_link_libraries(RendererOpenGL ${OpenGL_libs} RendererInterface)
target_link_libraries(Renderer RendererOpenGL)
