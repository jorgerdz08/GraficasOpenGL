#include <GL/glew.h>
#include <GL/freeglut.h>
#include <stdio.h>
#include <iostream>

using namespace std;

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define WINDOW_XPOS 300
#define WINDOW_YPOS 300

#define DEBUGMSG 1

void preocessKey(unsigned char, int, int);
void processSpecialKey(int, int, int);

void display(void);
void createTriangle(void);
void createRectangle(void);

GLfloat trianglePos[] = { 0.0,  0.9,  1.0,
						  -0.9, -0.9,  1.0,
						   0.9, -0.9,  1.0
};

//								x,    y,   r,   g,   b
GLfloat rectanglePosCol[] = { -0.7,  0.7, 0.9, 0.9, 0.0,
							   -0.7, -0.7, 0.9, 0.0, 0.0,
							    0.7,  0.7, 0.0, 0.0, 0.9,
							    0.7, -0.7, 0.0, 0.9, 0.9
};

GLuint vertexArrayId[2];

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

	glutCreateWindow("Mi primer ventana GLUT");

	glutKeyboardFunc(preocessKey);
	glutSpecialFunc(processSpecialKey);
	glutDisplayFunc(display);

	glewInit();
	if(GLEW_VERSION_4_0){
		cout << "OpenGL 4.0 supported" << endl;
	}
	glClearColor(0.72, 0.28, 0.46, 1.0);
	glGenVertexArrays(2, vertexArrayId);
	createTriangle();
	createRectangle();

	glutMainLoop();

	return 0;
}

void preocessKey(unsigned char key, int x, int y){
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


void processSpecialKey(int key, int x, int y) {
	int keyModifier;

#if DEBUGMSG
	if(116 == key)
		printf("Special key press: Alt + ");
	else
		printf("F%d\n", key);
#endif

	switch(key) {
	case GLUT_KEY_F4 :
		keyModifier = glutGetModifiers();
		if (keyModifier == (GLUT_ACTIVE_ALT))
			exit(0);
		break;
	}
}

void display(){
	glClear(GL_COLOR_BUFFER_BIT);
	glBindVertexArray(vertexArrayId[0]);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glBindVertexArray(vertexArrayId[1]);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 5);
	glutSwapBuffers();
}

void createTriangle(){
	glBindVertexArray(vertexArrayId[0]);
	glBindBuffer(GL_ARRAY_BUFFER, 1);
	glBufferData(GL_ARRAY_BUFFER, sizeof(trianglePos), trianglePos, GL_STATIC_DRAW);
	glVertexPointer(3, GL_FLOAT, 0, 0);
	glEnableClientState(GL_VERTEX_ARRAY);
}

void createRectangle(){
	GLuint bufferID[2];
	glBindVertexArray(vertexArrayId[1]);
	glGenBuffers(2, bufferID);
	glBindBuffer(GL_ARRAY_BUFFER, bufferID[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(rectanglePosCol), rectanglePosCol, GL_STATIC_DRAW);
	glVertexPointer(3, GL_FLOAT, 5*sizeof(GLfloat), 0);
	glEnableClientState(GL_VERTEX_ARRAY);
}
