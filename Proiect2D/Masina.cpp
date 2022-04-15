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

	//spatele masinii - gri
	glColor3f(0.560, 0.560, 0.560);
	glRecti(-20, -27, 10, 27);


	//mijlocul masinii - random color
	glColor3f(r,g,b);
	glRecti(10, 32, 90, -32);

	//fata masinii - gri
	glColor3f(0.560, 0.560, 0.560);
	glRecti(90, -27, 120, 27);

	//roata dreapta spate - negru

	glColor3f(0, 0, 0);
	glRecti(15, -32, 35, -38);

	//roata dreapta fata - negru

	glColor3f(0, 0, 0);
	glRecti(65, -32, 85, -38);

	//roata stanga spate - negru

	glColor3f(0, 0, 0);
	glRecti(15, 38, 35, 32);

	//roata stanga fata - negru
	glColor3f(0, 0, 0);
	glRecti(65, 38, 85, 32);
	glPopMatrix();
};
