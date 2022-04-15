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
	if (y < 320)
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
	glTranslated(x, y, 0.0);

	//spatele masinii - verde
	glColor3f(0.584, 0.015, 0.015);
	glRecti(-20, -27, 10, 27);


	//mijlocul masinii - rosu
	glColor3f(1, 0.039, 0.039);
	glRecti(10, 32, 90, -32);

	//fata masinii - verde
	glColor3f(0.584, 0.015, 0.015);
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
	
	// Sigla
	glPushMatrix();

	glColor3f(1.0, 0.0, 1.0);
	glScaled(0.1, 0.1, 1.0);
	glTranslated(x * 10 + 106 * 10, y * 10, 0);

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