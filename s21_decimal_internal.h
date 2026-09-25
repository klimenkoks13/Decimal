#ifndef S21_DECIMAL_INTERNAL_H
#define S21_DECIMAL_INTERNAL_H

#include "s21_decimal.h"

int s21_get_sign(s21_decimal value);
void s21_set_sign(s21_decimal *value, int sign);
int s21_get_scale(s21_decimal value);
void s21_set_scale(s21_decimal *value, int scale);
void s21_zero_decimal(s21_decimal *value);
void s21_copy_decimal(s21_decimal src, s21_decimal *dst);
int s21_is_zero(s21_decimal value);
int s21_mantissa_is_zero(s21_decimal value);

#endif