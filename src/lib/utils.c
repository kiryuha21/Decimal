#include <math.h>
#include <stdio.h>

#include "../s21_decimal.h"

int get_bit(unsigned int val, int index) {
  return (val & ((unsigned int)1 << index)) ? 1 : 0;
}

int get_decimal_bit(const s21_decimal* val, int index) {
  return (get_bit(val->bits[index / BITS_IN_INT], index % BITS_IN_INT));
}

void set_bit(unsigned int* val, int index, int bit) {
  if (bit == 1) {
    (*val) |= 1 << index;
  } else {
    (*val) &= ~(1 << index);
  }
}

int get_sign(const s21_decimal* val) {
  return get_bit(val->bits[3], SIGN_BIT) ? NEGATIVE : POSITIVE;
}

void set_sign(s21_decimal* val, int sign) {
  set_bit(&val->bits[3], SIGN_BIT, sign);
}

void change_sign(s21_decimal* val) {
  int sign = NEGATIVE;
  if (get_sign(val) == NEGATIVE) {
    sign = POSITIVE;
  }
  set_sign(val, sign);
}

unsigned int get_exponent(const s21_decimal* val) {
  return (val->bits[3] & EXPONENT_MASK) >> 16;
}

void zero_bits(s21_decimal* val) {
  for (int i = 0; i < 32; ++i) {
    if (get_bit(NULL_BITS_MASK, i) == 0) {
      set_bit(&val->bits[3], i, 0);
    }
  }
}

void set_exponent(s21_decimal* val, unsigned int exp) {
  for (int i = 0; i < 8; ++i) {
    set_bit(&val->bits[3], 16 + i, (int)(exp % 2));
    exp /= 2;
  }
}

int is_zero(const s21_decimal* val) {
  int res = FALSE;
  if (val->bits[0] == 0 && val->bits[1] == 0 && val->bits[2] == 0) {
    res = TRUE;
  }
  return res;
}

int add_int_to_dec(s21_decimal val, int num, s21_decimal* res) {
  null_decimal_val(res);

  int overflow = num;

  for (int i = 0; i <= 2; ++i) {
    unsigned long long bit_val = (unsigned long long)val.bits[i] + overflow;
    res->bits[i] = bit_val % OVERFLOW_BIT;
    overflow = (int)(bit_val / OVERFLOW_BIT);
  }

  return overflow;
}

int sub_int_fr_dec(s21_decimal val, int num, s21_decimal* res) {
  null_decimal_val(res);

  unsigned int overflow = num;

  for (int i = 0; i <= 2; ++i) {
    unsigned long long bit_val;
    if (overflow > val.bits[i]) {
      bit_val = OVERFLOW_BIT + val.bits[i] - overflow;
      overflow = 1;
    } else {
      bit_val = (unsigned long long)val.bits[i] - overflow;
      overflow = 0;
    }
    res->bits[i] = bit_val % OVERFLOW_BIT;
  }

  return overflow;
}

int mul_dec_on_int(s21_decimal val, int num, s21_decimal* res) {
  res->bits[3] = val.bits[3];

  unsigned long long bit_val, overflow = 0;

  for (int i = 0; i <= 2; ++i) {
    bit_val = (unsigned long long)val.bits[i] * num + overflow;
    res->bits[i] = bit_val % OVERFLOW_BIT;
    overflow = bit_val / OVERFLOW_BIT;
  }

  return (int)overflow;
}

int mul_without_signs(s21_decimal a, s21_decimal b, s21_decimal* rh,
                      s21_decimal* rl) {
  null_decimal_val(rh);
  null_decimal_val(rl);

  s21_decimal c = DEFAULT_DECIMAL;

  for (int i = 96; i > 0; --i) {
    if (get_decimal_bit(&b, 0) == 1) {
      add_same_signs(c, a, &c);
    }
    right_shift_2n(&c, &b);
  }

  *rh = c;
  *rl = b;

  return OK;
}

int div_dec_on_int(s21_decimal val, int num, s21_decimal* res) {
  if (num == 0) {
    return ZERO_DIVISION;
  }

  unsigned long long bit_val, overflow = 0;

  for (int i = 2; i >= 0; --i) {
    bit_val = (unsigned long long)(val.bits[i] + overflow * OVERFLOW_BIT);
    res->bits[i] = bit_val / num;
    overflow = bit_val % num;
  }

  return (int)overflow;
}

int is_bigger_2n(s21_2n_decimal first, s21_2n_decimal second) {
  for (int i = 5; i >= 0; --i) {
    if (first.bits[i] > second.bits[i]) {
      return TRUE;
    } else if (second.bits[i] > first.bits[i]) {
      return FALSE;
    }
  }
  return FALSE;
}

int div_without_signs_1n(s21_decimal a, s21_decimal b, s21_decimal* rh,
                         s21_decimal* rl) {
  *rl = a;

  s21_decimal c = DEFAULT_DECIMAL;

  for (int i = 95; i >= 0; --i) {
    left_shift_2n(rh, rl);
    if (is_bigger(b, *rh) == TRUE) {
      set_bit(&c.bits[i / 32], i % 32, 0);
    } else {
      set_bit(&c.bits[i / 32], i % 32, 1);
      sub_diff_signs(*rh, b, rh);
    }
  }

  *rl = c;
  swap_decimals(rl, rh);

  return OK;
}

int div_without_signs(s21_2n_decimal a, s21_2n_decimal b, s21_2n_decimal* rh,
                      s21_2n_decimal* rl) {
  *rl = a;

  s21_2n_decimal c = DEFAULT_DECIMAL;

  for (int i = 191; i >= 0; --i) {
    left_shift_4n(rh, rl);
    if (is_bigger_2n(b, *rh) == TRUE) {
      set_bit(&c.bits[i / 32], i % 32, 0);
    } else {
      set_bit(&c.bits[i / 32], i % 32, 1);
      sub_diff_signs_2n(*rh, b, rh);
    }
  }

  *rl = c;
  swap_decimals_2n(rl, rh);

  return OK;
}

int add_same_signs(s21_decimal value_1, s21_decimal value_2,
                   s21_decimal* result) {
  set_sign(result, get_sign(&value_1));
  int overflow = 0;
  for (int i = 0; i < 3; ++i) {
    unsigned long long bit_val =
        (unsigned long long)value_1.bits[i] + value_2.bits[i] + overflow;
    result->bits[i] = bit_val % OVERFLOW_BIT;
    overflow = (int)(bit_val / OVERFLOW_BIT);
  }

  return overflow;
}

int handle_enough(s21_decimal* result, s21_decimal* v1, s21_decimal v2) {
  s21_decimal mh = DEFAULT_DECIMAL, ml = DEFAULT_DECIMAL;
  div_without_signs_1n(*v1, v2, &mh, &ml);
  if (is_zero(&mh) == FALSE) {
    *v1 = ml;
  }
  mul_dec_on_int(*v1, 10, v1);
  s21_decimal temp = *result;
  int ret = add_same_signs(temp, mh, &temp);
  if (ret == OK) {
    *result = temp;
  }
  return ret;
}

int check_bank(s21_decimal* result, s21_decimal v1, s21_decimal v2) {
  s21_decimal mh = DEFAULT_DECIMAL, ml = DEFAULT_DECIMAL;
  div_without_signs_1n(v1, v2, &mh, &ml);
  if (mh.bits[0] >= 5) {
    return add_int_to_dec(*result, 1, result) == OK
               ? OK
               : (get_sign(result) == NEGATIVE ? TOO_SMALL : TOO_LARGE);
  }
  return OK;
}

int sub_diff_signs(s21_decimal value_1, s21_decimal value_2,
                   s21_decimal* result) {
  unsigned long long int overflow = 0;
  unsigned long long int bit_val;
  for (int i = 0; i < 3; ++i) {
    if (value_1.bits[i] >= value_2.bits[i] + overflow) {
      bit_val =
          (unsigned long long)value_1.bits[i] - value_2.bits[i] - overflow;
      overflow = 0;
    } else {
      bit_val = OVERFLOW_BIT - value_2.bits[i] + value_1.bits[i] - overflow;
      overflow = 1;
    }
    result->bits[i] = bit_val;
  }

  return (int)overflow;
}

int sub_diff_signs_2n(s21_2n_decimal value_1, s21_2n_decimal value_2,
                      s21_2n_decimal* result) {
  unsigned long long int overflow = 0;
  unsigned long long int bit_val;
  for (int i = 0; i < 6; ++i) {
    if (value_1.bits[i] >= value_2.bits[i] + overflow) {
      bit_val =
          (unsigned long long)value_1.bits[i] - value_2.bits[i] - overflow;
      overflow = 0;
    } else {
      bit_val = OVERFLOW_BIT - value_2.bits[i] + value_1.bits[i] - overflow;
      overflow = 1;
    }
    result->bits[i] = bit_val;
  }

  return (int)overflow;
}

int scale_decimals(s21_decimal* num1, s21_decimal* num2, unsigned int* exp,
                   s21_decimal* overflow) {
  reduce_exponent(num1);
  reduce_exponent(num2);

  unsigned int exp1 = get_exponent(num1), exp2 = get_exponent(num2);

  s21_decimal temp;
  if (exp1 > exp2) {
    temp = *num2;
    *exp = exp1;
    *num2 = temp;
  } else {
    temp = *num1;
    *exp = exp2;
    *num1 = temp;
  }

  set_exponent(&temp, *exp);
  if (overflow != NULL) {
    null_decimal(overflow);
  }
  for (unsigned int i = *exp == exp2 ? exp1 : exp2; i < *exp; ++i) {
    int ret = mul_dec_on_int(temp, 10, &temp);
    if (overflow != NULL) {
      mul_dec_on_int(*overflow, 10, overflow);
      add_int_to_dec(*overflow, ret, overflow);
    }
  }

  if (exp1 > exp2) {
    *num2 = temp;
    return TOO_SMALL;
  } else {
    *num1 = temp;
    return TOO_LARGE;
  }
}

s21_2n_decimal convert(s21_decimal val) {
  s21_2n_decimal res = DEFAULT_DECIMAL;
  for (int i = 0; i < 3; ++i) {
    res.bits[i] = val.bits[i];
  }
  res.bits[6] = val.bits[3];
  return res;
}

s21_decimal rconvert(s21_2n_decimal val) {
  s21_decimal res = DEFAULT_DECIMAL;
  for (int i = 0; i < 3; ++i) {
    res.bits[i] = val.bits[i];
  }
  res.bits[3] = val.bits[6];
  return res;
}

s21_decimal rsconvert(s21_2n_decimal val) {
  s21_decimal res = DEFAULT_DECIMAL;
  for (int i = 3; i < 6; ++i) {
    res.bits[i - 3] = val.bits[i];
  }
  return res;
}

int scale_2n_decimal(s21_2n_decimal* val1, s21_2n_decimal* val2,
                     unsigned int* exp) {
  s21_decimal overflow, value1 = rconvert(*val1), value2 = rconvert(*val2);
  int res = scale_decimals(&value1, &value2, exp, &overflow);
  for (int i = 0; i < 3; ++i) {
    val1->bits[i] = value1.bits[i];
    val2->bits[i] = value2.bits[i];
  }

  if (res == TOO_LARGE) {
    for (int i = 0; i < 3; ++i) {
      val1->bits[i + 3] = overflow.bits[i];
    }
  } else {
    for (int i = 0; i < 3; ++i) {
      val2->bits[i + 3] = overflow.bits[i];
    }
  }

  return res;
}

void null_decimal(s21_decimal* val) {
  for (int i = 0; i < 4; ++i) {
    val->bits[i] = 0;
  }
}

void null_decimal_val(s21_decimal* val) {
  for (int i = 0; i <= 2; ++i) {
    val->bits[i] = 0;
  }
}

void swap_decimals(s21_decimal* val1, s21_decimal* val2) {
  s21_decimal cp = *val2;
  *val2 = *val1;
  *val1 = cp;
}

void swap_decimals_2n(s21_2n_decimal* val1, s21_2n_decimal* val2) {
  s21_2n_decimal cp = *val2;
  *val2 = *val1;
  *val1 = cp;
}

void reduce_exponent(s21_decimal* val) {
  zero_bits(val);
  if (is_zero(val) == TRUE) {
    set_sign(val, POSITIVE);
    set_exponent(val, 0);
    return;
  }

  unsigned int exp = get_exponent(val);
  s21_decimal reduced = *val;

  int ret = OK;
  while (exp > 0 && is_zero(&reduced) == FALSE) {
    ret = div_dec_on_int(reduced, 10, &reduced);
    if (ret != OK) {
      set_exponent(val, exp);
      return;
    }
    *val = reduced;
    --exp;
  }

  set_exponent(val, exp);
}

int get_elder_bit_index(const s21_decimal* val) {
  if (val->bits[1] == 0) {
    return 0;
  }

  if (val->bits[2] == 0) {
    return 1;
  }

  return 2;
}

int left_shift(s21_decimal* val) {
  int overflow = 0;

  for (int i = 0; i < 3; ++i) {
    int next_overflow =
        get_decimal_bit(val, (BITS_IN_INT - 1) + i * BITS_IN_INT);
    val->bits[i] = (val->bits[i] << 1) + overflow;
    overflow = next_overflow;
  }

  return overflow;
}

int left_shift_2n(s21_decimal* dh, s21_decimal* dl) {
  int ret = left_shift(dl);
  int res = left_shift(dh);
  set_bit(&dh->bits[0], 0, ret);
  return res;
}

int left_shift_2n_dec(s21_2n_decimal* val) {
  int overflow = 0;

  for (int i = 0; i < 6; ++i) {
    int next_overflow =
        get_bit(val->bits[i], (BITS_IN_INT - 1) + i * BITS_IN_INT);
    val->bits[i] = (val->bits[i] << 1) + overflow;
    overflow = next_overflow;
  }

  return overflow;
}

int left_shift_4n(s21_2n_decimal* dh, s21_2n_decimal* dl) {
  int ret = left_shift_2n_dec(dl);
  int res = left_shift_2n_dec(dh);
  set_bit(&dh->bits[0], 0, ret);
  return res;
}

int right_shift(s21_decimal* val) {
  int overflow = 0;

  for (int i = 2; i >= 0; --i) {
    int next_overflow = get_decimal_bit(val, i * BITS_IN_INT);
    val->bits[i] = (val->bits[i] >> 1) + (overflow * (OVERFLOW_BIT >> 1));
    overflow = next_overflow;
  }

  return overflow;
}

void right_shift_2n(s21_decimal* dh, s21_decimal* dl) {
  int ret = right_shift(dh);
  right_shift(dl);
  set_bit(&dl->bits[2], (BITS_IN_INT - 1), ret);
}

void handle_decimal_inc(s21_decimal* val) {
  val->bits[0] += 1;
  if (val->bits[0] != 0) {
    return;
  }

  val->bits[1] += 1;
  if (val->bits[1] != 0) {
    return;
  }

  val->bits[2] += 1;
}

// return TRUE if swapped
int make_first_bigger_no_signs(s21_decimal* first, s21_decimal* second) {
  int ret = is_bigger(*second, *first);
  if (ret == TRUE) {
    swap_decimals(first, second);
  }
  return ret;
}

int is_bigger(s21_decimal first, s21_decimal second) {
  for (int i = 2; i >= 0; --i) {
    if (first.bits[i] > second.bits[i]) {
      return TRUE;
    } else if (second.bits[i] > first.bits[i]) {
      return FALSE;
    }
  }
  return FALSE;
}

int is_equal(s21_decimal first, s21_decimal second) {
  return is_bigger(first, second) == is_bigger(second, first) ? TRUE : FALSE;
}

int decimal_size_10(s21_decimal val) {
  if (is_zero(&val) == TRUE) {
    return 0;
  }
  s21_decimal temp = {{1, 0, 0, 0}};

  int ret = OK;
  int exp = 0;
  while (is_bigger(val, temp) && ret == OK) {
    ++exp;
    ret = mul_dec_on_int(temp, 10, &temp);
  }

  if (is_equal(val, temp) && ret == OK) {
    ++exp;
  }

  return exp;
}

int try_add_overflow(s21_decimal* val, s21_decimal overflow) {
  if (is_zero(&overflow)) {
    reduce_exponent(val);
    return OK;
  }

  unsigned int size = decimal_size_10(overflow);

  if (get_exponent(val) < size) {
    return get_sign(val) == POSITIVE ? TOO_LARGE : TOO_SMALL;
  }

  return bank_round(val, overflow);
}

int should_bround_up(unsigned long long extended_bit, int thrown_digits,
                     unsigned int low_integer) {
  return extended_bit == 5 && thrown_digits == 0 && low_integer % 2 == 1;
}

int should_round_up(unsigned long long extended_bit, int thrown_digits) {
  return extended_bit % 10 >= 6 ||
         (extended_bit % 10 == 5 && thrown_digits == 1);
}

int bank_round(s21_decimal* val, s21_decimal overflow) {
  int exp_change = 0;
  int thrown_digits = 0;
  unsigned long long bit_val = 0;
  while (is_zero(&overflow) == FALSE) {
    ++exp_change;

    unsigned long long mod = div_dec_on_int(overflow, 10, &overflow);

    for (int i = 2; i >= 0; --i) {
      bit_val = (unsigned long long)(val->bits[i] + mod * OVERFLOW_BIT);
      val->bits[i] = bit_val / 10;
      mod = bit_val % 10;
      if (mod != 0) {
        thrown_digits = 1;
      }
    }
  }

  if ((should_round_up(bit_val, thrown_digits) ||
       should_bround_up(bit_val, thrown_digits, val->bits[0] % 10)) &&
      exp_change != 0) {
    int ret = add_int_to_dec(*val, 1, val);
    if (ret != OK) {
      return get_sign(val) == POSITIVE ? TOO_LARGE : TOO_SMALL;
    }
  }

  set_exponent(val, get_exponent(val) - exp_change);
  reduce_exponent(val);

  return OK;
}
