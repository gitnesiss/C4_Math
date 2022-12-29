#include "s21_math.h"

static long double main_alg(double, double);
static int exep_foo(double, double, long double *);

long double s21_pow(double base, double exp) {
    long double result = 0;
    if (!exep_foo(base, exp, &result)) {
        if (exp == 1.0) {
            result = base;
        } else if (exp == 2.0) {
            result = base * base;
        } else if (exp == -1.0) {
            result = 1.0 / base;
        } else if ((int)exp == exp &&
                (int)base == base &&
                exp > 0) {
            result = base;
            while (--exp) {result *= base;}
        } else { result = main_alg(base, exp);}
    }
    return result;
}

static long double main_alg(double base, double exp) {
    int sign = 1;
    if (base < 0) {
        base = s21_fabs(base);
        if ((int)exp % 2) {sign *= -1;}
    }
    return s21_exp(exp * s21_log(base)) * sign;
}

static int exep_foo(double base, double exp, long double *indet) {
    int sign = 0;

    int base_is_nan = is_nan(base);
    int base_is_fin = is_fin(base);
    int exp_is_nan = is_nan(exp);
    int exp_is_fin = is_fin(exp);
    int exp_min = s21_fabs(exp - s21_floor(exp)) <= S21_EPS;

    // pow(±0, exp), where exp is negative, finite, and is an even integer or a
    //  non-integer, returns +∞ and raises FE_DIVBYZERO
    if (!sign && base_is_fin && !base_is_nan && s21_fabs(base) < S21_EPS && exp_is_fin &&
        ((exp_min && !(((int)exp) % 2)) || !exp_min)) {
        if (base == 0 && exp == 0) {
        *indet = 1;
        } else if (base == 0 && exp > 0) {
        *indet = 0;
        } else {*indet = S21_INF;}
        sign = 1;
    }

    // pow(±0, -∞) returns +∞ and may raise FE_DIVBYZERO
    if (!sign && base_is_fin && !base_is_nan && s21_fabs(base) < S21_EPS && !exp_is_nan &&
        !exp_is_fin && exp < 0) {
        *indet = S21_INF;
        sign = 1;
    }

    // pow(±0, exp), where exp is positive non-integer or a positive even
    //  integer, returns +0
    if (!sign && base_is_fin && !base_is_nan && s21_fabs(base) < S21_EPS &&
        ((!exp_min && s21_fabs(exp) > S21_EPS) ||
        (exp_min && !(((int)exp) % 2)))) {
        *indet = +0;
        sign = 1;
    }

    // pow(-1, ±∞) returns 1
    if (!sign && base_is_fin && !base_is_nan && s21_fabs(base + 1) < S21_EPS &&
        !exp_is_fin && !exp_is_nan) {
        *indet = 1;
        sign = 1;
    }

    // pow(+1, exp) returns 1 for any exp, even when exp is NaN
    if (!sign && base_is_fin && !base_is_nan && s21_fabs(base - 1) < S21_EPS) {
        *indet = 1;
        sign = 1;
    }

    // pow(base, ±0) returns 1 for any base, even when base is NaN
    if (!sign && s21_fabs(exp) < S21_EPS) {
        *indet = 1;
        sign = 1;
    }

    // pow(base, exp) returns NaN and raises FE_INVALID if base is finite and
    // negative and exp is finite and non-integer.
    if (!sign && base_is_fin && base < -S21_EPS && exp_is_fin && !exp_min) {
        *indet = S21_NAN;
        sign = 1;
    }

    // pow(base, -∞) returns +∞ for any |base|<1
    if (!sign && s21_fabs(base) - 1 < S21_EPS && !exp_is_nan && !exp_is_fin && exp < 0) {
        *indet = S21_INF;
        sign = 1;
    }

    // pow(base, -∞) returns +0 for any |base|>1
    if (!sign && s21_fabs(base) - 1 > S21_EPS && !exp_is_nan && !exp_is_fin && exp < 0) {
        *indet = +0;
        sign = 1;
    }

    // pow(base, +∞) returns +0 for any |base|<1
    if (!sign && s21_fabs(base) - 1 < S21_EPS && !exp_is_nan && !exp_is_fin && exp > 0) {
        *indet = +0;
        sign = 1;
    }

    // pow(base, +∞) returns +∞ for any |base|>1
    if (!sign && s21_fabs(base) - 1 > S21_EPS && !exp_is_nan && !exp_is_fin && exp > 0) {
        *indet = S21_INF;
        sign = 1;
    }

    // pow(-∞, exp) returns -0 if exp is a negative odd integer
    if (!sign && !base_is_nan && !base_is_fin && base < 0 && exp_min && exp < 0 &&
        ((int)exp) % 2) {
        *indet = -0.;
        sign = 1;
    }

    // pow(-∞, exp) returns +0 if exp is a negative non-integer or negative
    // even integer
    if (!sign && !base_is_nan && !base_is_fin && base < 0 &&
        ((!exp_min && exp < 0) || (exp_min && exp < 0 && !(((int)exp) % 2)))) {
        *indet = +0;
        sign = 1;
    }

    // pow(-∞, exp) returns -∞ if exp is a positive odd integer
    if (!sign && !base_is_nan && !base_is_fin && base < 0 &&
        (exp_min && exp > 0 && ((int)exp) & 1)) {
        *indet = -S21_INF;
        sign = 1;
    }

    // pow(-∞, exp) returns +∞ if exp is a positive non-integer or positive
    // even integer
    if (!sign && !base_is_nan && !base_is_fin && base < 0 &&
        ((!exp_min && exp > 0) || (exp_min && exp > 0 && !(((int)exp) % 2)))) {
        *indet = +S21_INF;
        sign = 1;
    }

    // pow(+∞, exp) returns +0 for any negative exp
    if (!sign && !base_is_nan && !base_is_fin && base > 0 && exp < -S21_EPS) {
        *indet = +0;
        sign = 1;
    }

    // pow(+∞, exp) returns +∞ for any positive exp
    if (!sign && !base_is_nan && !base_is_fin && base > 0 && exp > S21_EPS) {
        *indet = +S21_INF;
        sign = 1;
    }

    if (!sign && (base_is_nan || exp_is_nan)) {
        *indet = S21_NAN;
        sign = 1;
    }
    return sign;
}
