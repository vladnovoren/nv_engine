#version 420 core

uniform vec3 light_position;
uniform vec3 light_color;

uniform sampler2D uAlbedoMap;

in vec3 frag_position;
in vec2 frag_uv;
in vec3 frag_normal;

out vec4 frag_color;

void main() {
    vec3 normal = normalize(frag_normal);

    vec3 light_dir = normalize(frag_position - light_position);

    float ambient_strength = 0.1;
    vec3 ambient = ambient_strength * light_color;

    float k_diff = max(dot(normal, -light_dir), 0.0);
    vec3 diffuse = k_diff * light_color;

    vec3 result = (ambient + diffuse) * texture(uAlbedoMap, frag_uv).rgb;
    frag_color = vec4(result, 1.0);
}