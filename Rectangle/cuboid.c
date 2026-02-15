#include "cuboid.h"

#include <math.h>

void set_cub_data(Cuboid* cuboid, double x, double y, double z)
{
	if (x > 0.0) {
        cuboid->x = x;
	} else {
		cuboid->x = x*-1;
	}

    if (y > 0.0) {
        cuboid->y = y;
	} else {
		cuboid->y = y*-1;
	}

    if (z > 0.0) {
        cuboid->z = z;
	} else {
		cuboid->z = z*-1;
	}
}

double calc_cub_volume(const Cuboid* cuboid)
{
	double volume = cuboid->x*cuboid->y*cuboid->z;
	return volume;
	
}

double calc_cub_surf(const Cuboid* cuboid){
	double surface = 2*(cuboid->x*cuboid->y+cuboid->x*cuboid->z+cuboid->y*cuboid->z);
	return surface;
}

int has_square_face(const Cuboid* cuboid){
	if (cuboid->x == cuboid->y || cuboid->x == cuboid->z || cuboid->y == cuboid->z)
	{
		return 1;
	}
	else
	{
		return 0;
	}
	
	
}
