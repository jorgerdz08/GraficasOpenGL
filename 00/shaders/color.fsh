#version 330

in vec3 vertexColorVF;

out vec4 pixelColor;

void main() {
	pixelColor = vec4(vertexColorVF, 1); 
}
