#version 430 core

in vec2 texcoords;

out vec4 fcolor;

uniform sampler2D texturesampler;

void main() {
	fcolor = texture(texturesampler, texcoords);
}