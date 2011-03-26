#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define START 0.0
#define END   1.0


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


double Integrate(double (*f)(double), double start, double end, size_t M) {
    if (M <= 0) {
        fputs("Not a valid number of intervals.\n", stderr);
        abort();
    }
    else if (M == 1) {
        return IntegrateTrapezoid(f, start, end, M);
    }
    else if (M % 2 == 0) {
        double h = (end - start) / M;
        double x0 = start;
        double sum = 0.0;

        for (size_t i = 0; i < M; i += 2) {
            sum += IntegrateSimpson1_3(f, x0, x0 + 2*h);
            x0 += 2*h;
        }

        return sum;
    }
    else {
        double h = (end - start) / M;
        double x0 = start;
        double sum = 0.0;

        for (size_t i = 0; i < M-3; i += 2) {
            sum += IntegrateSimpson1_3(f, x0, x0 + 2*h);
            x0 += 2*h;
        }

        return sum + IntegrateSimpson3_8(f, end - 3*h, end);
    }
}


double f(double x) {
    return 1.0 / (x*x + x + 1);
}


void Usage(const char *program_name) {
    fprintf(stderr, "Utilisation: %s <M>\n", program_name);
}


int main(int argc, char *argv[]) {
    if (argc != 2) {
        Usage(argv[0]);
        return 1;
    }

    int M = atoi(argv[1]);

    printf("Méthode de Simpson  : %f\n", Integrate(&f, START, END, M));
    printf("Méthode des trapèzes: %f\n", IntegrateTrapezoid(&f, START, END, M));

    return EXIT_SUCCESS;
}
