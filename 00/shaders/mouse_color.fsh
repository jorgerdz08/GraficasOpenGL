#version 330

in vec3 vertexColorVF;

uniform ivec2 mousePosition; 

out vec4 pixelColor;

void main() {
	if( distance(mousePosition, gl_FragCoord.xy) < 20 ) discard; 
	else pixelColor = vec4(vertexColorVF, 1); 
}
