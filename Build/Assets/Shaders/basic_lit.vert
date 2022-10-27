#version 430 core 

in layout(location = 0) vec3 vposition; // 0
in layout(location = 1) vec2 vtexcoords; // 2
in layout(location = 2) vec3 vnormal; // 3

out vec2 texcoords;
out vec3 color;

struct Light {
    vec3 color;
    vec4 position;
};

struct Material {
    vec3 color;
    float shininess;
};

uniform Light light;
uniform Material material;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
	texcoords = vtexcoords;

    // Diffuse
    // Create model view matrix
    mat4 model_view = view * model;

    // Transform normals to view space
    vec3 normal = mat3(model_view) * vnormal;

    // Transform positions to view space
    vec4 position = model_view * vec4(vposition, 1);

    // Calculate light direction (Unit vector)
    vec3 light_dir = normalize(vec3(light.position - position));

    // Calculate light intensity with dot product (Normal * Light direction)
    float intensity = max(dot(light_dir, normal), 0);
    vec3 diffuse = light.color * intensity;

    // Specular
    vec3 specular = vec3(0);
    if (intensity > 0) {
        vec3 reflection = reflect(-light_dir, normal);
        vec3 viewdirection = normalize(-vec3(position));
        intensity = max(dot(reflection, viewdirection), 0);
        intensity = pow(intensity, 32);
        specular = light.color * intensity;
    }

    color = vec3(0.2) + diffuse + specular;

	mat4 MVP = projection * view * model;
	gl_Position = MVP * vec4(vposition, 1.0);
}