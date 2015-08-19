#ifndef DISPLAY_H
#define DISPLAY_H

#define DISPLAY_TITLE  "Raycaster"
#define DISPLAY_WIDTH  1080 
#define DISPLAY_HEIGHT 720 
#define BACKGROUND_COLOUR 0x000000

void initDisplay(void);
void clearDisplay(void);
void flipDisplay(void);
void closeDisplay(void);
void drawRect(int x, int y, int w, int h, int colour);

#endif
