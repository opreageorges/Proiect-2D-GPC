#include "Ambulanta.h"
Ambulanta::Ambulanta(irrklang::ISoundEngine* audio_engine) : Inamic(audio_engine) {
	coliziune = 7;

	claxon = "Sound/claxon_ambulanta.wav";
	audio_engine->getSoundSource(claxon);

	puncte_generate = 150;
	destroyCoord = 1;
}

void Ambulanta::misca(double viteza) {
	x -= viteza;
}


void Ambulanta::draw() {
	glPushMatrix();

	//glBegin(GL_POLYGON);
	glTranslatef(x, y[0], 0.6);
	glScalef(.5, .5, .5);

	glRotatef(90, 1, 0, 0);
	glRotatef(90, 0, 1, 0);

	l->draw("ambulanta", glm::vec3(), glm::vec3(.5, .5, .5), glm::vec4(90, 1, 0, 0));
	glRotated(90, 0, 0, 1);
	//glVertex3f(3.5 + x, 0.4 + y[0], 0.1);// Stanga jos
	//glVertex3f(3.5 + x, -0.4 + y[0], 0.1); // Dreapta jos
	//glVertex3f(5.5 + x, -0.4 + y[0], 0.7); // Dreapta sus
	//glVertex3f(5.5 + x, 0.4 + y[0], 0.7);// Stanga sus
	glPopMatrix();

}
