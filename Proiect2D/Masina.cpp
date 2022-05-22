#include "Masina.h"


Masina::Masina(irrklang::ISoundEngine* audio_engine) : Inamic(audio_engine) {
	destroyCoord = 1;

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

	glTranslatef(x, y[0] - 0.5, 0.6);
	glScalef(.5, .5, .5);

	glRotatef(90, 1, 0, 0);
	glRotatef(-90, 0, 1, 0);
	l->draw("logan");
	
	glPopMatrix();
};
