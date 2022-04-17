#include "Jucator.h"

Jucator::Jucator() {
	x = 0.0;
	y = 0.0;
}

double Jucator::get_y() {
	return y;
}

double Jucator::get_x() {
	return x;
}

void Jucator::miscasus(void)
{
	if (y < 290)
	{
		y += 160;
	}
}

void Jucator::miscajos(void)
{
	if (y > 0)
	{
		y -= 160;
	}

}

void Jucator::miscaDreapta(void)
{
	if (x < 600)
	{
		x += 10;
	}
}

void Jucator::miscaStanga(void)
{

	if (x > -20)
	{
		x -= 10;
	}
}

void Jucator::draw() {
	glPushMatrix();
	glTranslated(x, y - 30.0, 0.0);
	glScaled(1.25, 1.25, 0.0);

	// car base
	glColor3f(0.84f, 0.11f, 0.18f);

	glBegin(GL_POLYGON);
	glVertex2f(0, 29);
	glVertex2f(1, 5);
	glVertex2f(15, 3);
	glVertex2f(35, 3);
	glVertex2f(54.5, 5.5);
	glVertex2f(85, 4);
	glVertex2f(106.5, 4);
	glVertex2f(118, 7);
	glVertex2f(122, 9.5);
	glVertex2f(125, 19.5);
	glVertex2f(125, 38.5);
	glVertex2f(122, 48.5);
	glVertex2f(118, 51);
	glVertex2f(106.5, 54);
	glVertex2f(85, 54);
	glVertex2f(54.5, 52.5);
	glVertex2f(35, 55);
	glVertex2f(15, 55);
	glVertex2f(1, 53);

	glEnd();

	// car top
	glColor3f(1.0f, 0.11f, 0.18f);

	glBegin(GL_POLYGON);
	glVertex2f(37, 15.5);
	glVertex2f(65, 15.5);
	glVertex2f(65, 42.5);
	glVertex2f(37, 42.5);

	glEnd();

	// car lights
		// right
	glBegin(GL_POLYGON);
	glVertex2f(114, 40);
	glVertex2f(122.5, 40);
	glVertex2f(120, 48.5);
	glVertex2f(112.5, 48.5);

	glEnd();

		// left
	glBegin(GL_POLYGON);
	glVertex2f(114, 10);
	glVertex2f(120.5, 10);
	glVertex2f(123, 18.5);
	glVertex2f(114.5, 18.5);

	glEnd();

	// car windows
	glColor3f(0.0f, 0.0f, 0.0f);

	// front
	glBegin(GL_POLYGON);
	glVertex2f(64.5, 15.5);
	glVertex2f(82.5, 9);
	glVertex2f(89.5, 18);
	glVertex2f(90.5, 29);
	glVertex2f(89.5, 40);
	glVertex2f(82.5, 49);
	glVertex2f(64.5, 42.5);
	glEnd();

	// rear
	glBegin(GL_POLYGON);
	glVertex2f(10, 14);
	glVertex2f(37, 15);
	glVertex2f(37, 42);
	glVertex2f(10, 44);
	glEnd();

	// left
	glBegin(GL_POLYGON);
	glVertex2f(35, 43.5);
	glVertex2f(60.5, 43.5);
	glVertex2f(77.5, 48.5);
	glVertex2f(77.5, 49.5);
	glVertex2f(35, 49.5);
	glEnd();

	// right
	glBegin(GL_POLYGON);
	glVertex2f(35, 8.5);
	glVertex2f(77.5, 8.5);
	glVertex2f(77.5, 9.5);
	glVertex2f(60.5, 14.5);
	glVertex2f(35, 14.5);
	glEnd();


	// tiers
	
	// rear right
	glBegin(GL_POLYGON);
	glVertex2f(16, 0);
	glVertex2f(34, 0);
	glVertex2f(34, 3);
	glVertex2f(16, 3);
	glEnd();

	// rear left
	glBegin(GL_POLYGON);
	glVertex2f(16, 55);
	glVertex2f(34, 55);
	glVertex2f(34, 58);
	glVertex2f(16, 58);
	glEnd();

	// front right
	glBegin(GL_POLYGON);
	glVertex2f(86, 1);
	glVertex2f(105, 1);
	glVertex2f(105, 4);
	glVertex2f(86, 4);
	glEnd();

	// front left
	glBegin(GL_POLYGON);
	glVertex2f(86, 54);
	glVertex2f(105, 54);
	glVertex2f(105, 57);
	glVertex2f(86, 57);
	glEnd();

	glPopMatrix();

	// Sigla
	glPushMatrix();

	glColor3f(1.0, 0.0, 1.0);
	glTranslated(x + 145, y + 6, 0);
	glScaled(0.075, 0.075, 1.0);

	double pi = 3.14159265359;
	double razaEmblemei = 100.0;
	double razaTriunghiurilor = 90.0;
	int nr_de_puncte = 100;
	float unghi;

	glBegin(GL_TRIANGLE_FAN);
	glColor3f(1.0f, 1.0f, 1.0f);  
	glVertex2f(0.0f, 0.0f);       
	for (int i = 0; i <= nr_de_puncte; i++) { 
		unghi = i * 2.0f * pi / nr_de_puncte; 
		glVertex2f(cos(unghi) * razaEmblemei, sin(unghi) * razaEmblemei);
	}
	glEnd();

	glBegin(GL_TRIANGLE_FAN);
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex2f(0.0f, 0.0f);
	for (int i = 0; i <= nr_de_puncte; i++) {
		unghi = i * 2.0f * pi / nr_de_puncte / 4;
		glVertex2f(cos(unghi) * razaTriunghiurilor, sin(unghi) * razaTriunghiurilor);
	}
	glEnd();

	glBegin(GL_TRIANGLE_FAN);
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex2f(0.0f, 0.0f);
	for (int i = 0; i <= nr_de_puncte; i++) {
		unghi = i * -4.0f * pi / nr_de_puncte / 4;
		glVertex2f(sin(unghi) * razaTriunghiurilor, cos(unghi) * razaTriunghiurilor);
	}
	glEnd();

	glBegin(GL_TRIANGLE_FAN);
	glColor3f(1.0f, 1.0f, 1.0f);  
	glVertex2f(0.0f, 0.0f);
	for (int i = 0; i <= nr_de_puncte; i++) {
		unghi = i * -4.0f * pi / nr_de_puncte / 8;
		glVertex2f(sin(unghi) * razaTriunghiurilor, cos(unghi) * razaTriunghiurilor);
	}
	glEnd();

	glPopMatrix();
}