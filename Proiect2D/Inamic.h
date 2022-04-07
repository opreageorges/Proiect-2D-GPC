#include <iostream>
#include <GL\freeglut.h>

class Inamic
{
private:
	double x, y;
	int puncte_generate;

public:
	Inamic();

	double get_x();
	double get_y();
	int getPuncte();
	void misca(double);

	void draw();
	
};

