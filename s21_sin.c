#include "s21_math.h"

long double s21_sin(double x) {
long double sum_sin = 0;
  int sign = 1;
  if (x == S21_NAN || x == -S21_INF || x == S21_INF) {
    return S21_NAN;
  }
  if (x == S21_PI) {
    return 1e-50;
  }
  if (x == -S21_PI) {
    return -1e-50;
  }
  if (x == 0) {
    return 0;
  }
  while (x < -2 * S21_PI || x > 2 * S21_PI) {
    if (x > 2 * S21_PI) {
      x -= 2 * S21_PI;
    } else {
      x += 2 * S21_PI;
    }
  }
  if (x < 0) {
    x = -x;
    sign = -1;
  }
  for (double i = 0; i < 100; i++) {
    sum_sin += s21_pow(-1, i) * s21_pow(x, 2 * i + 1) / s21_fact(2 * i + 1);
  }
  return sum_sin * sign;
}
