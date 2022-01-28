// Simple reader that translates binary model files to an ascii readable format

#include "particle.h"
#include "params.h"
#include "reader.h"
#include "writer.h"

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char * argv[])
{
	particle particles[NPART];

	if (argc != 3)
	{
		printf("asciiread: incorrect argument number\n");
		exit(1);
	}
	
	readfile(particles, argv[1]);
	writeascii(particles, argv[2]);

	return 0;
}

