#ifndef P2D_MASINA_CLASS
#define P2D_MASINA_CLASS
#include "Inamic.h"
#include <mmsystem.h>


class Masina :
    public Inamic
{
private:
    float r, g, b;
    
public:
    Masina(irrklang::ISoundEngine* audio_engine);

    void misca(double);
    void draw();
    
};

#endif