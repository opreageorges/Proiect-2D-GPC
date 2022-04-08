#include "Inamic.h"

Inamic::Inamic() {
	x = 800.0;
	y = 160 * (rand() % 3);
	puncte_generate = 100;
	form = rand() % 2;
	color = rand() % 2;
	switch (form)
	{
	case 0: 
		coliziune = 120;
		break;
	case 1: 
		coliziune = 100;
		break;
	default:
		break;
	}
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
int Inamic::get_coliziune() {
	return coliziune;
};

void Inamic::misca(double viteza) {
	x -= viteza;
};

void Inamic::draw() {
	glPushMatrix();
	glTranslated(x, y, 0.0);


	if (color== 1) {
		glColor3f(0.471, 0.667, 0.949);
	}
	else {
		glColor3f(0.4466, 0.0622, 0.5311);
	}
	if (form== 1) {
		glRecti(-45, -10, 45, 10);
	}
	else {
		glRecti(-65, -10, 65, 10);
	}

	glPopMatrix();
};