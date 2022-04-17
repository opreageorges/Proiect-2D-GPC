#ifndef P2D_Bikers_CLASS
#define P2D_Bikers_CLASS
#include "Inamic.h"

class Bikers :
    public Inamic
{

public:

    Bikers(irrklang::ISoundEngine* audio_engine);
    void draw();
    void draw_motorcycle();
    void misca(double);

private:
    float r, g, b;
};
#endif
