#include "Tir.h"

Tir::Tir() {
	x += 100;
	destroyCoord = -200;

	coliziune = 135;

	r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	g = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	b = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
}

void Tir::misca(double viteza) {
	x -= (viteza - 2);
}

void Tir::draw() {
	glPushMatrix();
	glTranslated(x-2, y[0], 0.0);
	
	glColor3f(r, g, b);
	glRecti(-85, -20, 85, 20);
	

	glPopMatrix();
};
