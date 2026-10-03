#include "../s21_decimal_internal.h"

#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#define MAX(a, b) (((a) > (b)) ? (a) : (b))

int s21_align_scales(s21_decimal *a, s21_decimal *b) {
	int exit_code = 0;
	s21_decimal a_tmp =  *a;
	s21_decimal b_tmp =  *b;
	int a_scale = s21_get_scale(a_tmp);
	int b_scale = s21_get_scale(b_tmp);
	if (a_scale != b_scale) {
		int max_scale =  MAX(a_scale, b_scale);
		int min_scale =  MIN(a_scale, b_scale);
		int delta = max_scale - min_scale;
		if (a_scale < b_scale) {
			for(int i = 0; i < delta && exit_code == 0; i++) {
				exit_code = s21_mul_by_10(&a_tmp); 
			}
			s21_set_scale(&a_tmp, max_scale);
		}
		else {
			for(int i = 0; i < delta && exit_code == 0; i++) {
				exit_code = s21_mul_by_10(&b_tmp); 
			}
			s21_set_scale(&b_tmp, max_scale);
		}
		if (!exit_code) {
			*a = a_tmp;
			*b = b_tmp;
		}
	}
	return exit_code;
}	

int s21_increase_scale(s21_decimal *value, int delta) {
	int exit_code = 0;
	s21_decimal tmp =  *value;
	int scale = s21_get_scale(tmp);

	if (scale + delta > S21_MAX_SCALE) exit_code = 1;

	for(int i = 0; i < delta && exit_code == 0; i++) {
		exit_code = s21_mul_by_10(&tmp); 
	}
		
	if (!exit_code) {
		s21_set_scale(&tmp, scale + delta);
		*value = tmp;
	}
	return exit_code;
}

int s21_decrease_scale(s21_decimal *value, int delta) {
	return 0;
}

int s21_normalize_scale(s21_decimal *value) {
	return 0;
}

int s21_fit_scale(s21_decimal *value) {
	return 0;
}