#include "Masina.h"


Masina::Masina(irrklang::ISoundEngine* audio_engine) : Inamic(audio_engine) {
	destroyCoord = -15;

	coliziune = 7;

	r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	g = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	b = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
}

void Masina::misca(double viteza) {
	x -= viteza;
}

void Masina::draw() {
	glPushMatrix();
	glColor3f(0, 0, 1);
	//glBegin(GL_POLYGON);
	glTranslatef(x, y[0], 0.2);
	glScalef(3,1,.3);
	glutSolidCube(1);
	//glVertex3f(3.5 + x, 0.4 + y[0], 0.1);// Stanga jos
	//glVertex3f(3.5 + x, -0.4 + y[0], 0.1); // Dreapta jos
	//glVertex3f(5.5 + x, -0.4 + y[0], 0.7); // Dreapta sus
	//glVertex3f(5.5 + x, 0.4 + y[0], 0.7);// Stanga sus
	glPopMatrix();
};
