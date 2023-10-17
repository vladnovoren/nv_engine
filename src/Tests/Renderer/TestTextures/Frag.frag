#version 420 core

in vec2 uv;
out vec4 out_color;

uniform sampler2D uNoneMap;

void main() {
  out_color.rgb = texture(uNoneMap, uv).rgb;
  out_color.a = 1.0;
}
