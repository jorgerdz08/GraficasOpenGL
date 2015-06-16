
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <stdio.h>
#include <iostream>
#include "utils/Utils.h"

using namespace std;

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define WINDOW_XPOS 300
#define WINDOW_YPOS 300

#define DEBUGMSG 0

void keyboardHandler(unsigned char, int, int);
void display(void);
void createTriangle(void);
void initShaders(void);

GLfloat trianglePos[] = {  0.0,  0.9,  1.0,
						  -0.9, -0.9,  1.0,
						   0.9, -0.9,  1.0
};

GLfloat triangleCol[] = {  1.0,  0.0, 0.0,
						   0.0,  1.0, 0.0,
						   0.0,  0.0, 1.0
};

GLuint programId;
GLuint vertexArrayId[1];
GLint vertexPositionLoc, vertexColorLoc;


void keyboardHandler(unsigned char key, int x, int y){
#if DEBUGMSG
	printf("Key press: %c\n", key);
#endif
	if( 27 == key){
    	exit(0);
	}
	else if( 'f' == key){
		//glutEnterGameMode();	// Hangs when run on laptop HP ZBook
		glutFullScreenToggle();
	}
}

void initShaders(){
	GLuint vShaderId = Utils::compileShader("shaders/color_position.vsh", GL_VERTEX_SHADER);
	if(!Utils::shaderCompiled(vShaderId)) return;

	GLuint fShaderId= Utils::compileShader("shaders/color.fsh", GL_FRAGMENT_SHADER);
	if(!Utils::shaderCompiled(fShaderId)) return;

	programId = glCreateProgram();
	glAttachShader(programId, vShaderId);
	glAttachShader(programId, fShaderId);
	glLinkProgram(programId);

	vertexPositionLoc= glGetAttribLocation(programId, "vertexPosition");
	vertexColorLoc = glGetAttribLocation(programId, "vertexColorAV");

}

void transferData(){
	glGenVertexArrays(1, vertexArrayId);
	glBindVertexArray(vertexArrayId[0]);
	GLuint bufferId[2];
	glGenBuffers(2, bufferId);

	glBindBuffer(GL_ARRAY_BUFFER, bufferId[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(trianglePos), trianglePos, GL_STATIC_DRAW);
	glVertexAttribPointer(vertexPositionLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(vertexPositionLoc);

	glBindBuffer(GL_ARRAY_BUFFER, bufferId[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(triangleCol), triangleCol, GL_STATIC_DRAW);
	glVertexAttribPointer(vertexColorLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(vertexColorLoc);
}

void display(){
	glClear(GL_COLOR_BUFFER_BIT);

	glUseProgram(programId);
	glBindVertexArray(vertexArrayId[0]);
	glDrawArrays(GL_TRIANGLES, 0, 3);

	glutSwapBuffers();
}

int main(int argc, char** argv) {
	int screenX, screenY;
	int screenResX, screenResY;

	glutInit(&argc, argv);

	screenResX  = glutGet(GLUT_SCREEN_WIDTH);
	screenResY = glutGet(GLUT_SCREEN_HEIGHT);
	screenX  = (screenResX-WINDOW_WIDTH)/2;
	screenY =  (screenResY-WINDOW_HEIGHT)/2;

	glutInitWindowPosition(screenX, screenY);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutCreateWindow("Mi primera experiencia con shaders");

	glutKeyboardFunc(keyboardHandler);
	glutDisplayFunc(display);

	glewInit();
	initShaders();
	transferData();
	glClearColor(0.85, 0.90, 0.75, 1.0);

	glutMainLoop();
	return 0;
}
