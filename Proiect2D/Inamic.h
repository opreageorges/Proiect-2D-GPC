#include <iostream>
#include <GL\freeglut.h>

class Inamic
{
private:
	// Coordonatele inamicului
	double x, y;
	int form, color;
	int coliziune;

	// Nr de puncte generat
	int puncte_generate;

public:
	Inamic();

	// Functii pentru aflarea locatiei
	double get_x();
	double get_y();

	// Returneaza nr de puncte pentru evitarea inamicului
	int getPuncte();

	int get_coliziune();

	// Functie de miscare
	void misca(double);

	// Functia de desenare
	void draw();
	
};

