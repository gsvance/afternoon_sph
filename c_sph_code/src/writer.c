// Routine that writes models to file

#include "writer.h"

void writefile(particle particles[], char filename[])
// Write particles in binary to file given by filename
{
	FILE * fp;

	fp = fopen(filename, "wb");
	fwrite(particles, sizeof(particle), NPART, fp);
	fclose(fp);
}

void writeascii(particle particles[], char filename[])
// Write particles to filename in readable format
{
	FILE * fp;
	int n;

	fp = fopen(filename, "w");
	fprintf(fp, "#mass id rho pgrad_x pgrad_y pgrad_z visc_x visc_y visc_z pos_x pos_y pos_z vel_x vel_y vel_z acc_x acc_y acc_z\n");

	for (n = 0; n < NPART; n++)
		fprintf(fp, "%e %d %e %e %e %e %e %e %e %e %e %e %e %e %e %e %e %e\n", particles[n].mass, particles[n].id, particles[n].rho, particles[n].pgrad.xyz[0], particles[n].pgrad.xyz[1], particles[n].pgrad.xyz[2], particles[n].visc.xyz[0], particles[n].visc.xyz[1], particles[n].visc.xyz[2], particles[n].pos.xyz[0], particles[n].pos.xyz[1], particles[n].pos.xyz[2], particles[n].vel.xyz[0], particles[n].vel.xyz[1], particles[n].vel.xyz[2], particles[n].acc.xyz[0], particles[n].acc.xyz[1], particles[n].acc.xyz[2]);

	fclose(fp);
}

