#include "SDL/SDL.h"

#include "display.h"

static struct SDL_Surface *screen;

void initDisplay(void)
{
    SDL_Init(SDL_INIT_VIDEO);
    screen = SDL_SetVideoMode(DISPLAY_WIDTH, DISPLAY_HEIGHT, 0, SDL_HWPALETTE); 
    SDL_WM_SetCaption(DISPLAY_TITLE, NULL);
}

void clearDisplay(void)
{
    SDL_FillRect(screen, NULL, BACKGROUND_COLOUR);
}

void flipDisplay(void)
{
    SDL_Flip(screen);
    SDL_Delay(50);
}

void closeDisplay(void)
{
    SDL_Quit();
}

void drawRect(int x, int y, int w, int h, int colour)
{
   struct SDL_Rect rect; 
   rect.x = x;
   rect.y = y;
   rect.w = w;
   rect.h = h;
   SDL_FillRect(screen, &rect, colour);
}

