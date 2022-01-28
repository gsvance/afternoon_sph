// Header for the routine steps time forwards

#ifndef STEPPER_H
#define STEPPER_H

#include "particle.h"
#include "voxels.h"
#include "boundary.h"
#include "equations.h"
#include "writer.h"

#include <stdio.h>
#include <stdlib.h>

void advance_time(particle particles[], int tstep);

#endif

