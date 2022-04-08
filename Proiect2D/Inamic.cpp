#include "Inamic.h"

Inamic::Inamic() {
	x = 800.0;
	y.push_back(160 * (rand() % 3));
	puncte_generate = 100;
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