#ifndef P2D_JUCATOR_H
#define P2D_JUCATOR_H
#include <GL\freeglut.h>
#include <cmath>
#include"Loader.h"

class Jucator
{
private:
	// Coordonatel jucatorului
	double x, y;
	Loader* l;
public:
	Jucator();

	// Functii pentru aflarea locatiei
	double get_x();
	double get_y();

	// Functiile de deplasare
	void miscasus(void);
	void miscajos(void);
	void miscaDreapta(void);
	void miscaStanga(void);

	// Functia de desenare
	void draw(int alege);

	void set_Loader(Loader* l);
};
#endif