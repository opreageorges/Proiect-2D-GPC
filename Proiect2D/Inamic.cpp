#include "Inamic.h"

Inamic::Inamic(irrklang::ISoundEngine* audio_engine) {
	x = 140.0;
	int y_posibili[3] = { 10, -10, 0 };
	y.push_back(y_posibili[rand() % 3]);
	puncte_generate = 100;
	claxon = "Sound/claxon_default.wav";
	audio_engine->getSoundSource(claxon);
	a_claxonat = false;
	coliziune = 0;
	destroyCoord = 0;
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

const char* Inamic::get_claxon() {
	a_claxonat = true;
	return this->claxon;
}
bool Inamic::get_a_claxonat() {
	return a_claxonat;
}