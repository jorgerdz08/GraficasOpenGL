#include <GL/freeglut.h>

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitWindowPosition(300, 300);
	glutInitWindowSize(800, 600);

	glutCreateWindow("Mi primer ventana GLUT");
	glutMainLoop();

	return 0;
}
