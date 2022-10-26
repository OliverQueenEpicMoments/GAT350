#version 430 core

in vec2 texcoords;
in vec3 color;

out vec4 fcolor;

uniform sampler2D texturesampler;

void main() {
	fcolor = texture(texturesampler, texcoords) * vec4(color, 1);
}