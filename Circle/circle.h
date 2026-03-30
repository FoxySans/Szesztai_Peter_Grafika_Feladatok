#ifndef CIRCLE_H
#define CIRCLE_H
#include <SDL2/SDL.h>

/**
 * Data of a circle object in Descartes coordinate system
 */
typedef struct Circle
{
	double x;
	double y;
	double radius;
	int colour;
} Circle;

/**
 * Set the data of the circle
 */
void set_circle_data(Circle* circle, double x, double y, double radius);

/**
 * Calculate the area of the circle.
 */
double calc_circle_area(const Circle* circle);

void draw_circle(SDL_Renderer* renderer, const Circle* circle, int segments);

void draw_circle_by_angle(SDL_Renderer* renderer, const Circle* circle, double delta_alpha);

void draw_circle_by_length(SDL_Renderer* renderer, const Circle* circle, double max_line_length);

#endif // CIRCLE_H
