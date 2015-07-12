#include "pathplan.h"

/*

 .  y
/|\
 |
 ._____________dx______________
 |o_____o____o____o_____o ____o| (x, y)
 |o_____o____o____o_____o_____o|
 |o_____o____o____o_____o_____o|
 |o_____o____o____o_____o_____o|dy
 |o_____o____o____o_____o_____o|
 |o___*(ox, oy)___o_____o_____o|
 |(0,0)_o____o____o_____o_____o|----------> x

*/

void path(double *x,
          double *y,
          double *dx,
          double *dy,
          size_t *nx,
          size_t *ny,
          point2 **pts,
          size_t **idx)
{
    *nx = 1 + (*x / *dx);
    *ny = 1 + (*y / *dy);
    *dx = *x / (double)*nx;
    *dy = *y / (double)*ny;
    ++(*nx);
    ++(*ny);

    *pts = (point2 *)malloc( (*nx)*(*ny)*sizeof(point2) );
    *idx = (size_t *)malloc( (*nx)*(*ny)*sizeof(size_t) );

    // the points
    for (int i = 0; i < *ny; ++i) {
        for (int j = 0; j < *nx; ++j) {
            (i*(*nx)+j+(*pts))->x =      j    * (*dx);
            (i*(*nx)+j+(*pts))->y = (*ny-i-1) * (*dy);
        }
    }

    // the path
    int i = 0;
    int j = 0;
    int k = 0;
    int f = 1;

    // the index
    while (j < *ny) {
        while (-1 < i && i < *nx) {
            *((*idx)+k) = (*ny-j-1)*(*nx)+i;
            ++k;
            i += f;
        }
        f *= -1;
        i += f;
        ++j;
    }
}
