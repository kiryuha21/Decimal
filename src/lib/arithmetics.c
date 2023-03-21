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

  unsigned int scale;
  s21_2n_decimal val1 = convert(value_1), val2 = convert(value_2),
                 rh = DEFAULT_DECIMAL, rl = DEFAULT_DECIMAL;
  int ret = scale_2n_decimal(&val1, &val2, &scale);

  ret = div_without_signs(val1, val2, &rh, &rl);
  if (ret != OK) {
    return ret;
  }
  s21_decimal rh_1n1 = rconvert(rh), rh_1n2 = rsconvert(rh),
              rl_1n1 = rconvert(rl), rl_1n2 = rsconvert(rl);

  ret = try_add_overflow(&rh_1n1, rh_1n2);
  ret = try_add_overflow(&rl_1n1, rl_1n2);

  *result = rh_1n1;
  reduce_exponent(result);

  set_sign(result,
           get_sign(&value_1) == get_sign(&value_2) ? POSITIVE : NEGATIVE);
  if (get_exponent(&value_1) >= get_exponent(&value_2)) {
    set_exponent(result, get_exponent(&value_1) - get_exponent(&value_2));
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

  s21_decimal v2 = value_2;
  v2.bits[3] = 0;
  s21_decimal v1 = rl_1n1;
  v1.bits[3] = 0;

  while (is_zero(&v1) == FALSE && get_exponent(result) < 28) {
    ret = handle_enough(result, &v1, v2);
    if (ret != OK) {
      return check_bank(result, v1, v2);
    }
    s21_decimal temp = *result;
    ret = mul_dec_on_int(temp, 10, &temp);
    if (ret != OK) {
      return check_bank(result, v1, v2);
    }
    *result = temp;
    set_exponent(result, get_exponent(result) + 1);
  }

  reduce_exponent(result);
  return check_bank(result, v1, v2);
}

int s21_mod(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  if (!result) {
    return OK;
  }

  null_decimal(result);
  if (is_zero(&value_2) == TRUE) {
    return ZERO_DIVISION;
  }

  unsigned int scale;
  s21_2n_decimal val1 = convert(value_1), val2 = convert(value_2),
                 rh = DEFAULT_DECIMAL, rl = DEFAULT_DECIMAL;
  int ret = scale_2n_decimal(&val1, &val2, &scale);

  ret = div_without_signs(val1, val2, &rh, &rl);
  if (ret != OK) {
    return ret;
  }
  s21_decimal rl_1n1 = rconvert(rl), rl_1n2 = rsconvert(rl);

  ret = try_add_overflow(&rl_1n1, rl_1n2);
  if (ret != OK) {
    return ret;
  }

  *result = rl_1n1;

  set_exponent(result, scale);
  set_sign(result, get_sign(&value_1));
  reduce_exponent(result);

  return ret;
}
