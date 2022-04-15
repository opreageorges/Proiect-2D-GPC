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
	glTranslated(x, y[0], 0.0);

	glColor3f(r, g, b);
	glRecti(-45, -10, 45, 10);

	glPopMatrix();
};
