#ifndef P2D_INAMIC_H
#define P2D_INAMIC_H
#include <iostream>
#include <vector>
#include <GL\freeglut.h>
#include <irrKlang.h>
#include "Loader.h"

class Inamic
{
protected:
	Loader* l;
	// Coordonatele inamicului
	double x;
	std::vector<double> y;

	// Coordonatele din afara ecranului la care inamicul este distrus
	int destroyCoord;

	// Fisierul audio cu sunetul de claxon al masini
	const char* claxon;

	// Pentru a opri claxonul la infinit
	bool a_claxonat;

	// Marimea liniei de coliziune (cat e intre centrul masinii si centrul inamicului)
	int coliziune;

	// Nr de puncte generat
	int puncte_generate;

public:
	Inamic(irrklang::ISoundEngine* audio_engine);

	// Functii pentru aflarea locatiei
	double get_x();
	std::vector<double> get_y();

	// Returneaza nr de puncte pentru evitarea inamicului
	int getPuncte();

	// Functia care returneaza claxonul
	const char* get_claxon();

	// Functia care returneaza marja de coliziune (cat e intre centrul masinii si centrul inamicului)
	int get_coliziune();

	int getDestroyCoord();

	// Functie de miscare
	void virtual misca(double) = 0;

	// Functia de desenare
	void virtual draw() = 0;
	
	bool get_a_claxonat();

	void set_Loader(Loader* l);
};
#endif
