#ifndef P2D_MASINA_CLASS
#define P2D_MASINA_CLASS
#include "Inamic.h"


class Masina :
    public Inamic
{
public:
    Masina();

    void misca(double);
    void draw();

};

#endif