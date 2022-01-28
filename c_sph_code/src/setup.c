// File with the routines that set up the simulation

#include "setup.h"

void create_particles(particle particles[])
// Simple routine to make a 20cm x 20cm x 20cm cube of particles
{
	const int cubeside = 20; // particles
	const float cubedim = 20.0; // cm
	const float spacing = cubedim / cubeside; // cm

	const float xcorner = 0.25*XMAX - 0.5*cubedim; // cm
	const float ycorner = 0.5*(YMAX - cubedim); // cm
	const float zcorner = 0.5*(ZMAX - cubedim); // cm
	vector cubecorner;

	int n, i = 0, j = 0, k = 0;
	vector relpos, pos, vel;

	printf("Setup routine running...\n");

	// Set the position of the top cube corner
	cubecorner = vector_make(xcorner, ycorner, zcorner);

	// Check that things work out
	if (cubeside*cubeside*cubeside != NPART)
	{
		printf("Error: particle cube dimensions don't work.\n");
		exit(1);
	}

	// Generate the cube
	for (n = 0; n < NPART; n++)
	{
		relpos = vector_make(spacing*i, spacing*j, spacing*k);
		pos = vector_add(cubecorner, relpos);
		vel = vector_zero();

		particles[n] = particle_make(MPART, pos, vel);
	
		// Increment positions
		i++;
		if (i == cubeside)
		{
			i = 0;
			j++;

			if (j == cubeside)
			{
				j = 0;
				k++;
			}
		}
	}

	printf("Sucessfully created %d particles.\n", NPART);
}

