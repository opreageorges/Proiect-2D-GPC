#ifndef P2D_COLOANAOFICIALA_CLASS
#define P2D_COLOANAOFICIALA_CLASS
#include "Inamic.h"

class ColoanaOficiala :
    public Inamic
{

public:

    ColoanaOficiala(irrklang::ISoundEngine* audio_engine);
    void draw();
    void misca(double);
};
#endif
