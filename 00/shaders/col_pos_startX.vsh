#version 330

in vec3 vertexColorAV; 
in vec3 vertexPosition;

uniform float startX;

uniform vec3 colorFactor;

out vec3 vertexColorVF;

void main() {
    vertexColorVF = vertexColorAV * colorFactor;
	gl_Position = vec4( vertexPosition + vec3(startX, 0, 0), 1);   // Another method to assign the uniform to gl_Position
	//gl_Position = vec4(vertexPosition.x + startX, vertexPosition.y, vertexPosition.z, 1);  
}
