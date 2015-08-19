#include "io.h"

void pollInput(struct Input *inputs)
{
    SDL_Event event;
    while(SDL_PollEvent(&event)) {
       switch(event.type) {
            case SDL_KEYDOWN:
                if (event.key.keysym.sym == SDLK_ESCAPE) {
                    inputs->exit = true; 
                }
                if (event.key.keysym.sym == SDLK_w) {
                    inputs->forward = true;
                }
                if (event.key.keysym.sym == SDLK_a) {
                    inputs->left = true;
                }
                if (event.key.keysym.sym == SDLK_s) {
                    inputs->back = true;
                }
                if (event.key.keysym.sym == SDLK_d) {
                    inputs->right = true;
                }
                break;
            case SDL_KEYUP:
                if (event.key.keysym.sym == SDLK_w) {
                    inputs->forward = false;
                }
                if (event.key.keysym.sym == SDLK_a) {
                    inputs->left = false;
                }
                if (event.key.keysym.sym == SDLK_s) {
                    inputs->back = false;
                }
                if (event.key.keysym.sym == SDLK_d) {
                    inputs->right = false;
                }
                break;
            case SDL_QUIT:
                inputs->exit = true;
                break;
            default:
                break;

        }
    }

}
