#version 430 core 

in layout(location = 0) vec3 vposition; // 0
in layout(location = 1) vec2 vtexcoords; // 2
in layout(location = 2) vec3 vnormal; // 3
in layout(location = 3) vec3 vtangent; // 4

out vec3 position;
//out vec3 normal;
out vec2 texcoords;
out mat3 tbn;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
    // Create model view matrix
    mat4 model_view = view * model;

    // Transform normals to view space
    vec3 normal = normalize(mat3(model_view) * vnormal);
    vec3 tangent = normalize(mat3(model_view) * vtangent);
    vec3 bitangent = cross(normal, tangent);

    tbn = mat3(tangent, bitangent, normal);

    // Transform positions to view space
    position = vec3(model_view * vec4(vposition, 1));

    // Pass through
	texcoords = vtexcoords;

	mat4 MVP = projection * view * model;
	gl_Position = MVP * vec4(vposition, 1.0);
}