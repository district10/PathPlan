#ifndef PATHPLAN_H
#define PATHPLAN_H

#include <stdio.h>
#include <stdlib.h>

typedef struct point2 {
    double x;
    double y;
} point2;

void path(double *x,
          double *y,
          double *dx,
          double *dy,
          size_t *nx,
          size_t *ny,
          point2 **pts,
          size_t **idx);

#endif // PATHPLAN_H

