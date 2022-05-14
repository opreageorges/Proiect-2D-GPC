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
	if (x < 100)
	{
		x += 1;
	}
}

void Jucator::miscajos(void)
{
	if (x > -12)
	{
		x -= 1;
	}

}

void Jucator::miscaDreapta(void)
{
	if (y > -10)
	{
		y -= 10;
	}
}

void Jucator::miscaStanga(void)
{

	if (y < 10)
	{
		y += 10;
	}
}

void Jucator::draw() {
	glPushMatrix();
	glColor3f(1.0f, 0.0f, 0.0f);
	glTranslatef(5+x, y, 0.2);
	glScalef(3, 1, 0.3);
	glutSolidCube(1);
	glPopMatrix();
}