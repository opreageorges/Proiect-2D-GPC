#include "ColoanaOficiala.h"
ColoanaOficiala::ColoanaOficiala() {
	int y_posibili[2] = {0, 320};
	y[0] = y_posibili[rand()%2];
	coliziune = 200;
	puncte_generate = 300;
	y.push_back(160.0);

	destroyCoord = -250;
}

void ColoanaOficiala::misca(double viteza) {
	x -= (10 + viteza);
}

void ColoanaOficiala::draw() {
	glPushMatrix();
	
	glTranslated(x + 120, y[0], 0.0);
	glColor3f(0, 0, 0);
	glRecti(-45, -10, 45, 10);
	glPopMatrix();

	glPushMatrix();


	glPushMatrix();
	
	glTranslated(x, y[0], 0.0);
	glColor3f(1, 1, 1);
	glRecti(-45, -10, 65, 10);
	
	glPopMatrix();


	glPushMatrix();

	glTranslated(x - 100, y[0], 0.0);
	glColor3f(0, 0, 0);
	glRecti(-45, -10, 45, 10);
	
	glPopMatrix();
	

	glPushMatrix();

	glTranslated(x + 120, y[1], 0.0);
	glColor3f(0, 0, 0);
	glRecti(-45, -10, 45, 10);
	glPopMatrix();

	glPushMatrix();


	glPushMatrix();

	glTranslated(x+10, y[1], 0.0);
	glColor3f(0, 0, 0);
	glRecti(-45, -10, 45, 10);

	glPopMatrix();


	glPushMatrix();

	glTranslated(x - 100, y[1], 0.0);
	glColor3f(0, 0, 0);
	glRecti(-45, -10, 45, 10);

	glPopMatrix();
}