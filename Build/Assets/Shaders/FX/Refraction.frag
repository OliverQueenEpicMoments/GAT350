#version 430 core

in vec3 refractiondir;

out vec4 fcolor;

uniform samplerCube cubemap;

void main() {
	fcolor = texture(cubemap, refractiondir);
}