#ifndef P2D_INAMIC_H
#define P2D_INAMIC_H
#include <iostream>
#include <vector>
#include <GL\freeglut.h>

class Inamic
{
protected:
	// Coordonatele inamicului
	double x;
	std::vector<double> y;
	int destroyCoord;
	int coliziune;

	// Nr de puncte generat
	int puncte_generate;

public:
	Inamic();

	// Functii pentru aflarea locatiei
	double get_x();
	std::vector<double> get_y();

	// Returneaza nr de puncte pentru evitarea inamicului
	int getPuncte();

	int get_coliziune();

	int getDestroyCoord();

	// Functie de miscare
	void virtual misca(double) = 0;

	// Functia de desenare
	void virtual draw() = 0;
	
};
#endif
