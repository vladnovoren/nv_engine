#version 420 core

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 uv;
layout (location = 2) in vec3 normal;

out vec3 frag_position;
out vec2 frag_uv;
out vec3 frag_normal;

void main() {
    gl_Position = projection * view * model * vec4(position, 1.0);
    frag_position = vec3(model * vec4(position, 1.0)); // calculations in fragment shader are to be done in world space

    frag_uv = uv;

    frag_normal = mat3(transpose(inverse(model))) * normal; // normal vectors must be transformed in a different way than position vectors
}

