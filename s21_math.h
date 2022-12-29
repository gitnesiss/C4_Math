#ifndef SRC_S21_MATH_H_
#define SRC_S21_MATH_H_

#include <stdlib.h>

#define S21_EPS 1e-16
#define S21_NAN 0.0 / 0.0
#define S21_INF 1.0 / 0.0
#define S21_EXP 2.7182818284590452353602874713526624
#define S21_LOG_10 2.302585092994046
#define S21_LOG_2 0.693147180559945309417232121458
#define S21_PI 3.14159265358979323846264338327950288
#define S21_2_PI 6.2831853
#define S21_PI_2 1.57079632
#define S21_PI_3 1.04719755
#define S21_PI_6 0.52359877
#define S21_PI_4 0.78539816
#define S21_INT_MIN -2147483647
#define S21_INT_MAX 2147483647
#define is_fin(x) __builtin_isfinite(x)
#define is_nan(x) __builtin_isnan(x)
#define is_inf(x) __builtin_isinf(x)
#define s21_size_t unsigned long long
#define s21_NULL (void*)0
/*
 *  вычисляет абсолютное значение целого числа
*/
int s21_abs(int);

/*
 *  вычисляет арккосинус
*/
long double s21_acos(double);

/*
 *  вычисляет арксинус
*/
long double s21_asin(double);

/*
 *  вычисляет арктангенс
*/
long double s21_atan(double);

/*
 *  возвращает ближайшее целое число, не меньшее заданного значения
*/
long double s21_ceil(double);

/*
 *  вычисляет косинус
*/
long double s21_cos(double);

/*
 *  возвращает значение e, возведенное в заданную степень
*/
long double s21_exp(double);

/*
 *  вычисляет абсолютное значение числа с плавающей точкой
*/
long double s21_fabs(double);

/*
 *  возвращает ближайшее целое число, не превышающее заданное значение
*/
long double s21_floor(double);

/*
 *  остаток операции деления с плавающей точкой
*/
long double s21_fmod(double, double);

/*
 *  вычисляет натуральный логарифм
*/
long double s21_log(double);

/*
 *  возводит число в заданную степень
*/
long double s21_pow(double, double);

/*
 *  вычисляет синус
*/
long double s21_sin(double);

/*
 *  вычисляет квадратный корень
*/
long double s21_sqrt(double);

/*
 *  вычисляет тангенс
*/
long double s21_tan(double);

/*
 *  вычисляет факториал
*/
long double s21_fact(int);

#endif  // SRC_S21_MATH_H_
