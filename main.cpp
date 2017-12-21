#include <windows.h>
#include "Dependencies\glew\glew.h"
#include "Dependencies\freeglut\freeglut.h"
#include <cmath>

static int w = 0, h = 0;
float angle = 0.0;
GLdouble eyeX = 0.0, eyeY = 0.0, eyeZ = 5.0;
double distance = 5.0;
double eyeAngle = 0;

void reshape(int width, int height)
{
	w = width;
	h = height;
	glViewport(0, 0, w, h); // задаётся область вывода изображения размером со всё окно
	glMatrixMode(GL_PROJECTION); // загружается матрица проекции
	glLoadIdentity();
	gluPerspective(42.0f, 1.0f, 0.1f, 20.0f); // матрица наблюдения перспективной проекции
}

void init(void)
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClearDepth(1);
}

void specialKeys(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_UP:
		eyeY += 0.5;
		break;
	case GLUT_KEY_DOWN:
		eyeY -= 0.5;
		break;
	case GLUT_KEY_LEFT:
		eyeAngle += 0.5;
		eyeX = distance * cos(eyeAngle);
		eyeZ = distance * sin(eyeAngle);
		break;
	case GLUT_KEY_RIGHT:
		eyeAngle -= 0.5;
		eyeX = -distance * cos(eyeAngle);
		eyeZ = -distance * sin(eyeAngle);
		break;
	}
	glutPostRedisplay();
}

void update(void)
{
	angle += 0.005;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	glMatrixMode(GL_MODELVIEW); // загружается модельно-видовая матрица
	glLoadIdentity();
	gluLookAt(eyeX, eyeY, eyeZ, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

	glRotatef(angle, 0.0f, 1.0f, 0.0f);
	//glTranslatef(0.5f, 0.0f, 0.0f);

	glColor3ub(255, 215, 0);
	glutSolidCube(0.7);

	glPushMatrix();
	glColor3ub(205, 127, 50);
	glTranslatef(0.5, -0.21, 0.0);
	glutSolidCube(0.3);
	glPopMatrix();

	glColor3ub(192, 192, 192);
	glTranslatef(-0.6, -0.1, 0.0);
	glutSolidCube(0.5);

	glPushMatrix();
	glLoadIdentity();
	GLfloat point_light0_pos[] = { 5.0, 0.0, 0.0, 1.0 };
	glLightfv(GL_LIGHT0, GL_POSITION, point_light0_pos);
	GLfloat diffuse0[] = { 1.0, 0.0, 0.0, 0.0 };
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse0);
	glPopMatrix();

	glPushMatrix();
	glLoadIdentity();
	GLfloat point_light1_pos[] = { -5.0, 0.0, 0.0, 1.0 };
	glLightfv(GL_LIGHT1, GL_POSITION, point_light1_pos);
	GLfloat diffuse1[] = { 0.0, 0.0, 1.0, 0.0 };
	glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuse1);
	glPopMatrix();

	glPushMatrix();
	glLoadIdentity();
	GLfloat projector_pos[] = { 0.0, 0.0, -1.0, 1.0 };
	GLfloat direction[] = { 0.0, 0.0, 1.0 };
	GLfloat proj_diffuse[] = { 0.5, 0.9, 0.0, 0.0 };
	glLightfv(GL_LIGHT2, GL_POSITION, projector_pos);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, proj_diffuse);
	glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, direction);
	//glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 42);
	//glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, 4);
	glPopMatrix();

	glFlush();
	glutSwapBuffers();
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitWindowPosition(200, 200);
	glutInitWindowSize(800, 800);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutCreateWindow("Hello!");
	glutDisplayFunc(update);
	glutIdleFunc(update);
	glutReshapeFunc(reshape);
	glutSpecialFunc(specialKeys);

	init();
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glEnable(GL_LIGHT2);

	glutMainLoop();
	return 0;
}