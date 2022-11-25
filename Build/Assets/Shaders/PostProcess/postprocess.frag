#version 430 core

in vec2 texcoord;

out vec4 fcolor;

const float screen_height = 600;

uniform float offset;
uniform sampler2D textureMap;

void main() {
    // Black and white
    // vec3 color = texture(textureMap, texcoord).rgb;
    // float avg = (color.r + color.g + color.b) / 3.0; 
	// fcolor = vec4(vec3(avg), 1); 

    // Inverted
    // vec3 color = texture(textureMap, texcoord).rgb;
	// fcolor = vec4(1.0 - color, 1); 

    // Night Vision
    // vec3 color = texture(textureMap, texcoord).rgb;
    // float avg = (color.r + color.g + color.b) / 3.0;
	// fcolor = vec4(vec3(0, avg, 0), 1);

    // Scaline
    // vec3 color = texture(textureMap, texcoord).rgb;
    // int y = int(texcoord.y * screen_height);
    // float alpha = (y % 6 != 0) ? 1 : 0;
    // fcolor = vec4(alpha, color);

    // Wave
    // vec2 ttexcoord = texcoord;
    // ttexcoord.x += sin(ttexcoord.y * 50.0 + offset) / 50.0;
    // fcolor = texture(textureMap, ttexcoord);

	fcolor = texture(textureMap, texcoord);
}
