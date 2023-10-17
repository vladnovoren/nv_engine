cmake_minimum_required(VERSION 3.22.1)

project(nv_engine)

set(CMAKE_EXPORT_COMPILE_COMMANDS "ON")
set(CMAKE_CXX_STANDARD 23)
list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")

find_package(glfw3 REQUIRED)
find_package(GLEW REQUIRED)
find_package(glm REQUIRED)
find_package(assimp REQUIRED)

add_library(nv_engine)

add_library(Core STATIC)

set(Core_INCLUDE_DIRS
  inc/
  inc/Core/
  inc/Core/Models/Mesh/
)

target_sources(Core PUBLIC
  src/Core/Transform.cpp

  src/Core/Camera/PerspectiveCamera.cpp
)

target_include_directories(Core PUBLIC ${Core_INCLUDE_DIRS})

target_compile_options(Core PUBLIC
  -Wall
  -Wextra
  -Wpedantic
  -Werror

  -g
)

set(OpenGL_libs
  OpenGL
  glfw
  GLEW
  assimp
)

add_library(RendererOpenGL STATIC)

set(RendererOpenGL_INCLUDE_DIRS
  inc/
  inc/Renderer/OpenGL/
  inc/Tools
)

target_compile_options(RendererOpenGL PRIVATE
  -Wall
  -Wextra
  -Wpedantic
  -Werror

  -g
)

target_include_directories(RendererOpenGL PUBLIC ${RendererOpenGL_INCLUDE_DIRS})

target_sources(RendererOpenGL PUBLIC
  src/Renderer/OpenGL/Buffers/BufferLayout.cpp

  src/Renderer/OpenGL/Buffers/IndexBuffer.cpp
  src/Renderer/OpenGL/Buffers/VertexArray.cpp
  src/Renderer/OpenGL/Buffers/VertexBuffer.cpp

  src/Renderer/OpenGL/Shaders/Program.cpp
  src/Renderer/OpenGL/Shaders/Shader.cpp

  src/Renderer/OpenGL/Models/Model.cpp
  src/Renderer/OpenGL/Models/Mesh.cpp
  src/Renderer/OpenGL/Models/Material.cpp

  src/Renderer/OpenGL/Textures/Texture2D.cpp

  src/Renderer/OpenGL/Window/Window.cpp
  src/Renderer/OpenGL/Window/Context.cpp
)

target_link_libraries(RendererOpenGL ${OpenGL_libs})
target_link_libraries(RendererOpenGL Core)
target_link_libraries(nv_engine PUBLIC RendererOpenGL)

add_executable(test_VAO)
target_sources(test_VAO PUBLIC
  src/Tests/Renderer/TestVAO/TestVAO.cpp
)
target_link_libraries(test_VAO PUBLIC nv_engine)

add_executable(test_textures)
target_sources(test_textures PUBLIC
  src/Tests/Renderer/TestTextures/main.cpp
)
target_link_libraries(test_textures PUBLIC nv_engine)

add_executable(test_phong)
target_sources(test_phong PUBLIC
  src/Tests/Renderer/Phong/phong.cpp
)
target_link_libraries(test_phong PUBLIC nv_engine)

