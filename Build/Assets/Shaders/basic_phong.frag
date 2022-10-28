#version 430 core

in vec3 position;
in vec3 normal;
in vec2 texcoords;

out vec4 fcolor; // Pixel to draw

struct Light {
    vec3 ambient;
    vec3 color;
    vec4 position;
};

struct Material {
    vec3 color;
    float shininess;
};

uniform Light light;
uniform Material material;

uniform sampler2D texturesampler;

void main() {
    // Ambient
    vec3 ambient = light.ambient * material.color;

    // Diffuse
    // Calculate light direction (Unit vector)
    vec3 light_dir = normalize(vec3(light.position) - position);

    // Calculate light intensity with dot product (Normal * Light direction)
    float intensity = max(dot(light_dir, normal), 0);
    vec3 diffuse = light.color * intensity;

    // Specular
    vec3 specular = vec3(0);
    if (intensity > 0) {
        vec3 reflection = reflect(-light_dir, normal);
        vec3 viewdirection = normalize(-vec3(position));

        intensity = max(dot(reflection, viewdirection), 0);
        intensity = pow(intensity, material.shininess);
        specular = light.color * material.color * intensity;
    }
	fcolor = vec4(ambient + diffuse, 1) * texture(texturesampler, texcoords) + vec4(specular, 1);
}