#include <stdio.h>
#include <stdlib.h>
#include <math.h>


double IntegrateTrapezoid(double (*f)(double), double start, double end, size_t num_intervals) {
    double sum = 0.0;
    double x0 = start;
    double h = (end - start) / num_intervals;

    for (size_t i = 0; i < num_intervals; ++i) {
        double y1 = (*f)(x0);
        double y2 = (*f)(x0 + h);

        sum += (y1 + y2) / 2 * h;
        x0 += h;
    }

    return sum;
}


double IntegrateSimpson1_3(double (*f)(double), double start, double end) {
    double h = (end - start) / 2;

    return h/3 * ((*f)(start) + 4*(*f)(start + h) + (*f)(end));
}


double IntegrateSimpson3_8(double (*f)(double), double start, double end) {
    double h = (end - start) / 3;

    return 3.0/8.0 * h * ((*f)(start) + 3*(*f)(start + h) +
                          3*(*f)(start + 2*h) + (*f)(end));
}


double f(double x) {
    return 1.0 / (x*x + x + 1);
}

int main(void) {
    printf("%g\n", IntegrateTrapezoid(&f, 0, 6, 100));
    printf("%g\n", IntegrateSimpson1_3(&f, 0, 6));
    printf("%g\n", IntegrateSimpson3_8(&f, 0, 6));
    return EXIT_SUCCESS;
}
