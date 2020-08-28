#ifndef ENGINE
#define ENGINE

#include <cstdio>
#include <vector>
#include <SDL2/SDL.h>

const int GREEN[] = {0, 177, 106, 1};
const int RED[] = {242, 38, 19, 1};
const int BLUE[] = {44, 130, 201, 1};

#define LEN(x) (sizeof(x) / sizeof(x[0]))

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
        void selfWindowSurface();
        void otherWindowSurface(SDL_Window *w);
        void rect_ssurface(const int c[]);
        /** The images we're going to be dealing with here are the screen image (what you see inside of the window) and the image we'll be loading from a file. **/
        bool image_ssurface(char *path);
        void event_loop();
        /** free SDL **/
        void destroy();

    private:
        SDL_Window *wind;
        SDL_Surface *surf;
        SDL_Surface *img_surf;
    };
} // namespace eng  

#endif /** Engine modules **/
