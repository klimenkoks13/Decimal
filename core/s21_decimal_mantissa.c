#include "../s21_decimal_internal.h"

#include <stdint.h>

int s21_get_bit(s21_decimal value, int bit_index) {
  int bit;
  int word = bit_index / 32;
  int offset = bit_index % 32;
  if (bit_index < 0 || bit_index > 95) { // проверяем что не выходит за пределы
    bit = 0;                             // ошибка
  } else {
    bit = ((uint32_t)value.bits[word] >> offset) &
          1; // сдвигаемя на остаток и берем младший бит
  }
  return bit;
}

void s21_set_bit(s21_decimal *value, int bit_index, int bit) {
  int word = bit_index / 32;
  int offset = bit_index % 32;
  if (bit_index < 0 || bit_index > 95) {
    return;
  }
  uint32_t mask =
      1u << offset; // передвигаем единичку на бит который нужно изменить
  if (bit) {
    value->bits[word] |= mask;
  } else {
    value->bits[word] &= ~mask;
  }
}

void s21_shift_left(s21_decimal *value, int shift) {
  if (shift <= 0) {
    return;
  } else if (shift >= 96) {
    value->bits[0] = 0;
    value->bits[1] = 0;
    value->bits[2] = 0;
  } else {
    for (int s = 0; s < shift; s++) {
      uint32_t carry = 0; // переносимый бит
      for (int word = 0; word < 3; word++) {
        uint32_t w = (uint32_t)value->bits[word];
        uint32_t next_carry =
            (w >> 31) & 1u; // сдвигаем старший бит в младший и запоминаем,
                            // уйдёт в следующее слово
        w = (w << 1) | carry; // сдвигаем и добавляем перенос из младшего слова
        value->bits[word] = (int)w;
        carry = next_carry; // перенос для следующего (старшего) слова
      }
    }
  }
}

void s21_shift_right(s21_decimal *value, int shift) {
  if (shift <= 0) {
    return;
  } else if (shift >= 96) {
    value->bits[0] = 0;
    value->bits[1] = 0;
    value->bits[2] = 0;
  } else {
    for (int s = 0; s < shift; s++) {
      uint32_t carry = 0;
      for (int word = 2; word >= 0; word--) {
        uint32_t w = (uint32_t)value->bits[word];
        uint32_t next_carry = w & 1u; // младший бит уйдёт вниз
        w = (w >> 1) | (carry << 31); // сдвигаем и добавляем перенос сверху
        value->bits[word] = (int)w;
        carry = next_carry;
      }
    }
  }
}

int s21_cmp_mantissa(s21_decimal a, s21_decimal b);
int s21_add_mantissa(s21_decimal a, s21_decimal b, s21_decimal *res);
int s21_sub_mantissa(s21_decimal a, s21_decimal b, s21_decimal *res);
int s21_mul_mantissa(s21_decimal a, s21_decimal b, s21_decimal *res);
int s21_div_mantissa(s21_decimal a, s21_decimal b, s21_decimal *res,
                     s21_decimal *rem);
int s21_mul_by_10(s21_decimal *value);
int s21_div_by_10(s21_decimal *value, int *remainder);
int s21_get_mantissa_digits(s21_decimal value);
