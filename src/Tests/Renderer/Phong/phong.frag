#version 420 core

uniform vec3 light_position;
uniform vec3 light_color;

uniform vec3 view_position;

uniform sampler2D uAlbedoMap;

in vec3 frag_position;
in vec2 frag_uv;
in vec3 frag_normal;

out vec4 frag_color;

void main() {
    vec3 normal = normalize(frag_normal);

    vec3 light_dir = normalize(frag_position - light_position);

    float ambient_strength = 0.3;
    vec3 ambient = ambient_strength * light_color;

    float k_diff = max(dot(normal, -light_dir), 0.0);
    vec3 diffuse = k_diff * light_color;

    float specular_strength = 0.5;
    vec3 to_view = normalize(view_position - frag_position);
    vec3 light_reflect = reflect(light_dir, normal);
    float k_specular = pow(max(dot(to_view, light_reflect), 0.0), 32);
    vec3 specular = specular_strength * k_specular * light_color;

    vec3 result = (ambient + diffuse + specular) * texture(uAlbedoMap, frag_uv).rgb;
//    frag_color = vec4(texture(uAlbedoMap, frag_uv).rgb, 1.0);
    frag_color = vec4(result, 1.0);
}
