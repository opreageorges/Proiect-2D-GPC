#include "Inamic.h"

Inamic::Inamic() {
	x = 800.0;
	y = 160 * (rand() % 3);
	puncte_generate = 100;
};

double Inamic::get_x() {
	return x;
};

double Inamic::get_y(){
	return y;
};

int Inamic::getPuncte() {
	return puncte_generate;
};

void Inamic::misca(double viteza) {
	x -= viteza;
};

void Inamic::draw() {
	glPushMatrix();
	glTranslated(x, y, 0.0);

	glColor3f(0.471, 0.667, 0.949);
	glRecti(-45, -15, 45, 15);

	glPopMatrix();
};