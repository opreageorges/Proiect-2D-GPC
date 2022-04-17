#include "Masina.h"


Masina::Masina(irrklang::ISoundEngine* audio_engine) : Inamic(audio_engine) {
	destroyCoord = -150;

	coliziune = 100;

	r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	g = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	b = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
}

void Masina::misca(double viteza) {
	x -= viteza;
}

void Masina::draw() {

	glPushMatrix();
	glTranslated(x, y[0] - 35, 0.0);

	// car base
	glColor3f(r, g, b);

	glBegin(GL_POLYGON);
	glVertex2f(1.5, 25);
	glVertex2f(15, 5.5);
	glVertex2f(23.5, 2.5);
	glVertex2f(155.5, 2.5);
	glVertex2f(160, 7.5);
	glVertex2f(160, 66.7);
	glVertex2f(155.5, 71.5);
	glVertex2f(23.5, 71.5);
	glVertex2f(15, 68.5);
	glVertex2f(1.5, 50);
	glEnd();

	// car top
	glColor3f(r - 0.3, g - 0.3, b - 0.3);

	glBegin(GL_POLYGON);
	glVertex2f(55, 37.5);
	glVertex2f(57, 14.5);
	glVertex2f(60.5, 12.5);
	glVertex2f(81.5, 12.5);
	glVertex2f(81.5, 61.5);
	glVertex2f(60.5, 61.5);
	glVertex2f(57, 60);
	glEnd();

	// car back
	glBegin(GL_POLYGON);
	glVertex2f(90, 8);
	glVertex2f(154, 8);
	glVertex2f(154, 66);
	glVertex2f(90, 66);
	glEnd();

	// car lights
	 glColor3f(1.0f, 1.0f, 1.0f);
	
	// right
	glBegin(GL_POLYGON);
	glVertex2f(15, 6);
	glVertex2f(15.5, 16.5);
	glVertex2f(5.5, 20);
	glEnd();

	// left
	glBegin(GL_POLYGON);
	glVertex2f(5.5, 54.5);
	glVertex2f(15.5, 58);
	glVertex2f(15, 68);
	glEnd();

	// car windows
	glColor3f(0.0f, 0.0f, 0.0f);

	// front
	glBegin(GL_POLYGON);
	glVertex2f(42.5, 6.5);
	glVertex2f(57, 14.5);
	glVertex2f(55, 37.5);
	glVertex2f(57, 60);
	glVertex2f(42.5, 67.5);
	glVertex2f(36, 43);
	glVertex2f(36, 31.5);
	glEnd();

	// left
	glBegin(GL_POLYGON);
	glVertex2f(60.5, 62);
	glVertex2f(79, 62);
	glVertex2f(85.5, 67);
	glVertex2f(50.5, 67);
	glEnd();

	// right
	glBegin(GL_POLYGON);
	glVertex2f(50.5, 7);
	glVertex2f(85.5, 7);
	glVertex2f(79, 12.5);
	glVertex2f(60.5, 12.5);
	glEnd();


	// tiers

	glBegin(GL_POLYGON);
	glVertex2f(31, 0);
	glVertex2f(56, 0);
	glVertex2f(31, 2);
	glVertex2f(56, 2);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex2f(31, 72);
	glVertex2f(56, 72);
	glVertex2f(56, 74);
	glVertex2f(31, 74);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex2f(116, 0);
	glVertex2f(141, 0);
	glVertex2f(141, 2);
	glVertex2f(116, 2);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex2f(116, 72);
	glVertex2f(141, 72);
	glVertex2f(141, 74);
	glVertex2f(116, 74);
	glEnd();

	glPopMatrix();
};
