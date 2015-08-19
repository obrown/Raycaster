#ifndef RAYCASTER_H
#define RAYCASTER_H

#define MAP_WIDTH  24
#define MAP_HEIGHT 24

#define BLOCK_SIZE 64

#define MOVE_SPEED 20 
#define TURN_SPEED 0.25

#define FOV 1.04719755128

#define PI_TWO 1.57079632679
#define PI     3.14159265358 
#define TWO_PI 6.28318530718 

#define COL_RED   0xFF0000
#define COL_GREEN 0x00FF00
 
struct Player {
    int x;
    int y;
    double a;    
};

struct Ray {
    double x;
    double y;
    double xStep;
    double yStep;
};

#endif
