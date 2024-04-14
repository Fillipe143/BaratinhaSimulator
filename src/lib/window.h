#ifndef WINDOW_H
#define WINDOW_H
#include <SDL2/SDL_events.h>
#include <cstdint>
#include <vector>

class Window {
    public:
        Window(const char* title, int width, int height);
        SDL_Event* poolEvent();
        
        void setColor(uint8_t r, uint8_t g, uint8_t b);
        void clear();
        void present();
        
        void drawPoint(int x, int y);
        void drawLine(int x1, int y1, int x2, int y2);
        void drawRay(int x, int y, double angle, int length);
        void drawThickLine(int x1, int y1, int x2, int y2, int thickness);
        
        void drawRect(int x, int y, int width, int height);
        void fillRect(int x, int y, int width, int height);

        void drawRotatedRect(int x, int y, int width, int height, double angle, int centerX, int centerY);
        void fillRotatedRect(int x, int y, int width, int height, double angle, int centerX, int centerY);

        void drawCircle(int centerX, int centerY, int radius);
        void fillCircle(int centerX, int centerY, int radius);

        void drawPolygon(const std::vector<SDL_Point>& points);
        void fillPolygon(const std::vector<SDL_Point>& points);
};

#endif
