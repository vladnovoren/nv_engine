#version 330 core

in vec3 color;
out vec4 out_color;

void main() {
  out_color.rgb = color;
  out_color.a = 1.0;
}

