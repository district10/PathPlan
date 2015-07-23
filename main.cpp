#include <QCoreApplication>
#include "pathplan.h"
#include <QDebug>

int main(int argc, char *argv[])
{
    // QCoreApplication a(argc, argv);

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
    printf("\nPlanned:\n"
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

    return 0;
    //return a.exec();
}
