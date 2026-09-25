#ifndef S21_DECIMAL_INTERNAL_H
#define S21_DECIMAL_INTERNAL_H

#include "s21_decimal.h"

#define S21_MAX_SCALE 28
#define S21_SIGN_MASK 0x80000000u
#define S21_SCALE_MASK 0x00FF0000u

int s21_get_sign(s21_decimal value);
void s21_set_sign(s21_decimal *value, int sign);
int s21_get_scale(s21_decimal value);
void s21_set_scale(s21_decimal *value, int scale);
void s21_zero_decimal(s21_decimal *value);
void s21_copy_decimal(s21_decimal src, s21_decimal *dst);
int s21_is_zero(s21_decimal value);
int s21_mantissa_is_zero(s21_decimal value);

int s21_get_bit(s21_decimal value, int bit_index);
void s21_set_bit(s21_decimal *value, int bit_index, int bit);
void s21_shift_left(s21_decimal *value, int shift);
void s21_shift_right(s21_decimal *value, int shift);
int s21_cmp_mantissa(s21_decimal a, s21_decimal b);
int s21_add_mantissa(s21_decimal a, s21_decimal b, s21_decimal *res);
int s21_sub_mantissa(s21_decimal a, s21_decimal b, s21_decimal *res);
int s21_mul_mantissa(s21_decimal a, s21_decimal b, s21_decimal *res);
int s21_div_mantissa(s21_decimal a, s21_decimal b, s21_decimal *res,
                     s21_decimal *rem);
int s21_mul_by_10(s21_decimal *value);
int s21_div_by_10(s21_decimal *value, int *remainder);
int s21_get_mantissa_digits(s21_decimal value);

#endif