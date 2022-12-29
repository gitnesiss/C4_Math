#include "s21_math.h"

long double s21_acos(double x) {
    long double acos = 0;
    if (x == S21_NAN || x == -S21_INF || x == S21_INF || x > 1 || x < -1) {
        acos = S21_NAN;
    }
    if (x == 1) {
        acos = 0;
    } else if (x == -1) {
        acos = S21_PI;
    } else {
        for (register int i = 0; i < 100; i++) {
        acos += ((s21_fact(2 * i)) / (s21_pow(4, i) * (s21_pow((s21_fact(i)), 2)) *
         (2 * i + 1))) *  s21_pow(x, (2 * i + 1));
        }
        acos = (S21_PI / 2) - acos;
    }
    return acos;
}
