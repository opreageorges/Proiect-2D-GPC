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

void Jucator::set_Loader(Loader *l) {
	this->l = l;
}

void Jucator::draw() {
	glPushMatrix();
	glTranslatef(5 + x, y, 0.6);
	glScalef(.5, .5, .5);
	
	glRotatef(90, 1, 0, 0);
	glRotatef(90, 0, 1, 0);
	
	l->draw("logan");
	glRotated(90, 0, 0, 1);
	glPopMatrix();
}