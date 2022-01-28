// Main driver routine for the simulation that runs everything

#include "main.h"

int main()
// Main driver routine for the SPH simulation
{
	particle particles[NPART];
	int tstep;

	printf("Starting driver routine...\n");

	create_particles(particles);
	writefile(particles, "cube/test00000.model");

	for (tstep = 1; tstep <= TSTEPS; tstep++)
		advance_time(particles, tstep);

	printf("Driver routine finished. Exiting...\n");

	return 0;
}

