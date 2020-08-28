#include "PixelEngine.h"

using namespace eng;


int main()
{
    PixelEngine engine;
    vector<int> axis;
    vector<int> dim;

    // for pre - loading
    char *background = "bmp/back1.bmp";
    SDL_Surface *back = NULL;

    //int x, int y, int w, int h
    dim.push_back(800); // w
    dim.push_back(500); // h
    axis.push_back(SDL_WINDOWPOS_CENTERED); // x
    axis.push_back(SDL_WINDOWPOS_CENTERED); // y

    if (!engine.init())
        exit(-1);
    
    if (!engine.loadMediaWindow("👽👽👽 -> LESSON #4", axis, dim, "visible"))
        exit(-1);

    engine.selfWindowSurface(); // engine gets her own windows surface

    //engine.image_ssurface(background[0]);

    // pre-loaded bmp


    engine.event_loop();

    engine.destroy();

    return (0);
    
}
