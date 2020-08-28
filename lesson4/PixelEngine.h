#ifndef ENGINE
#define ENGINE

#include <cstdio>
#include <vector>
#include <SDL2/SDL.h>

#define LEN(x) (sizeof(x) / sizeof(x[0]))

const int GREEN[] = {0, 177, 106, 1};
const int RED[] = {242, 38, 19, 1};
const int BLUE[] = {44, 130, 201, 1};

enum KeyPress {
    KEY_UP,
    KEY_DOWN,
    KEY_LEFT,
    KEY_RIGHT,
    KEY_DEFAULT,
    KEY_TOTAL
};

SDL_Surface *loader_bmp_Surf(char *path);

typedef struct FLAGS
{
    char *name;
    int hex;

} flags_t;

using namespace std;

namespace eng
{
    
    class PixelEngine
    {
    public:
        PixelEngine();
        bool init();
        bool loadMediaWindow(char *title, vector <int> axis, vector <int> dimensions, char *flagName);
        void reload();
        void blit_reload(SDL_Surface *src, SDL_Surface *dst);
        void selfWindowSurface();
        void otherWindowSurface(SDL_Window *w);
        SDL_Surface *get_current_surface() { return (this->surf) ;};
        /** Bckground color **/
        void rect_ssurface(const int c[]);
        /** The images we're going to be dealing with here are the screen image (what you see inside of the window) and the image we'll be loading from a file. **/
        //bool image_ssurface(char *path);  deprecated 
        void event_loop();
        /** free SDL **/
        void destroy();

    private:
        // Window
        SDL_Window *wind;
        // surface of the window
        SDL_Surface *surf;
        // current img surface
        SDL_Surface *img_surf;
        // need to allocate the total of keys
        SDL_Surface *keypress_img[ KEY_TOTAL ];
    };
} // namespace eng  

#endif /** Engine modules **/
