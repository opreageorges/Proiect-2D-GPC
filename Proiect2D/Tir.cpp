#include "Tir.h"

Tir::Tir(irrklang::ISoundEngine* audio_engine) : Inamic(audio_engine) {
	destroyCoord = 1;

	coliziune = 7;

	claxon = "Sound/claxon_tir.wav";
	audio_engine->getSoundSource(claxon);

	r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	g = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	b = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
}

void Tir::misca(double viteza) {
	x -= viteza;
}

void Tir::draw() {
	glPushMatrix();

	//glBegin(GL_POLYGON);
	glTranslatef(x, y[0], 0.6);
	glScalef(.01, .01, .01);

	glRotatef(90, 1, 0, 0);
	glRotatef(90, 0, 1, 0);

	l->draw("tir");
	glRotated(90, 0, 0, 1);
	//glVertex3f(3.5 + x, 0.4 + y[0], 0.1);// Stanga jos
	//glVertex3f(3.5 + x, -0.4 + y[0], 0.1); // Dreapta jos
	//glVertex3f(5.5 + x, -0.4 + y[0], 0.7); // Dreapta sus
	//glVertex3f(5.5 + x, 0.4 + y[0], 0.7);// Stanga sus
	glPopMatrix();
};
