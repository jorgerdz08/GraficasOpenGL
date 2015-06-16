
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
GLint vertexPositionLoc, vertexColorLoc, startXLoc, colorFactorLoc;

GLfloat r = 1.0;
GLfloat g = 1.0;
GLfloat b = 1.0;

GLfloat startX = 0.0;

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

void timerFunc(int id) {
	glutTimerFunc(5, timerFunc, 1);
	glutPostRedisplay();
}

void initShaders(){
	GLuint vShaderId = Utils::compileShader("shaders/col_pos_startX.vsh", GL_VERTEX_SHADER);
	if(!Utils::shaderCompiled(vShaderId)) return;

	GLuint fShaderId= Utils::compileShader("shaders/color.fsh", GL_FRAGMENT_SHADER);
	if(!Utils::shaderCompiled(fShaderId)) return;

	programId = glCreateProgram();
	glAttachShader(programId, vShaderId);
	glAttachShader(programId, fShaderId);
	glLinkProgram(programId);

	vertexPositionLoc= glGetAttribLocation(programId, "vertexPosition");
	vertexColorLoc = glGetAttribLocation(programId, "vertexColorAV");
	startXLoc = glGetUniformLocation(programId, "startX");
	colorFactorLoc = glGetUniformLocation(programId, "colorFactor");

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

#if DEBUGMSG
	printf("startX: %f\n", startX);
#endif
	glUniform1f(startXLoc, startX);
	glUniform3f(colorFactorLoc, r, g, b);

	glBindVertexArray(vertexArrayId[0]);
	glDrawArrays(GL_TRIANGLES, 0, 3);

	glutSwapBuffers();
	startX += 0.005;
	if(startX >= 1.9) startX = -1.9;

	//r *= 0.9996;
	r -= 0.005;
	if(r<0.5) r = 1.0;

	//g *= 0.9993;
	g -= 0.005;
	if(g<0.5) g = 1.0;

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
	glutTimerFunc(5, timerFunc, 1);

	glewInit();
	initShaders();
	transferData();
	glClearColor(0.85, 0.90, 0.75, 1.0);

	glutMainLoop();
	return 0;
}
