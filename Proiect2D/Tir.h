#ifndef P2D_TIR_H
#define P2D_TIR_H

#include "Inamic.h"
class Tir :
    public Inamic
{
private:
    float r, g, b;
public:
    Tir();

    void misca(double);
    void draw();

};

#endif