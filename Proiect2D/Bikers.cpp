#include "Bikers.h"
Bikers::Bikers(irrklang::ISoundEngine* audio_engine) : Inamic(audio_engine) {
	
	destroyCoord = 1;

	coliziune = 7;

	claxon = "Sound/claxon_CO.wav";
	audio_engine->getSoundSource(claxon);

	puncte_generate = 300;
	

	this->r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	this->g = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	this->b = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
}

void Bikers::misca(double viteza) {
	x -= viteza;
}


void Bikers::draw() {
	glPushMatrix();

	//glBegin(GL_POLYGON);
	glTranslatef(x, y[0], 0.6);
	glScalef(.02, .02, .02);

	glRotatef(90, 1, 0, 0);
	glRotatef(180, 0, 1, 0);

	l->draw("bikers");
	glRotated(90, 0, 0, 1);
	//glVertex3f(3.5 + x, 0.4 + y[0], 0.1);// Stanga jos
	//glVertex3f(3.5 + x, -0.4 + y[0], 0.1); // Dreapta jos
	//glVertex3f(5.5 + x, -0.4 + y[0], 0.7); // Dreapta sus
	//glVertex3f(5.5 + x, 0.4 + y[0], 0.7);// Stanga sus
	glPopMatrix();
}