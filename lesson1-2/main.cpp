#include "PixelEngine.h"

using namespace eng;


int main()
{
    PixelEngine engine;
    vector<int> axis;
    vector<int> dim;
    char *background[] = {
        "bmp/back1.bmp", 
        "bmp/back3.bmp", 
        "bmp/back4.bmp", 
        "bmp/back5.bmp"
    };
    //int x, int y, int w, int h
    dim.push_back(960); // w
    dim.push_back(600); // h
    axis.push_back(1100); // x
    axis.push_back(1100); // y

    if (!engine.init())
        exit(-1);
    
    if (!engine.loadMediaWindow("Ventana uno", axis, dim, "resizable"))
        exit(-1);

    engine.selfWindowSurface();

    for (int i = 0; i < LEN(background); i++)
    {
        engine.image_ssurface(background[i]);
        SDL_Delay(1000);
    }


    //engine.rect_ssurface(GREEN);

    SDL_Delay(3000);

    engine.destroy();

    return (0);
    
}
