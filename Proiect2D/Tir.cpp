#include "Tir.h"

Tir::Tir(irrklang::ISoundEngine* audio_engine) : Inamic(audio_engine) {
	x += 100;
	destroyCoord = -200;

	coliziune = 135;

	claxon = "Sound/claxon_tir.wav";
	audio_engine->getSoundSource(claxon);

	r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	g = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	b = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
}

void Tir::misca(double viteza) {
	x -= (viteza - 2);
}

void Tir::draw() {
	//glPushMatrix();
	//glTranslated(x-2, y[0], 0.0);
	//
	////fata tirului - gri
	//glColor3f(0.043, 0.039, 0.039);
	//glRecti(-20, -27, 10, 27);


	////mijlocul tirului 
	//glColor3f(r, g, b);
	//glRecti(10, 32, 140, -32);

	////spatele tirului  - gri
	//glColor3f(0.043, 0.039, 0.039);
	//glRecti(140, -27, 150, 27);

	////rotile

	//glColor3f(0, 0, 0);
	//glRecti(15, -32, 35, -38);


	//glColor3f(0, 0, 0);
	//glRecti(40, -32, 60, -38);

	//glColor3f(0, 0, 0);
	//glRecti(90, -32, 128, -38);


	//glColor3f(0, 0, 0);
	//glRecti(15, 38, 35, 32);

	//glColor3f(0, 0, 0);
	//glRecti(40, 38, 60, 32);

	//glColor3f(0, 0, 0);
	//glRecti(90, 38, 128, 32);
	//glPopMatrix();
};
