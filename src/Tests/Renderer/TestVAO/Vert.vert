#version 330 core

layout (location = 0) in vec3 in_position;
layout (location = 1) in vec3 in_color;

out vec3 color;

void main() {
  gl_Position.xyz = in_position;
  gl_Position.w = 1.0;

  color = in_color;
}
