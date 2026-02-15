#include "cuboid.h"

#include <stdio.h>

int main(int argc, char* argv[])
{
	Cuboid cuboid;
	double volume;
	double surface;

	set_cub_data(&cuboid, 5, 10, 8);
	
	volume = calc_cub_volume(&cuboid);
	surface = calc_cub_surf(&cuboid);

	printf("Cuboid volume: %lf\n", volume);
	printf("Cuboid surface: %lf\n", surface);

	if (has_square_face(&cuboid))
	{
		printf("The object has a square face.");
	}
	else{
		printf("The object lacks a square face.");
	}
	
	
	return 0;
}
