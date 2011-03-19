#include <stdio.h>
#include <stdlib.h>
#include <math.h>


typedef struct {
    size_t degree;
    double *coefficients;
} Polynomial;


Polynomial* PolynomialNew(size_t degree) {
    double *coefficients = calloc(degree+1, sizeof(double));
    if (coefficients == NULL) {
        fputs("Not enough memory to allocate new polynomial.\n", stderr);
        abort();
    }

    Polynomial *p = malloc(sizeof(Polynomial));
    if (p == NULL) {
        fputs("Not enough memory to allocate new polynomial.\n", stderr);
        abort();
    }

    p->degree = degree;
    p->coefficients = coefficients;

    return p;
}


void PolynomialFree(Polynomial *p) {
    free(p->coefficients);
    free(p);
}


double PolynomialEvaluate(Polynomial *p, double x) {
    double sum = 0.0;

    for (size_t i = 0; i <= p->degree; ++i) {
        sum += p->coefficients[i] * pow(x, i);
    }

    return sum;
}


void PolynomialPrint(Polynomial *p) {
    for (size_t i = p->degree; i != (size_t)-1; --i) {
        if (p->coefficients[i] != 0) {
            printf("%.gx^%d", p->coefficients[i], (int)i);
            if (i != 0) {
                printf(" + ");
            }
        }
    }
    putchar('\n');
}


int main(void) {
    Polynomial *p = PolynomialNew(3);
    p->coefficients[0] = -3;
    p->coefficients[1] =  1;
    p->coefficients[3] =  2;

    PolynomialPrint(p);
    printf("%g\n", PolynomialEvaluate(p, 4));
    PolynomialFree(p);


    return EXIT_SUCCESS;
}
