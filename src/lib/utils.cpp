#include <SDL2/SDL_rect.h>
#include <algorithm>
#include <iostream>

void throwError(const char * msg) {
    std::cerr << msg << std::endl;
    exit(1);
}

SDL_Rect calculateRotatedRect(int x, int y, int width, int height, double angle, int centerX, int centerY) {
    SDL_Rect rect;

    double rad = angle * M_PI / 180.0;
    int newX1 = static_cast<int>(centerX + (x - centerX) * std::cos(rad) - (y - centerY) * std::sin(rad));
    int newY1 = static_cast<int>(centerY + (x - centerX) * std::sin(rad) + (y - centerY) * std::cos(rad));
    int newX2 = static_cast<int>(centerX + (x + width - centerX) * std::cos(rad) - (y - centerY) * std::sin(rad));
    int newY2 = static_cast<int>(centerY + (x + width - centerX) * std::sin(rad) + (y - centerY) * std::cos(rad));
    int newX3 = static_cast<int>(centerX + (x + width - centerX) * std::cos(rad) - (y + height - centerY) * std::sin(rad));
    int newY3 = static_cast<int>(centerY + (x + width - centerX) * std::sin(rad) + (y + height - centerY) * std::cos(rad));
    int newX4 = static_cast<int>(centerX + (x - centerX) * std::cos(rad) - (y + height - centerY) * std::sin(rad));
    int newY4 = static_cast<int>(centerY + (x - centerX) * std::sin(rad) + (y + height - centerY) * std::cos(rad));

    rect.x = std::min({newX1, newX2, newX3, newX4});
    rect.y = std::min({newY1, newY2, newY3, newY4});
    rect.w = std::max({newX1, newX2, newX3, newX4}) - rect.x;
    rect.h = std::max({newY1, newY2, newY3, newY4}) - rect.y;

    return rect;
}
