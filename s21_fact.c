#include "s21_math.h"

long double s21_fact(int n) {
    if (n == 0 || n == 1) {
        return 1;
    } else {
        return n * s21_fact(n - 1);
    }
}
