#ifndef UTILS_H
#define UTILS_H

#include <SDL2/SDL_rect.h>

void throwError(const char* msg);
SDL_Rect calculateRotatedRect(int x, int y, int width, int height, double angle, int centerX, int centerY);

#endif
