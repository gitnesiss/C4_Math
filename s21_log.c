#include "s21_math.h"

static long double main_alg(double);
static int exep_foo(double, long double *);

long double s21_log(double x) {
    long double result = 0;
    if (!exep_foo(x, &result)) {result = main_alg(x);}
    return result;
}

static long double main_alg(double x) {
    int ex_pow = 0;
    double result = 0;
    double compare = 0;
    for (; x >= S21_EXP; x /= S21_EXP, ex_pow++) continue;
    for (int i = 0; i < 100; i++) {
        compare = result;
        result = compare + 2 * (x - s21_exp(compare)) / (x + s21_exp(compare));
    }
    return result + ex_pow;
}

static int exep_foo(double base, long double *indet) {
    int sign = 0;
    if (base == S21_INF) {
        *indet = S21_INF;
        sign = 1;
    } else if (base == 0) {
        *indet = -S21_INF;
        sign = 1;
    } else if (base < 0) {
        *indet = S21_NAN;
        sign = 1;
    } else if (base == 1) {
        *indet = 0;
        sign = 1;
    }
    return sign;
}
