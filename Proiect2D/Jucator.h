#include <GL\freeglut.h>

class Jucator
{
private:
	double x, y;

public:
	Jucator();

	double get_x();
	double get_y();

	void miscasus(void);
	void miscajos(void);
	void miscaDreapta(void);
	void miscaStanga(void);

	void draw();
};