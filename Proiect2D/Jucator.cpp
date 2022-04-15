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
}