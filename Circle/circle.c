#include "circle.h"
#include <SDL2/SDL.h>
#include <math.h>
#include <C:\Users\szesz\Documents\Egyetemi_cuccok\IV_Felev\PC_Graphics\c_sdk_220203\MinGW\include\SDL2\SDL_stdinc.h>

void set_circle_data(Circle* circle, double x, double y, double radius)
{
	circle->x = x;
	circle->y = y;
	if (radius > 0.0) {
		circle->radius = radius;
	} else {
		circle->radius = NAN;
	}
}

double calc_circle_area(const Circle* circle)
{
	double area = circle->radius * circle->radius * M_PI;
	return area;
}

void draw_circle(SDL_Renderer* renderer, const Circle* circle, int segments) {
    if (segments < 3) segments = 3;
    double step = 2.0 * M_PI / segments;
    for (int i = 0; i < segments; i++) {
        double a1 = i * step;
        double a2 = (i + 1) * step;
        SDL_RenderDrawLine(renderer, 
            (int)(circle->x + circle->radius * cos(a1)), (int)(circle->y + circle->radius * sin(a1)),
            (int)(circle->x + circle->radius * cos(a2)), (int)(circle->y + circle->radius * sin(a2)));
    }
}

void draw_circle_by_angle(SDL_Renderer* renderer, const Circle* circle, double delta_alpha) {
    int segments = (int)(2.0 * M_PI / delta_alpha);
    draw_circle(renderer, circle, segments);
}

void draw_circle_by_length(SDL_Renderer* renderer, const Circle* circle, double max_line_length) {
    int segments = (int)((2.0 * M_PI * circle->radius) / max_line_length);
    draw_circle(renderer, circle, segments);
}
