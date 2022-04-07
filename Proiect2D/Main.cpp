#include<windows.h>
#include <GL\freeglut.h>
#include <iostream>
#include "Jucator.h"
#include "Inamic.h"

using namespace std;


// Marimea zonei de joc
GLdouble left_m = -100.0;
GLdouble right_m = 700.0;
GLdouble bottom_m = -140.0;
GLdouble top_m = 460.0;

int argc_bu;
char** argv_bu;

// daca e 1 jocul merge daca e 0 ai pierdut
double ok;

Jucator juc;

Inamic* inamic;

int score;

// Nr de puncte la care se mareste dificultatea
int pct = 1000;

// Jocul este in pauza
bool paused;

void init(void)
{
	glClearColor(0.98, 0.929, 0.792, 0.0);
	glMatrixMode(GL_PROJECTION);
	glOrtho(left_m, right_m, bottom_m, top_m, -1.0, 1.0);
}

void RenderString(float x, float y, void* font, const unsigned char* string)
{

	glColor3f(0.0f, 0.0f, 0.0f);
	glRasterPos2f(x, y);
	glutBitmapString(font, string);
}

void initGame() {
	score = 0;

	juc = Jucator();
	inamic = new Inamic();

	ok = 1;

	paused = FALSE;
}

void startgame(void)
{

	if ((* inamic).get_y() == juc.get_y() && ((*inamic).get_x() < juc.get_x() + 90 && (*inamic).get_x() > juc.get_x() - 90)) {
		ok = 0;
		return;
	}

	(*inamic).misca(0.1);

	if ((*inamic).get_x() < -150)
	{
		score += (*inamic).getPuncte();
		cout << "Score:  " << score << endl;
		delete inamic;
		inamic = new Inamic();
	}

	glutPostRedisplay();
	
}


void scoredisplay(int posx, int posy, int space_char, int scorevar)
{
	int j = 0, p, k;
	GLvoid* font_style1 = GLUT_BITMAP_TIMES_ROMAN_24;

	p = scorevar;
	j = 0;
	k = 0;
	while (p > 9)
	{
		k = p % 10;
		glRasterPos2f((posx - (j * space_char)), posy);
		glutBitmapCharacter(font_style1, 48 + k);
		j++;
		p /= 10;
	}
	glRasterPos2f((posx - (j * space_char)), posy);
	glutBitmapCharacter(font_style1, 48 + p);

}

void drawBackground() {
	glColor3f(0.55, 0.788, 0.451);

	// Iarba de jos
	glBegin(GL_POLYGON);
	glVertex2i(-100, -140);// Stanga jos
	glVertex2i(700, -140); // Dreapta jos
	glVertex2i(700, -80);  // Dreapta sus
	glVertex2i(-100, -80); // Stanga sus
	glEnd();

	// Iarba de sus
	glBegin(GL_POLYGON);
	glVertex2i(-100, 400);// Stanga jos
	glVertex2i(700, 400); // Dreapta jos
	glVertex2i(700, 460); // Dreapta sus
	glVertex2i(-100, 460);// Stanga sus
	glEnd();
	RenderString(200.0f, 425.0f, GLUT_BITMAP_TIMES_ROMAN_24, (const unsigned char*)"Depaseste masinile! Scor :");
	scoredisplay(525.0f, 425.0f, 15, score);

	// Delimitare sosea
	glLineWidth(3);
	glColor3f(1, 1, 1);

	// Delimitam soseaua de iarba partea de jos
	glBegin(GL_LINES);
	glVertex2i(-100, -80);
	glVertex2i(1500, -80);
	glEnd();

	// Delimitam soseaua de iarba partea de sus
	glBegin(GL_LINES);
	glVertex2i(-100, 400);
	glVertex2i(1500, 400);
	glEnd();

	// Liniile intrerupte

	glBegin(GL_LINES);
	glVertex2i(-100, 80);
	glVertex2i(1500, 80);
	glEnd();

	glBegin(GL_LINES);
	glVertex2i(-100, 240);
	glVertex2i(1500, 240);
	glEnd();

	glPopMatrix();
}

void drawScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT);

	drawBackground();
	

	if (ok == 0) {
		RenderString(250.0f, 200.0f, GLUT_BITMAP_8_BY_13, (const unsigned char*)"GAME OVER");
	}

	juc.draw();
	(*inamic).draw();
	
	if (!paused && ok == 1) {
		startgame();
	}
	glutPostRedisplay();
	glutSwapBuffers();
	glFlush();


}

void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-100.0, 700.0, -140.0, 460.0, -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void pauseGame(void) {

	if (ok != 0)
	{
		paused = !paused;
	}
}

void keyboard(int key, int x, int y)
{
	if (paused || ok == 0) {
		return;
	}
	switch (key) {
	case GLUT_KEY_UP:
		juc.miscasus();
		break;
	case GLUT_KEY_DOWN:
		juc.miscajos();
		break;
	case GLUT_KEY_RIGHT:
		juc.miscaDreapta();
		break;
	case GLUT_KEY_LEFT:
		juc.miscaStanga();
		break;
	}

}

void normalKeyboard(unsigned char key, int x, int y)
{
	switch (key) {
	case ' ':
		pauseGame();
		break;
	case 'r':
		initGame();
		break;
	}
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(800, 600);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Depaseste masinile - mini game");
	init();
	initGame();
	glutDisplayFunc(drawScene);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(normalKeyboard);
	glutSpecialFunc(keyboard);

	glutMainLoop();

}