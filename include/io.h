#ifndef IO_H
#define IO_H

#include <stdbool.h>
#include "SDL/SDL.h"

struct Input {
    bool forward;
    bool back;
    bool left;
    bool right;
    bool exit;
};

void pollInput(struct Input *inputs);


#endif
