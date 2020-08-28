#include "PixelEngine.h"

using namespace eng;


SDL_Surface *loader_bmp_Surf(char *path)
{
    if (!path)
        return (NULL);

    SDL_Surface *new_surface = SDL_LoadBMP(path);
    if (!new_surface)
        return (NULL);
    
    return (new_surface);
}
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

    printf("-> SDL inicio Correctamente\n");
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
        printf("Fallo al renderizar la ventana : err : %s\n", SDL_GetError());
        return false;
    }

    this->keypress_img[KEY_UP] = loader_bmp_Surf("bmp/back1.bmp");
    this->keypress_img[KEY_DOWN] = loader_bmp_Surf("bmp/back2.bmp");
    this->keypress_img[KEY_LEFT] = loader_bmp_Surf("bmp/back4.bmp");
    this->keypress_img[KEY_RIGHT] = loader_bmp_Surf("bmp/back0.bmp");
    this->keypress_img[KEY_DEFAULT] = loader_bmp_Surf("bmp/back5.bmp");
    if (!this->keypress_img[KEY_UP]    ||
        !this->keypress_img[KEY_DOWN]  ||
        !this->keypress_img[KEY_RIGHT] ||
        !this->keypress_img[KEY_LEFT]  ||
        !this->keypress_img[KEY_DEFAULT])
            return (false);

    printf("ventana creada satisfactoriamente\n");
    return (true);
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
    this->reload();
}

void PixelEngine::reload()
{
    SDL_UpdateWindowSurface(this->wind);
}

void PixelEngine::blit_reload(SDL_Surface *src, SDL_Surface *dst)
{
    this->reload();
    SDL_BlitSurface(src, NULL, dst, NULL);
}

void PixelEngine::event_loop()
{
    //Main loop flag
    bool quit = false;
    //Event handler
    SDL_Event e;

    this->img_surf = this->keypress_img[ KEY_DEFAULT ];
    this->blit_reload(img_surf, this->surf);

    while (!quit)
    {
        //Handle events on queue
        while (SDL_PollEvent(&e) != 0)
        {
            //User requests quit
            if (e.type == SDL_QUIT)
            {
                quit = true;
            }
            else if( e.type == SDL_KEYDOWN )
            {
                switch (e.key.keysym.scancode)
                {
                case SDL_SCANCODE_W:
                    this->img_surf = this->keypress_img[ KEY_UP ];
                    break;
                case SDL_SCANCODE_S:
                    this->img_surf = this->keypress_img[ KEY_DOWN ];
                    break;
                case SDL_SCANCODE_D:
                    this->img_surf = this->keypress_img[ KEY_RIGHT ];
                    break;
                case SDL_SCANCODE_A:
                    this->img_surf = this->keypress_img[ KEY_LEFT ];
                    break;
                default:
                    this->img_surf = this->keypress_img[ KEY_DEFAULT ];
                    break;
                }
            }
        }
        this->blit_reload(img_surf, this->surf);
    }
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

    printf("Salida exitosa, bye!\n");
}






/* bool PixelEngine::image_ssurface(char *path)
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
        SDL_BlitSurface(this->img_surf, NULL, this->surf, NULL);
    else
        return false;

    SDL_UpdateWindowSurface(this->wind);
    printf("%s: Cargada exitosamente\n", path);
    return true;
} */
