// Header file for the voxel sorting routine

#ifndef VOXELS_H
#define VOXELS_H

#include "particle.h"

#include <stdlib.h>
#include <stdio.h>

// Voxel grid parameters
#define VOXSIDE (2.0 * HLEN)
#define XVOX ((int) (XMAX / VOXSIDE))
#define YVOX ((int) (YMAX / VOXSIDE))
#define ZVOX ((int) (ZMAX / VOXSIDE))

void sort_voxels(particle particles[], int voxels[]);
particle ** find_neighbors(particle particles[], int voxels[], int p, int * n_neighbors);

#endif

