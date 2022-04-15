#ifndef P2D_AMBULANTA_H
#define P2D_AMBULANTA_H
#include "Inamic.h"
class Ambulanta :
    public Inamic
{
private:
    double rotatie = 0.0;

public:
    Ambulanta(irrklang::ISoundEngine* audio_engine);
    void misca(double);
    void draw();
};

#endif
