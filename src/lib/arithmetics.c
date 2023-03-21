#include <stdlib.h>

#include "../s21_decimal.h"

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  if (!result) {
    return ERROR;
  }

  unsigned int scale;
  s21_decimal overflow = {0};
  scale_decimals(&value_1, &value_2, &scale, &overflow);

  set_exponent(result, scale);
  set_sign(result, get_sign(&value_1));

  if (get_sign(&value_1) == get_sign(&value_2)) {
    int additional_bit = add_same_signs(value_1, value_2, result);
    add_int_to_dec(overflow, additional_bit, &overflow);
    return try_add_overflow(result, overflow);
  }

  if (make_first_bigger_no_signs(&value_1, &value_2) == TRUE) {
    change_sign(result);
  }

  int additional_bit = sub_diff_signs(value_1, value_2, result);
  sub_int_fr_dec(overflow, additional_bit, &overflow);
  return try_add_overflow(result, overflow);
}

int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  change_sign(&value_2);

  return s21_add(value_1, value_2, result);
}

int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  if (!result) {
    return ERROR;
  }

  null_decimal(result);

  s21_decimal rh, rl;

  mul_without_signs(value_1, value_2, &rh, &rl);
  set_exponent(&rl, get_exponent(&value_1) + get_exponent(&value_2));

  int ret = try_add_overflow(&rl, rh);
  if (ret != OK) {
    return ret;
  }

  *result = rl;

  if (get_sign(&value_1) != get_sign(&value_2)) {
    set_sign(result, NEGATIVE);
  } else {
    set_sign(result, POSITIVE);
  }

  reduce_exponent(result);

  return OK;
}

int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  if (!result) {
    return ERROR;
  }

  null_decimal(result);
  if (is_zero(&value_2) == TRUE) {
    return ZERO_DIVISION;
  }

  s21_decimal rh, rl;

  unsigned int scale;
  s21_decimal overflow;
  int ret = scale_decimals(&value_1, &value_2, &scale, &overflow);

  ret = div_without_signs(value_1, value_2, &rh, &rl);
  if (ret != OK) {
    return ret;
  }
  *result = rh;
  reduce_exponent(result);

  if (get_exponent(&value_1) >= get_exponent(&value_2)) {
    set_exponent(&rh, get_exponent(&value_1) - get_exponent(&value_2));
  } else {
    for (unsigned int i = get_exponent(&value_2); i < get_exponent(&value_1);
         ++i) {
      ret = mul_dec_on_int(*result, 10, result);
      if (ret != OK) {
        return ret;
      }
    }
    set_exponent(result, 0);
  }

  return ret;
}

int s21_mod(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  if (!result) {
    return ERROR;
  }

  null_decimal(result);
  if (is_zero(&value_2) == TRUE) {
    return ZERO_DIVISION;
  }

  s21_decimal rh, rl;

  unsigned int scale;
  s21_decimal overflow;
  scale_decimals(&value_1, &value_2, &scale, &overflow);

  int ret = div_without_signs(value_1, value_2, &rh, &rl);

  set_exponent(&rl, scale);
  reduce_exponent(&rl);

  *result = rl;

  return ret;
}
