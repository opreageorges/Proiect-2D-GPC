#include <GL\freeglut.h>

class Jucator
{
private:
	// Coordonatel jucatorului
	double x, y;

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
	void draw();
};