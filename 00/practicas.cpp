#include <GL/freeglut.h>
#include <stdio.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define WINDOW_XPOS 300
#define WINDOW_YPOS 300

#define DEBUGMSG 1

void preocessKey(unsigned char, int, int);

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitWindowPosition(WINDOW_XPOS, WINDOW_YPOS);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);

	glutCreateWindow("Mi primer ventana GLUT");

	glutKeyboardFunc(preocessKey);
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
