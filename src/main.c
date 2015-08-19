#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#include "display.h"
#include "io.h"
#include "main.h"

int map[MAP_HEIGHT][MAP_WIDTH]=
{
      {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
      {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
      {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
      {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
      {1,0,0,0,0,0,1,1,1,1,1,0,0,0,0,1,0,1,0,1,0,0,0,1},
      {1,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,1},
      {1,0,0,0,0,0,1,0,0,0,1,0,0,0,0,1,0,0,0,1,0,0,0,1},
      {1,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1},
      {1,0,0,0,0,0,1,1,0,1,1,0,0,0,0,1,0,1,0,1,0,0,0,1},
      {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
      {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
      {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1},
      {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
      {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
      {1,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,1},
      {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
      {1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1},
      {1,1,0,1,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,1},
      {1,1,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
      {1,1,0,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
      {1,1,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1},
      {1,1,0,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,1},
      {1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
      {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

void wrap(double *angle);
void drawWalls(struct Player *player);

double findHorizontalIntersection(double castAngle, struct Player *player);
double findVerticalIntersection(double castAngle, struct Player *player);

double distance(int x1, int y1, int x2, int y2);

struct Ray *trace(struct Ray *ray);

int main(int argc, char* args[])
{
    initDisplay();
    
    struct Player player = {128, 128, (PI / 180) * 60};
    struct Input input = {false, false, false, false, false};
    

    while (!input.exit) {
        pollInput(&input);

        if (input.forward) {
            player.x += cos(player.a) * MOVE_SPEED;
            player.y -= sin(player.a) * MOVE_SPEED; 
        }
        if (input.left) {
            player.a -= TURN_SPEED;
            wrap(&player.a);
        }
        if (input.back) {
            player.x -= cos(player.a) * MOVE_SPEED;
            player.y += sin(player.a) * MOVE_SPEED; 
        }
        if (input.right) {
            player.a += TURN_SPEED;
            wrap(&player.a);
        }

        clearDisplay(); 
        drawWalls(&player);
        flipDisplay();
    }

    closeDisplay(); 

    return 0;
}


void wrap(double *angle) {
    if (*angle > TWO_PI) {
        *angle -= TWO_PI;
    } else if (*angle < 0) {
        *angle += TWO_PI;
    }
}

void drawWalls(struct Player *player)
{
    int column = 0;
    double degreesPerColumn = FOV / DISPLAY_WIDTH;
    double start = player->a - FOV / 2;

    while (column < DISPLAY_WIDTH) {
        double castAngle = start + degreesPerColumn * column; 
        double alpha = castAngle - player->a;
        wrap(&castAngle);

        double hDist, vDist;
        hDist = vDist = -1;

        hDist = findHorizontalIntersection(castAngle, player);
        vDist = findVerticalIntersection(castAngle, player);

        double distToWall;
        unsigned int colour;
        if (vDist < hDist) {
            distToWall = vDist; 
            colour = COL_GREEN;
        } else {
            distToWall = hDist;
            colour = COL_RED;
        }

        distToWall *= cos(alpha); 

        int wallSize = (BLOCK_SIZE / distToWall) * DISPLAY_HEIGHT;
        int y = (DISPLAY_HEIGHT / 2) - (wallSize / 2);

        drawRect(column, y, 1, wallSize, colour);

        column++;
    }

}

double findHorizontalIntersection(double castAngle, struct Player *player)
{
    struct Ray hRay;
    
    if (castAngle < PI) {
        hRay.y = floor(player->y / BLOCK_SIZE) * BLOCK_SIZE; 
        hRay.yStep  = -BLOCK_SIZE;
        hRay.xStep  = BLOCK_SIZE / tan(castAngle);
        hRay.x = player->x + (fabs(player->y-hRay.y) / tan(castAngle));
        hRay.y--;
    } else {
        hRay.y = floor(player->y / BLOCK_SIZE) * BLOCK_SIZE + BLOCK_SIZE;
        hRay.yStep  = BLOCK_SIZE;
        hRay.xStep  = BLOCK_SIZE / tan(-castAngle);
        hRay.x = player->x + (fabs(player->y-hRay.y) / tan(-castAngle));
    }

    if (trace(&hRay) != NULL) {
        return distance(player->x, player->y, hRay.x, round(hRay.y));
    } else {
        return 10000000000;
    }
}

double findVerticalIntersection(double castAngle, struct Player *player)
{
    struct Ray vRay;

    if (castAngle >= PI_TWO && castAngle < 3 * PI_TWO) {
        vRay.x = floor(player->x / BLOCK_SIZE) * BLOCK_SIZE;
        vRay.xStep = -BLOCK_SIZE;
        vRay.y = player->y + (fabs(vRay.x-player->x) * tan(castAngle));
        vRay.yStep = BLOCK_SIZE * tan(castAngle);
        vRay.x--;
    } else {
        vRay.x = floor(player->x / BLOCK_SIZE) * BLOCK_SIZE + BLOCK_SIZE;
        vRay.xStep = BLOCK_SIZE;
        vRay.y = player->y + (fabs(vRay.x-player->x) * tan(-castAngle));
        vRay.yStep = BLOCK_SIZE * tan(-castAngle);
    }

    if (trace(&vRay) != NULL) {
        return distance(player->x, player->y, vRay.x, vRay.y);
    } else {
        return 10000000000;
    }
}


struct Ray *trace(struct Ray *ray)
{
    while (ray->x <= BLOCK_SIZE * MAP_WIDTH && ray->x >= 0
                && ray->y <= BLOCK_SIZE * MAP_HEIGHT && ray->y >= 0) {

        int gX = ray->x / BLOCK_SIZE;
        int gY = ray->y / BLOCK_SIZE;

        if (map[gY][gX] > 0) {
            return ray;
        }

        ray->x += ray->xStep;
        ray->y += ray->yStep;
    }

    return NULL;
}

double distance(int x1, int y1, int x2, int y2)
{
    int dX = x2 - x1;
    int dY = y2 - y1;
    return sqrt((dX * dX) + (dY * dY));
}
