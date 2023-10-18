#version 420 core

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

layout (location = 0) vec3 position;
layout (location = 1) vec3 normal;

out vec3 frag_position;
out vec3 frag_color;
out vec3 frag_normal;

void main() {
  gl_Position = projection * view * model * vec4(position, 0.1);
  frag_color = vec4(1.0, 0.0, 0.0);
  frag_normal = mat3(transpose(inverse(model))) * normal;
}
