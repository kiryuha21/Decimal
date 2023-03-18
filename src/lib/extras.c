#include "../s21_decimal.h"

#include <math.h>

int s21_floor(s21_decimal value, s21_decimal *result) {
  *result = value;

  s21_truncate(value, result);

  int exp = (int)get_exponent(&value);
  if (exp > 0 && get_sign(&value) == NEGATIVE) {
    result->bits[get_elder_bit_index(&value)] += 1;
  }

  return OK;
}

int s21_round(s21_decimal value, s21_decimal *result) {
    reduce_exponent(&value);

    int exp = (int) get_exponent(&value);
    int first_integer_bit_ind = get_first_integer_bit_index(&value);
    for (int i = first_integer_bit_ind; i <= 2; ++i) {
        unsigned int mod = (unsigned int) pow(10.0, (double) (exp % 10));
        for (; mod > 0; mod /= 10) {

        }
    }
}

int s21_truncate(s21_decimal value, s21_decimal *result) {
  *result = value;

  int exp = (int)get_exponent(&value);

  for (int i = 2; exp > 0 && i >= 0; --i) {
    for (; result->bits[i] > 0 && exp > 0; --exp) {
      result->bits[i] /= 10;
    }
  }

  return OK;
}

int s21_negate(s21_decimal value, s21_decimal *result) {
  *result = value;
  if (!is_zero(result)) {
    change_sign(result);
  }
  return OK;
}
