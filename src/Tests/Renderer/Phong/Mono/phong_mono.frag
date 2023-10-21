#version 420 core

uniform vec3 light_position;
uniform vec3 light_color;

uniform vec3 view_position;

in vec3 frag_position;
in vec3 frag_color;
in vec3 frag_normal;

out vec4 color;

vec3 GetAmbient(float strength) {
  return strength * light_color;
}

vec3 GetDiffuse(vec3 normal, vec3 light_dir) {
  float k_diffuse = max(dot(normal, -light_dir), 0.0);
  return k_diffuse * light_color;
}

vec3 GetSpecular(vec3 normal, vec3 light_dir, vec3 to_view,
                 float power) {
  vec3 reflected_light = reflect(light_dir, normal);
  float k_specular = pow(max(dot(to_view, reflected_light), 0.0),
                         power);
  return k_specular * light_color;
}

vec3 GetPhong(vec3 normal, vec3 to_view, vec3 light_dir,
              float ambient_strength, float specular_power) {
  vec3 ambient = GetAmbient(ambient_strength);
  vec3 diffuse = GetDiffuse(normal, light_dir);
  vec3 specular = GetSpecular(normal, light_dir, to_view,
                              specular_power);

  return (ambient + diffuse + specular) * frag_color;
}

void main() {
  vec3 normal = normalize(frag_normal);
  vec3 to_view = normalize(view_position - frag_position);
  vec3 light_dir = normalize(frag_position - light_position);

  color.rgb = GetPhong(normal, to_view, light_dir, 0.3, 32.0);
  color.a = 1.0;
}
