#version 430 core

in vec3 position;
//in vec3 normal;
in vec2 texcoords;
in mat3 tbn;

out vec4 fcolor; // Pixel to draw

struct Light {
    vec3 ambient;
    vec3 color;
    vec4 position;
};

struct Material {
    vec3 color;
    float shininess;
    vec2 uv_tiling;
    vec2 uv_offset;
};

uniform Light light;
uniform Material material;

layout (binding = 0) uniform sampler2D diffusemap;
layout (binding = 1) uniform sampler2D normalmap;
//layout (binding = 2) uniform sampler2D emissivemap;

void phong (vec3 position, vec3 normal, out vec3 ambient, out vec3 diffuse, out vec3 specular) {
    // Ambient
    ambient = light.ambient * material.color;

    // Diffuse
    // Calculate light direction (Unit vector)
    vec3 light_dir = normalize(vec3(light.position) - position);

    // Calculate light intensity with dot product (Normal * Light direction)
    float intensity = max(dot(light_dir, normal), 0);
    diffuse = light.color * intensity;

    // Specular
    specular = vec3(0);
    if (intensity > 0) {
        vec3 reflection = reflect(-light_dir, normal);
        vec3 viewdirection = normalize(-vec3(position));

        intensity = max(dot(reflection, viewdirection), 0);
        intensity = pow(intensity, material.shininess);
        specular = light.color * material.color * intensity;
    }
}

void main() {
    vec2 ttexcoords = (texcoords * material.uv_tiling) + material.uv_offset;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    vec3 normal = texture(normalmap, ttexcoords).rgb;
    normal = (normal * 2) - 1;
    normal = normalize(tbn * normal);

    phong(position, normal, ambient, diffuse, specular);

    vec4 texture_color = texture(diffusemap, ttexcoords);
    //vec4 texture_color = mix(texture(diffusemap, ttexcoords), texture(specularmap, ttexcoords), 0.5);

	//fcolor = texture_color;
	fcolor = vec4(ambient + diffuse, 1) * texture_color + vec4(specular, 1);
}