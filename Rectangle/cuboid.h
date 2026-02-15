#ifndef CUBOID_H
#define CUBOID_H

typedef struct Cuboid
{
	double x;
	double y;
    double z;
} Cuboid;

void set_cub_data(Cuboid* cuboid, double x, double y, double z);

double calc_cub_volume(const Cuboid* cuboid);

double calc_cub_surf(const Cuboid* cuboid);

int has_square_face(const Cuboid* cuboid);

#endif 
