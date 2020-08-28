#include "PixelEngine.h"

using namespace eng;


int main()
{
    PixelEngine engine;
    vector<int> axis;
    vector<int> dim;
    char *background[] = {
        "bmp/back0.bmp",
    };
    //int x, int y, int w, int h
    dim.push_back(800); // w
    dim.push_back(500); // h
    axis.push_back(SDL_WINDOWPOS_CENTERED); // x
    axis.push_back(SDL_WINDOWPOS_CENTERED); // y

    if (!engine.init())
        exit(-1);
    
    if (!engine.loadMediaWindow("Ventana uno", axis, dim, "visible"))
        exit(-1);

    engine.selfWindowSurface();

    engine.image_ssurface(background[0]);

    engine.event_loop();


    engine.destroy();

    return (0);
    
}
