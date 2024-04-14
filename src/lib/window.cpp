#include <SDL2/SDL_events.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include <algorithm>
#include <cmath>
#include <cstdint>
#include <vector>
#include "utils.h"
#include "window.h"

SDL_Window* window;
SDL_Renderer* renderer;
uint8_t color[3];

Window::Window(const char* title, int width, int height) {
    window = SDL_CreateWindow(title, 0, 0, width, height, SDL_WINDOW_OPENGL);
    if (window == nullptr) throwError("Erro ao criar janela SDL");

    renderer = SDL_CreateRenderer(window, -1 , SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr) throwError("Erro ao criar renderizador SDL");
}

SDL_Event* Window::poolEvent() {
    SDL_Event* event = new SDL_Event;
    bool status = SDL_PollEvent(event);
    if (!status) {
        delete event;
        return nullptr;
    }
    return event;
}

void Window::setColor(uint8_t r, uint8_t g, uint8_t b) {
    color[0] = r;
    color[1] = g;
    color[2] = b;
    SDL_SetRenderDrawColor(renderer, r, g, b, 255);
}

void Window::clear() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, color[0], color[1], color[2], 255);
}

void Window::present() {
    SDL_RenderPresent(renderer);
}

void Window::drawPoint(int x, int y) {
    SDL_RenderDrawPoint(renderer, x, y);
}

void Window::drawLine(int x1, int y1, int x2, int y2) {
    SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
}

void Window::drawRay(int startX, int startY, double angle, int length) {
    int endX = startX + static_cast<int>(length * std::cos(angle * M_PI / 180.0));
    int endY = startY + static_cast<int>(length * std::sin(angle * M_PI / 180.0));
    SDL_RenderDrawLine(renderer, startX, startY, endX, endY);
}

void Window::drawThickLine(int x1, int y1, int x2, int y2, int thickness) {
    float dx = x2 - x1;
    float dy = y2 - y1;

    float length = sqrt(dx * dx + dy * dy);

    float vx = dx / length;
    float vy = dy / length;

    float offsetX = thickness * vy;
    float offsetY = thickness * vx;

    float x1r = x1 + offsetX / 2;
    float y1r = y1 - offsetY / 2;
    float x2r = x2 + offsetX / 2;
    float y2r = y2 - offsetY / 2;
    float x3r = x2 - offsetX / 2;
    float y3r = y2 + offsetY / 2;
    float x4r = x1 - offsetX / 2;
    float y4r = y1 + offsetY / 2;

    std::vector<SDL_Point> points; 
    points.push_back({ static_cast<int>(x1r), static_cast<int>(y1r) });
    points.push_back({ static_cast<int>(x2r), static_cast<int>(y2r) });
    points.push_back({ static_cast<int>(x3r), static_cast<int>(y3r) });
    points.push_back({ static_cast<int>(x4r), static_cast<int>(y4r) });
    points.push_back({ static_cast<int>(x1r), static_cast<int>(y1r) });

    fillPolygon(points);
}

void Window::drawRect(int x, int y, int width, int height) {
    SDL_Rect rect = {x, y, width, height};
    SDL_RenderDrawRect(renderer, &rect);
}

void Window::fillRect(int x, int y, int width, int height) {
    SDL_Rect rect = {x, y, width, height};
    SDL_RenderFillRect(renderer, &rect);
}

void Window::drawRotatedRect(int x, int y, int width, int height, double angle, int centerX, int centerY) {
    double rad = angle * M_PI / 180.0;
    double newX1 = centerX + (x - centerX) * std::cos(rad) - (y - centerY) * std::sin(rad);
    double newY1 = centerY + (x - centerX) * std::sin(rad) + (y - centerY) * std::cos(rad);
    double newX2 = centerX + (x + width - centerX) * std::cos(rad) - (y - centerY) * std::sin(rad);
    double newY2 = centerY + (x + width - centerX) * std::sin(rad) + (y - centerY) * std::cos(rad);
    double newX3 = centerX + (x + width - centerX) * std::cos(rad) - (y + height - centerY) * std::sin(rad);
    double newY3 = centerY + (x + width - centerX) * std::sin(rad) + (y + height - centerY) * std::cos(rad);
    double newX4 = centerX + (x - centerX) * std::cos(rad) - (y + height - centerY) * std::sin(rad);
    double newY4 = centerY + (x - centerX) * std::sin(rad) + (y + height - centerY) * std::cos(rad);

    SDL_Point points[5] = {
        { static_cast<int>(newX1), static_cast<int>(newY1) },
        { static_cast<int>(newX2), static_cast<int>(newY2) },
        { static_cast<int>(newX3), static_cast<int>(newY3) },
        { static_cast<int>(newX4), static_cast<int>(newY4) },
        { static_cast<int>(newX1), static_cast<int>(newY1) }
    };
    SDL_RenderDrawLines(renderer, points, 5);
}

void Window::fillRotatedRect(int x, int y, int width, int height, double angle, int centerX, int centerY) {
    double rad = angle * M_PI / 180.0;
    double newX1 = centerX + (x - centerX) * std::cos(rad) - (y - centerY) * std::sin(rad);
    double newY1 = centerY + (x - centerX) * std::sin(rad) + (y - centerY) * std::cos(rad);
    double newX2 = centerX + (x + width - centerX) * std::cos(rad) - (y - centerY) * std::sin(rad);
    double newY2 = centerY + (x + width - centerX) * std::sin(rad) + (y - centerY) * std::cos(rad);
    double newX3 = centerX + (x + width - centerX) * std::cos(rad) - (y + height - centerY) * std::sin(rad);
    double newY3 = centerY + (x + width - centerX) * std::sin(rad) + (y + height - centerY) * std::cos(rad);
    double newX4 = centerX + (x - centerX) * std::cos(rad) - (y + height - centerY) * std::sin(rad);
    double newY4 = centerY + (x - centerX) * std::sin(rad) + (y + height - centerY) * std::cos(rad);

    std::vector<SDL_Point> points;
    points.push_back({ static_cast<int>(newX1), static_cast<int>(newY1) });
    points.push_back({ static_cast<int>(newX2), static_cast<int>(newY2) });
    points.push_back({ static_cast<int>(newX3), static_cast<int>(newY3) });
    points.push_back({ static_cast<int>(newX4), static_cast<int>(newY4) });

    fillPolygon(points);
}

void Window::drawCircle(int centerX, int centerY, int radius) {
    for (int angle = 0; angle < 360; angle++) {
        int x = static_cast<int>(radius * std::cos(angle * M_PI / 180.0));
        int y = static_cast<int>(radius * std::sin(angle * M_PI / 180.0));
        SDL_RenderDrawPoint(renderer, x + centerX, y + centerY);
    }
}

void Window::fillCircle(int centerX, int centerY, int radius) {
    for (int y = -radius; y <= radius; ++y) {
        for (int x = -radius; x <= radius; ++x) {
            if (x*x + y*y <= radius*radius) {
                SDL_RenderDrawPoint(renderer, x + centerX, y + centerY);
            }
        }
    }
}
void Window::drawPolygon(const std::vector<SDL_Point>& points) {
    if (points.size() < 3) throwError("O polígono precisa de ao menos 3 pontos.");

    for (size_t i = 0; i < points.size() - 1; ++i) {
        SDL_RenderDrawLine(renderer, points[i].x, points[i].y, points[i + 1].x, points[i + 1].y);
    }

    SDL_RenderDrawLine(renderer, points.back().x, points.back().y, points.front().x, points.front().y);
}

void Window::fillPolygon(const std::vector<SDL_Point>& points) {
    if (points.size() < 3) throwError("O polígono precisa de ao menos 3 pontos.");

    int minY = points[0].y;
    int maxY = points[0].y;
    for (size_t i = 1; i < points.size(); ++i) {
        if (points[i].y < minY) minY = points[i].y;
        if (points[i].y > maxY) maxY = points[i].y;
    }

    for (int y = minY; y <= maxY; ++y) {
        std::vector<int> intersections;

        for (size_t i = 0; i < points.size(); ++i) {
            size_t j = (i + 1) % points.size();
            int y1 = points[i].y;
            int y2 = points[j].y;
            if ((y1 <= y && y < y2) || (y2 <= y && y < y1)) {
                int x = points[i].x + (y - y1) * (points[j].x - points[i].x) / (y2 - y1);
                intersections.push_back(x);
            }
        }

        std::sort(intersections.begin(), intersections.end());

        for (size_t i = 0; i < intersections.size(); i += 2) {
            SDL_RenderDrawLine(renderer, intersections[i], y, intersections[i + 1] - 1, y);
        }
    }
}
