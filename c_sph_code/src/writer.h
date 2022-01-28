// Header file for the routine that writes models to file

#ifndef WRITER_H
#define WRITER_H

#include "particle.h"
#include "params.h"

#include <stdio.h>

void writefile(particle particles[], char filename[]);
void writeascii(particle particles[], char filename[]);

#endif

