#include "Inamic.h"

Inamic::Inamic() {
	x = 800.0;
	y.push_back(160 * (rand() % 3));
	puncte_generate = 100;
	form = rand() % 2;
	color = rand() % 2;
	switch (form)
	{
	case 0: 
		coliziune = 120;
		break;
	case 1: 
		coliziune = 100;
		break;
	default:
		coliziune = 0;
		break;
	}
};

double Inamic::get_x() {
	return x;
};

std::vector<double> Inamic::get_y(){
	return y;
};

int Inamic::getPuncte() {
	return puncte_generate;
};
int Inamic::get_coliziune() {
	return coliziune;
};

int Inamic::getDestroyCoord() {
	return destroyCoord;
}