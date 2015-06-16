
in vec3 vertexColorAV; 
in vec3 vertexPosition;

out vec3 vertexColorVF;

void main() {
	vertexColorVF = vertexColorAV;
	gl_Position = vec4(vertexPosition, 1);  
}