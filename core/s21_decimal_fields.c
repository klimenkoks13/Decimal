#include "../s21_decimal_internal.h"

#include <stddef.h>
#include <stdint.h>

// накладываем маску знака, возвращаем 1 на минус 0 на плюс
int s21_get_sign(s21_decimal value) {
  return value.bits[3] & S21_SIGN_MASK ? 1 : 0;
}

// устанавливаем знак
void s21_set_sign(s21_decimal *value, int sign) {
  value->bits[3] &= ~S21_SIGN_MASK; // обнуляем знак
  if (sign)
    value->bits[3] |= S21_SIGN_MASK;
}

// узнаем точность, накладываем маску точности и сдвигаемся на 16 бит, так как
// там хранится точнность
int s21_get_scale(s21_decimal value) {
  return (value.bits[3] & S21_SCALE_MASK) >> 16;
}

// обнуляем точность, ставим новую с 16 бита
void s21_set_scale(s21_decimal *value, int scale) {
  value->bits[3] &= ~S21_SCALE_MASK;
  value->bits[3] |= (scale << 16) & S21_SCALE_MASK;
}

// обнуляем
void s21_zero_decimal(s21_decimal *value) {
  for (int i = 0; i < 4; i++) {
    value->bits[i] = 0;
  }
}

// делаем копию
void s21_copy_decimal(s21_decimal src, s21_decimal *dst) {
  if (dst != NULL) {
    for (int i = 0; i < 4; i++) {
      dst->bits[i] = src.bits[i];
    }
  }
}

// 3 не смотрим, так как знак и точность не влияют на ноль
int s21_is_zero(s21_decimal value) {
  return value.bits[0] == 0 && value.bits[1] == 0 && value.bits[2] == 0;
}
