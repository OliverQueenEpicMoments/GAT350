#version 430 core

#define POINT 0
#define DIRECTIONAL 1
#define SPOTLIGHT 2

in vec3 position;
in vec3 normal;
in vec2 texcoords;

out vec4 fcolor; // Pixel to draw

uniform struct Light {
    int type;
    vec3 ambient;
    vec3 color;
    vec4 position;
    vec3 direction;
    float cutoff;
    float exponent;
} light;

uniform struct Material {
    vec3 color;
    float shininess;
    vec2 uv_tiling;
    vec2 uv_offset;
} material;

const int levels = 6;
const float scale_factor = 1.0 / levels;

void cell (vec3 position, vec3 normal, out vec3 ambient, out vec3 diffuse, out vec3 specular) {
    // Ambient
    ambient = light.ambient * material.color;

    // Direction vector to light
    vec3 light_dir = (light.type == DIRECTIONAL) ? normalize(-light.direction) : normalize(vec3(light.position) - position);

    // If spotlight, compute intensity based on angle to cutoff
    float spot_intensity = 1;
    if (light.type == SPOTLIGHT) {
        // Get cosin of light direction and direction vector from light
        float cosine = dot(light.direction, -light_dir);
        // Get angle using acos() of the cosine (returns the angle)
        float angle = acos(cosine);

        // If angle less than light.cutoff, set spot intensity else set to 0 (outside)
        spot_intensity = (angle < light.cutoff) ? pow(cosine, light.exponent) : 0;
    }

    // Calculate light intensity with dot product (Normal * Light direction)
    float intensity = max(dot(light_dir, normal), 0) * spot_intensity;
    intensity = floor(intensity * levels) * scale_factor;

    // Calculate diffuse color
    diffuse = light.color * material.color * intensity;

    // Specular
    specular = vec3(0);
    /*if (intensity > 0) {
        vec3 reflection = reflect(-light_dir, normal);
        vec3 viewdirection = normalize(-vec3(position));

        intensity = max(dot(reflection, viewdirection), 0);
        intensity = pow(intensity, material.shininess);
        specular = light.color * material.color * intensity;
    } */
}

void main() {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    cell(position, normal, ambient, diffuse, specular);

	fcolor = vec4(ambient + diffuse, 1) + vec4(specular, 1);
}