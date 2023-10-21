#version 420 core

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;

out vec3 frag_position;
out vec3 frag_color;
out vec3 frag_normal;

void main() {
  frag_position = vec3(model * vec4(position, 0.1));
  frag_color = vec3(1.0, 0.0, 0.0);
  frag_normal = mat3(transpose(inverse(model))) * normal;

  gl_Position = projection * view * vec4(frag_position, 1.0);
}
