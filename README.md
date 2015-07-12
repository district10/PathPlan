# PathPlan

## Path

```
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
```


## Main

```
    double x = 6.6, dx = 2.6;
    double y = 4.7, dy = 1.8;
    printf("Input:\n"
           "%10sX: %4.2lf, dx: %4.2lf\n"
           "%10sY: %4.2lf, dy: %4.2lf\n", "", x, dx, "", y, dy);

    size_t nx, ny;
    point2 *pts = NULL;
    size_t *idx = NULL;

    // gen path
    path(&x, &y, &dx, &dy, &nx, &ny, &pts, &idx);
    printf("\nPlaned:\n"
           "%10sX: %4.2lf, dx: %4.2lf\n"
           "%10sY: %4.2lf, dy: %4.2lf\n", "", x, dx, "", y, dy);

    // print points
    puts("\nPoints");
    for (int i = 0; i < ny; ++i) {
        printf("%10s", "");
        for (int j = 0; j < nx; ++j) {
            printf("[%4.2lf, %4.2lf]%s",
                   (*(pts+i*ny+j)).x,
                   (*(pts+i*ny+j)).y,
                   (j != (nx-1)) ? "  " : "\n");
        }
    }

    // the path
    puts("\nThe Path:");
    int k = 0;
    while (k < nx*ny) {
        printf("%10s%2d: %2d ==> [%3.1f, %3.1f]\n", "", k+1, *(idx+k), (pts+*(idx+k))->x, (pts+*(idx+k))->y);
        ++k;
    }

    free(pts);
    free(idx);
```

## Sample output:

```
Input:
          X: 6.60, dx: 2.60
          Y: 4.70, dy: 1.80

Planed:
          X: 6.60, dx: 2.20
          Y: 4.70, dy: 1.57

Points
          [0.00, 4.70]  [2.20, 4.70]  [4.40, 4.70]  [6.60, 4.70]
          [0.00, 3.13]  [2.20, 3.13]  [4.40, 3.13]  [6.60, 3.13]
          [0.00, 1.57]  [2.20, 1.57]  [4.40, 1.57]  [6.60, 1.57]
          [0.00, 0.00]  [2.20, 0.00]  [4.40, 0.00]  [6.60, 0.00]

The Path:
           1: 12 ==> [0.0, 0.0]
           2: 13 ==> [2.2, 0.0]
           3: 14 ==> [4.4, 0.0]
           4: 15 ==> [6.6, 0.0]
           5: 11 ==> [6.6, 1.6]
           6: 10 ==> [4.4, 1.6]
           7:  9 ==> [2.2, 1.6]
           8:  8 ==> [0.0, 1.6]
           9:  4 ==> [0.0, 3.1]
          10:  5 ==> [2.2, 3.1]
          11:  6 ==> [4.4, 3.1]
          12:  7 ==> [6.6, 3.1]
          13:  3 ==> [6.6, 4.7]
          14:  2 ==> [4.4, 4.7]
          15:  1 ==> [2.2, 4.7]
          16:  0 ==> [0.0, 4.7]
```