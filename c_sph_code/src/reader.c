// Routine that reads models from file

#include "reader.h"

void readfile(particle particles[], char filename[])
// Read particles in binary from file given by filename
{
	FILE * fp;

	fp = fopen(filename, "rb");
	fread(particles, sizeof(particle), NPART, fp);
	fclose(fp);
}

