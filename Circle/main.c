#include "circle.h"
#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <math.h>

#define MAX_CIRCLE_COUNT 100

bool is_inside(const Circle* c, int x, int y) {
    double dx = c->x - x;
    double dy = c->y - y;
    return (dx * dx + dy * dy) <= (c->radius * c->radius);
}

int main(int argc, char* argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) return 1;

    SDL_Window* window = SDL_CreateWindow("Bubor-ék", 
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, 0);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    Circle circles[MAX_CIRCLE_COUNT];
    int circle_count = 0;
    int dragged_index = -1;

    bool quit = false;
    SDL_Event e;

    while (!quit) {
        int mouse_x, mouse_y;
        Uint32 mouse_state = SDL_GetMouseState(&mouse_x, &mouse_y);

        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) quit = true;

            if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_RIGHT) {
                if (circle_count < MAX_CIRCLE_COUNT) {
                    set_circle_data(&circles[circle_count], mouse_x, mouse_y, 50);
                    circle_count++;
                }
            }

            if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT) {
                for (int i = circle_count - 1; i >= 0; i--) {
                    if (is_inside(&circles[i], mouse_x, mouse_y)) {
                        dragged_index = i;
                        break;
                    }
                }
            }

            if (e.type == SDL_MOUSEBUTTONUP && e.button.button == SDL_BUTTON_LEFT) {
                dragged_index = -1;
            }
        }

        if (dragged_index != -1) {
            circles[dragged_index].x = mouse_x;
            circles[dragged_index].y = mouse_y;
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        for (int i = 0; i < circle_count; i++) {
            SDL_SetRenderDrawColor(renderer, 100, 150, 255, 255);
            draw_circle_by_length(renderer, &circles[i], 5.0);

            if (is_inside(&circles[i], mouse_x, mouse_y)) {
                SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255); 
                int r = 15;
                SDL_RenderDrawLine(renderer, circles[i].x - r, circles[i].y - r, circles[i].x + r, circles[i].y + r);
                SDL_RenderDrawLine(renderer, circles[i].x + r, circles[i].y - r, circles[i].x - r, circles[i].y + r);
            }
        }

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}