#include "s21_math.h"

long double s21_ceil(double x) {
    long double result = 0;
    if (is_nan(x) || is_inf(x)) {
        result = x;
    } else {
        result = (int)x == x ? (long double)x
                : (x < 0 ? (long double)((int)x) : (long double)((int)++x));
    }
    return result;
}
