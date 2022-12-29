#include "s21_math.h"

long double s21_tan(double x) {
    long double s21tan = 0;
    if (x == S21_NAN || x == -S21_INF || x == S21_INF) {
        s21tan = S21_NAN;
    } else {
        while (x < - S21_PI / 2 || x > S21_PI / 2) {
            if (x > S21_PI / 2) {
                x -= S21_PI;
            } else {
                x += S21_PI;
            }
        }
        if (x == S21_PI / 2) {
            s21tan = 16331239353195370L;
        } else if (x == - S21_PI / 2) {
            s21tan = -16331239353195370L;
        } else {
            s21tan = s21_sin(x) / s21_cos(x);
        }
    }
    return s21tan;
}
