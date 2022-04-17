#include "Bikers.h"
Bikers::Bikers(irrklang::ISoundEngine* audio_engine) : Inamic(audio_engine) {
	
	int y_posibili[2] = {0, 320};
	y[0] = y_posibili[rand()%2];
	y.push_back(160.0);

	coliziune = 200;

	claxon = "Sound/claxon_CO.wav";
	audio_engine->getSoundSource(claxon);

	puncte_generate = 300;
	
	destroyCoord = -250;

	this->r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	this->g = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	this->b = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
}

void Bikers::misca(double viteza) {
	x -= (10 + viteza);
}

void Bikers::draw_motorcycle() {
	
	// motorcycle base
	glColor3f(r, g, b);

	glBegin(GL_POLYGON);
	glVertex2f(28.5, 35);
	glVertex2f(52.5, 24.5);
	glVertex2f(66.5, 26.5);
	glVertex2f(76, 30.5);
	glVertex2f(79.5, 35);
	glVertex2f(80, 38);
	glVertex2f(79.5, 41);
	glVertex2f(76, 45.5);
	glVertex2f(66.5, 49.5);
	glVertex2f(52.5, 51.5);
	glVertex2f(28.5, 41);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex2f(95, 28);
	glVertex2f(99, 25.5);
	glVertex2f(105.5, 27);
	glVertex2f(119, 31.5);
	glVertex2f(124.5, 33.5);
	glVertex2f(127, 36.5);
	glVertex2f(127, 39.5);
	glVertex2f(124.5, 42.5);
	glVertex2f(119, 44.5);
	glVertex2f(105.5, 49);
	glVertex2f(99, 50.5);
	glVertex2f(95, 48);
	glEnd();

	glColor3f(0.9, 0.9, 0.9);

	glBegin(GL_POLYGON);
	glVertex2f(76, 30.5);
	glVertex2f(80.75, 29);
	glVertex2f(85.5, 27.5);
	glVertex2f(95, 28);
	glVertex2f(117, 32.5);
	glVertex2f(122.5, 35);
	glVertex2f(123.5, 38);
	glVertex2f(122.5, 41);
	glVertex2f(117, 43.5);
	glVertex2f(95, 48);
	glVertex2f(85.5, 48.5);
	glVertex2f(76, 45.5);
	glVertex2f(79.5, 41);
	glVertex2f(80, 38);
	glVertex2f(79.5, 35);
	glEnd();

	// motorcycle details
	glColor3f(0.66, 0.66, 0.66);

	// steering base
	glBegin(GL_POLYGON);
	glVertex2f(41, 27.5);
	glVertex2f(55, 27.5);
	glVertex2f(55, 48.5);
	glVertex2f(41, 48.5);
	glVertex2f(35, 38);
	glEnd();

	// pedals
	glBegin(GL_POLYGON);
	glVertex2f(79, 46.5);
	glVertex2f(81, 47);
	glVertex2f(81, 51.5);
	glVertex2f(79, 51.5);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex2f(79, 24.5);
	glVertex2f(81, 24.5);
	glVertex2f(81, 29);
	glVertex2f(79, 29.5);
	glEnd();

	// steering
	glColor3f(0.33, 0.33, 0.33);

	glBegin(GL_POLYGON);
	glVertex2f(55, 16);
	glVertex2f(57, 16.5);
	glVertex2f(50, 30);
	glVertex2f(51, 38);
	glVertex2f(50, 46);
	glVertex2f(57, 59.5);
	glVertex2f(55, 60);
	glVertex2f(46.5, 46);
	glVertex2f(43.5, 42.5);
	glVertex2f(43.5, 33.5);
	glVertex2f(46.5, 30);
	glEnd();
}

void Bikers::draw() {
	glPushMatrix();
	glTranslated(x, y[0] - 50, 0.0);
	this->draw_motorcycle();
	glPopMatrix();

	glPushMatrix();
	glTranslated(x - 130, y[0] - 50, 0.0);
	this->draw_motorcycle();
	glPopMatrix();

	glPushMatrix();
	glTranslated(x, y[1] - 50, 0.0);
	this->draw_motorcycle();
	glPopMatrix();

	glPushMatrix();
	glTranslated(x - 130, y[1] - 50, 0.0);
	this->draw_motorcycle();
	glPopMatrix();

	/*glPushMatrix();
	
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

	glPopMatrix();*/
}