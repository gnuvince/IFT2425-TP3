#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define PI 3.14159265358979323846
#define START 0
#define END   3*PI

double fact(int);
double CalculateS(double, double, double, size_t);


/* A polynomial structure contains an non-negative degree,
 * and a list of coefficients.
 */
typedef struct {
    size_t degree;
    double *coefficients;
} Polynomial;


/* Allocate a new polynomial of degree n.  Because we have
 * coefficients from 0 to n inclusive, we allocate a table of
 * n+1 coefficients.  All coefficients are initialized to 0.
 */
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


/* Free the space taken by a polynomial. */
void PolynomialFree(Polynomial *p) {
    free(p->coefficients);
    free(p);
}


/* Given a value for x, evaluate the polynomial.  Not used for
 * interpolation polynomials.
 */
double PolynomialEvaluate(Polynomial *p, double x) {
    double sum = 0.0;

    for (size_t i = 0; i <= p->degree; ++i) {
        sum += p->coefficients[i] * pow(x, i);
    }

    return sum;
}

/* Display a polynomial. */
void PolynomialPrint(Polynomial *p) {
    for (size_t i = p->degree; i != (size_t)-1; --i) {
        printf("%+gx^%d", p->coefficients[i], (int)i);
    }
    putchar('\n');
}


/* Using Newton-Gregory's method, allocate and return a new collocation
 * polynomial of degree `degree` that passes through `degree+1` points
 * in the interval [start, end].
 */
Polynomial* InterpolationPolynomialNew(double (*f)(double), size_t degree,
                                       double start, double end) {
    Polynomial *p = PolynomialNew(degree);
    double table[degree + 1][degree + 1]; /* Containing Delta_y, Delta^2_y, ... */
    double h = (end - start) / degree;

    /* Initialize table */
    for (size_t i = 0; i <= degree; ++i) {
        table[0][i] = (*f)(start + i*h);
        //printf("  >> f(%.6lf) = %.6lf\n", (start + i*h), table[0][i]);
    }

    /* Fill up the table */
    for (size_t i = 1; i <= degree; ++i) {
        for (size_t j = 0; j <= degree - i; ++j) {
            table[i][j] = table[i-1][j+1] - table[i-1][j];
        }
    }

    /*
    for (size_t i = 0; i <= degree; ++i) {
        for (size_t j = 0; j <= degree - i; ++j) {
            printf("%+.5lf\t", table[i][j]);
        }
        putchar('\n');
    }
    */





    /* Assign coefficients in polynomial. */
    for (size_t i = 0; i <= degree; ++i) {
        p->coefficients[i] = table[i][0] / (fact(i) * pow(h, i));
    }

    return p;
}


double InterpolationPolynomialEval(Polynomial *p, double x, double start, double end) {
    double y = 0.0;
    double h = (end - start) / p->degree;

    for (size_t i = 0; i <= p->degree; ++i) {
        double t = 1.0;
        for (size_t j = 0; j < i; ++j) {
            t *= (x - (start + j*h));
        }
        y += p->coefficients[i] * t;
    }

    return y;
}


void InterpolationPolynomialPrint(Polynomial *p, double start, double end) {
    double h = (end - start) / p->degree;

    for (size_t i = p->degree; i != (size_t)-1; --i) {
        printf("%+g", p->coefficients[i]);
        for (size_t j = 0; j < i; ++j) {
            printf("*(x - %g)", start + j*h);
        }
    }
    putchar('\n');
}


double fact(int n) {
    double p = 1.0;
    for (int i = 1; i <= n; ++i) {
        p *= i;
    }
    return p;
}


double f(double x) {
    return sin(x);
}

int main(void) {
    for (size_t i = 1; i <= 5; ++i) {
        Polynomial *p = InterpolationPolynomialNew(&f, i, START, END);
        InterpolationPolynomialPrint(p, START, END);
        PolynomialFree(p);
    }

    return EXIT_SUCCESS;
}
