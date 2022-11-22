#version 430 core

in vec3 reflectiondir;
in vec3 refractiondir;

out vec4 fcolor;

uniform float interp;

layout (binding = 0) uniform samplerCube cubemap;

void main() {
    vec3 reflect_color = texture(cubemap, reflectiondir).rgb; 
    vec3 refract_color = texture(cubemap, refractiondir).rgb; 
	fcolor = vec4(mix(reflect_color, refract_color, interp), 1);
}