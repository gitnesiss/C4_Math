#include "s21_math.h"

static long double main_alg(double);
static int exep_foo(double, long double *);

long double s21_sqrt(double x) {
    long double result = 0;
    if (!exep_foo(x, &result)) {result = main_alg(x);}
    return result;
}

static long double main_alg(double x) {
    return s21_pow(x, 0.5);
}

static int exep_foo(double base, long double *indet) {
    int sign = 0;
    if (base == 0) {
        *indet = 0;
        sign = 1;
    } else if (base < 0) {
        *indet = S21_NAN;
        sign = 1;
    }
    return sign;
}
