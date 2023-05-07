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

add_library(Renderer STATIC
)

target_compile_options(Renderer PRIVATE
  -Wall
  -Wextra
  -Wpedantic
  -Werror
)

target_sources(Renderer PUBLIC
  src/Renderer/Renderer.cpp

  src/Renderer/Buffers/ABuffer.cpp
  src/Renderer/Buffers/AIndexBuffer.cpp
  src/Renderer/Buffers/AVertexBuffer.cpp
  src/Renderer/Buffers/BufferLayout.cpp
  src/Renderer/Buffers/AVertexArray.cpp
  src/Renderer/Buffers/ABindable.cpp
  
  src/Renderer/RendererAPIs/OpenGL/OpenGL_RendererAPI.cpp

  src/Renderer/RendererAPIs/OpenGL/Buffers/OpenGL_IndexBuffer.cpp
  src/Renderer/RendererAPIs/OpenGL/Buffers/OpenGL_VertexArray.cpp
  src/Renderer/RendererAPIs/OpenGL/Buffers/OpenGL_VertexBuffer.cpp
)

target_include_directories(Renderer PRIVATE
  inc/Renderer/
  inc/Renderer/Buffers/
  
  inc/Renderer/RendererAPIs/
  inc/Renderer/RendererAPIs/OpenGL/
  inc/Renderer/RendererAPIs/OpenGL/Buffers

  inc/Tools
)