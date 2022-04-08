#include "Masina.h"
Masina::Masina() {
	destroyCoord = -150;
}

void Masina::misca(double viteza) {
	x -= viteza;
}

void Masina::draw() {
	glPushMatrix();
	glTranslated(x, y[0], 0.0);


	if (color == 1) {
		glColor3f(0.471f, 0.667f, 0.949f);
	}
	else {
		glColor3f(0.4466f, 0.0622f, 0.5311f);
	}
	if (form == 1) {
		glRecti(-45, -10, 45, 10);
	}
	else {
		glRecti(-65, -10, 65, 10);
	}

	glPopMatrix();
};
