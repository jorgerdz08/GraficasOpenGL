#version 330

in vec3 vertexColorAV; 
in vec3 vertexPosition;

uniform float startX;

out vec3 vertexColorVF;

void main() {
	vertexColorVF = vertexColorAV;
	gl_Position = vec4(vertexPosition.x + startX, vertexPosition.y, vertexPosition.z, 1);  
}
