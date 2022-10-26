#version 430 core 
in layout(location = 0) vec3 vposition; // 0
//in layout(location = 1) vec3 vcolor; // 1
in layout(location = 1) vec2 vtexcoords; // 2

out vec3 color;
out vec2 texcoords;

uniform float scale;
uniform mat4 MVP;

void main() {
	//color = vcolor;
	texcoords = vtexcoords;
	vec4 tposition = MVP * vec4(vposition * scale, 1);
	gl_Position = tposition;
}

/*#version 430 core 

in layout(location = 0) vec3 vposition;  0
in layout(location = 1) vec2 vtexcoords;  2

out vec2 texcoords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
	texcoords = vtexcoords;

	mat4 MVP = projection * view * model;
	gl_Position = MVP * vec4(vposition, 1.0);
}*/