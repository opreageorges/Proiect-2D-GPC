#include "Ambulanta.h"
Ambulanta::Ambulanta() {
	coliziune = 40;
	puncte_generate = 150;
	destroyCoord = -250;
}

void Ambulanta::misca(double viteza) {
	x -= (3 + viteza);
}


void Ambulanta::draw() {
	glPushMatrix();
	// sasiu
	glTranslated(x-80, y[0] - 40,0);
	glRotated(90, 0, 0, 1);

	glColor3f(1, 0, 0);
	glRectf(20, -200, 80, -155);
	glColor3f(1, 1, 1);
	glRectf(20, -155, 80, -115);
	glColor3f(1, 0, 0);
	glRectf(20, -115, 80, -90);

	// faruri
	glColor3f(0.8, 0.5, 0);
	glRectf(25, -90, 35, -85);
	glColor3f(0.8, 0.5, 0);
	glRectf(65, -90, 75, -85);

	// GIROFAR

	glTranslated(50, -135, 0);
	glRotated(rotatie, 0, 0, 1);
	glTranslated(-50, 135, 0);

	//girofar
	glColor4f(0, 0, 1, 0.5);
	glBegin(GL_TRIANGLES);

	glVertex2f(10, -115);
	glVertex2f(50, -135);
	glVertex2f(10, -155);
	
	glVertex2f(50, -135);
	glVertex2f(90, -115);
	glVertex2f(90, -155);
	
	glEnd();

	glPopMatrix();

	rotatie += 15;

}
