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

	glColor3f(0.996f, 0.365f, 0.149f);
	glRecti(-45, -15, 45, 15);


	glPopMatrix();
	glPopMatrix();
}