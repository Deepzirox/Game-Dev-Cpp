#include "PixelEngine.h"

using namespace eng;
/**
 * PixelEngine - Constructor
 * 
 * Defines all atributes
 */
PixelEngine::PixelEngine()
{
    // the window we will render
    this->wind = NULL;
    // The surface contained by the windo
    this->surf = NULL;

    this->img_surf = NULL;
}
/**
 * Init - Start SDL video Layer
 * 
 * Returns false if can't start SDL
 */
bool PixelEngine::init()
{
    // initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("Fail: %s\n", SDL_GetError());
        return (false);
    }

    printf("SDL started succesfully\n");
    return (true);
}
/**
 * loadMediaWindow - load media window
 * 
 * LOAD MEDIA
 */
bool PixelEngine::loadMediaWindow(char *title, vector<int> axis, vector<int> dimensions, char *flagName)
{
    int w_option;
    size_t obj_len;

    flags_t opt[] = {
        {"fullscreen", 0x00000001},
        {"visible", 0x00000004},
        {"invisible", 0x00000008},
        {"borderless", 0x00000010},
        {"resizable", 0x00000020},
        {"minimized", 0x00000040},
        {"maximized", 0x00000080},
        {"input_grabbed", 0x00000100},
        {"input_focus", 0x00000200},
        {"mouse_focus", 0x00000400},
        {"fullscreen_desktop", (0x00000001 | 0x00001000)},
        {"foreign", 0x00000800}};

    obj_len = LEN(opt);

    for (int i = 0; i < obj_len; i++)
    {
        if (!strcmp(opt[i].name, flagName))
            w_option = opt[i].hex;
    }

    this->wind = SDL_CreateWindow(title, axis[0], axis[1], dimensions[0], dimensions[1], w_option);

    if (!this->wind)
    {
        printf("Failed rendering window : err : %s\n", SDL_GetError());
        return false;
    }

    printf("Window created succesfully\n");
    return (true);
}

bool PixelEngine::image_ssurface(char *path)
{
    if (!path)
        return false;

    this->img_surf = SDL_LoadBMP(path);
    if (!this->img_surf)
    {
        printf("Failed opening BMP file, try check path: %s\n", path);
        return false;
    }
    if (this->img_surf && this->surf)
        SDL_BlitSurface( this->img_surf, NULL, this->surf, NULL );
    else
        return false;

    SDL_UpdateWindowSurface(this->wind);
    printf("%s: LOADED SUCCESFULLY\n", path);
    return true;
}


void PixelEngine::selfWindowSurface()
{
    this->surf = SDL_GetWindowSurface(this->wind);
}

void PixelEngine::otherWindowSurface(SDL_Window *w)
{
    this->surf = SDL_GetWindowSurface(w);
}
void PixelEngine::rect_ssurface(const int c[])
{
    SDL_FillRect(this->surf, NULL, SDL_MapRGBA(this->surf->format, c[0], c[1], c[2], c[3]));
    SDL_UpdateWindowSurface(this->wind);
}
void PixelEngine::destroy()
{
    if (this->wind)
        SDL_DestroyWindow(this->wind);
    if (this->img_surf)
        SDL_FreeSurface(this->img_surf);
    
    this->img_surf = NULL;
    this->wind = NULL;
    this->surf = NULL;

    SDL_Quit();
}
