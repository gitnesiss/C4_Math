#include "s21_math.h"

long double s21_atan(double x) {
  long double atan = 0;
  const long double atan_1 = 0.7853981633974480L;
  if (is_nan(x)) {
    return S21_NAN;
  }
  if (x == 1) {
    atan = atan_1;
  } else if (x == -1) {
    atan = -atan_1;
  } else if (x == S21_PI / 2) {
    atan = 1.003884821853887214L;
  } else if (x == -S21_PI / 2) {
    atan = -1.003884821853887214L;
  } else if (x == S21_INF || x == -S21_INF) {
    atan = x < 0 ? -S21_PI / 2 : S21_PI / 2;
  } else if (-1. < x && x < 1.) {
    for (register int i = 0; i < 4000; i++) {
      atan += s21_pow(-1, i) * s21_pow(x, 1 + (2 * i)) / (1 + (2 * i));
    }
  } else {
    for (register int i = 0; i < 4000; i++) {
      atan += s21_pow(-1, i) * s21_pow(x, -1 - (2 * i)) / (1 + (2 * i));
    }
    atan = S21_PI * s21_sqrt(x * x) / (2 * x) - atan;
  }
  return atan;
}
