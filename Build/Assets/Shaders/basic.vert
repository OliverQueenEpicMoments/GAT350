#version 430 core 
in layout(location = 0) vec3 vposition; // 0
in layout(location = 1) vec3 vcolor; // 1

out vec3 color;

void main() {
	color = vcolor;

	gl_Position = vec4(vposition, 1.0);
}