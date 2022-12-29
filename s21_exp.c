#include "s21_math.h"

static long double main_alg(double);
static int exep_foo(double base, long double *indet);

long double s21_exp(double x) {
    long double result = 0;
    if (!exep_foo(x, &result)) {result = main_alg(x);}
    return result;
}

static long double main_alg(double x) {
    int signal = 0;
    long double result = 0;
    long double p = 1;
    if (x < 0) {
            x *= -1;
            signal = 1;
        }
        for (int n = 1; s21_fabs(p) > S21_EPS && result != S21_INF; n++) {
            result += p;
            p *= x / n;
            if (!signal) {
                if (result > __DBL_MAX__) {result = S21_INF;}
            } else {
                if (1. / result < __DBL_DENORM_MIN__) {result = S21_INF;}
            }
        }
    return !signal ? result : 1. / result;
}

static int exep_foo(double base, long double *indet) {
    int sign = 0;
    if (base == -S21_INF) {
        *indet = 0;
        sign = 1;
    } else if (is_nan(base) || is_inf(base)) {
        *indet = base;
        sign = 1;
    }
    return sign;
}
