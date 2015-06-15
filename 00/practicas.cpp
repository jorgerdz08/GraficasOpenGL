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

	glewInit();
	if(GLEW_VERSION_4_0){
		cout << "OpenGL 4.0 supported" << endl;
	}

	glutMainLoop();

	return 0;
}

void preocessKey(unsigned char key, int x, int y)
{
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
