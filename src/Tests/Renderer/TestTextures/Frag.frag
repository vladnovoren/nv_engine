#version 330 core

in vec2 uv; 
out vec4 out_color;

uniform sampler2D texture_sampler;

void main() {
  out_color.rgb = texture(texture_sampler, uv).rgb;
  out_color.a = 1.0;
}
