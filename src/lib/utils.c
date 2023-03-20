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

void set_decimal_bit(s21_decimal* val, int index, int bit) {
  set_bit(&val->bits[index / BITS_IN_INT], index % BITS_IN_INT, bit);
}

int get_higher_bit(unsigned int val) {
  int res = -1;
  for (int i = 0; val != 0; ++i) {
    if ((val & 1) == 1) {
      res = i;
    }
    val = val >> 1;
  }
  return res;
}

int decimal_size(s21_decimal val) {
  for (int i = 2; i >= 0; --i) {
    if (val.bits[i] != 0) {
      return get_higher_bit(val.bits[i]) + BITS_IN_INT * i;
    }
  }
  return 0;
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
  null_decimal(res);

  int overflow = num;

  for (int i = 0; i <= 2; ++i) {
    unsigned long long bit_val = val.bits[i] + overflow;
    res->bits[i] = bit_val % OVERFLOW_BIT;
    overflow = (int)(bit_val / OVERFLOW_BIT);
  }

  return overflow;
}

int sub_int_fr_dec(s21_decimal val, int num, s21_decimal* res) {
  null_decimal(res);

  int overflow = num;

  for (int i = 0; i <= 2; ++i) {
    unsigned long long bit_val;
    if (overflow > val.bits[i]) {
      bit_val = OVERFLOW_BIT + val.bits[i] - overflow;
      overflow = 1;
    } else {
      bit_val = val.bits[i] - overflow;
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

int mul_without_signs(s21_decimal val1, s21_decimal val2, s21_decimal* res) {
  null_decimal(res);
  make_first_bigger_no_signs(&val1, &val2);

  int ret = OK;
  while (is_zero(&val2) == FALSE) {
    int mod = 0;
    right_shift(&val2, &mod);
    if (mod == 1) {
      ret = add_same_signs(*res, val1, res);
      if (ret != OK) {
        return ret;
      }
    }

    if (is_zero(&val2) == FALSE) {
      ret = left_shift(&val1);
      if (ret != OK) {
        return ret;
      }
    }
  }

  return ret;
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

int sub_diff_signs(s21_decimal value_1, s21_decimal value_2,
                   s21_decimal* result) {
  unsigned long long int overflow = 0;
  unsigned long long int bit_val;
  for (int i = 0; i < 3; ++i) {
    if (value_1.bits[i] >= value_2.bits[i] + overflow) {
      bit_val = value_1.bits[i] - value_2.bits[i] - overflow;
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

void null_decimal(s21_decimal* val) {
  for (int i = 0; i < 4; ++i) {
    val->bits[i] = 0;
  }
}

void swap_decimals(s21_decimal* val1, s21_decimal* val2) {
  s21_decimal cp = *val2;
  *val2 = *val1;
  *val1 = cp;
}

void reduce_exponent(s21_decimal* val) {
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

s21_decimal create_decimal(unsigned int bit0, unsigned int bit1,
                           unsigned int bit2, unsigned int bit3) {
  s21_decimal res = {{bit0, bit1, bit2, bit3}};
  return res;
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

int get_first_integer_bit_index(const s21_decimal* val) {
  int exp = (int)get_exponent(val);
  if (exp < 10) {
    return 0;
  }

  if (exp < 20) {
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

  if (overflow != 0) {
    return TOO_LARGE;
  }

  return OK;
}

int right_shift(s21_decimal* val, int* mod) {
  int overflow = 0;

  for (int i = 2; i >= 0; --i) {
    int next_overflow = get_decimal_bit(val, i * BITS_IN_INT);
    val->bits[i] = (val->bits[i] >> 1) + (overflow * (OVERFLOW_BIT >> 1));
    overflow = next_overflow;
  }

  *mod = overflow;

  return OK;
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

float remove_elder_digit(float val) {
  int digits = 0;
  int temp = (int)val;
  for (; temp > 0; temp /= 10, ++digits) {
  }

  temp = (int)val;
  int result = 0;
  for (int i = 0; i < digits - 1; ++i, temp /= 10) {
    result += temp % 10 * (int)pow(10.0, (double)i);
  }

  return val - (float)((int)val) + (float)result;
}

void print_decimal(const s21_decimal* val) {
  printf("\nsign = %s\nexp = %u\nbit[2] - %.8X\nbit[1] - %.8X\nbit[0] - %.8X\n",
         get_sign(val) == POSITIVE ? "POSITIVE" : "NEGATIVE", get_exponent(val),
         val->bits[2], val->bits[1], val->bits[0]);
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
  s21_decimal temp = {1, 0, 0, 0};

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

  int size = decimal_size_10(overflow);

  if (get_exponent(val) < size) {
    return TOO_LARGE;
  }

  return bank_round(val, overflow);
}

int bank_round(s21_decimal* val, s21_decimal overflow) {
  int exp_change = 0;
  while (is_zero(&overflow) == FALSE) {
    ++exp_change;

    unsigned long long mod = div_dec_on_int(overflow, 10, &overflow);

    // TODO: Make real bank round for last sym
    for (int i = 2; i >= 0; --i) {
      unsigned long long bit_val =
          (unsigned long long)(val->bits[i] + mod * OVERFLOW_BIT);
      val->bits[i] = bit_val / 10;
      mod = bit_val % 10;
    }
  }

  if (get_exponent(val) < exp_change) {
    return ERROR;
  }
  set_exponent(val, get_exponent(val) - exp_change);
  reduce_exponent(val);

  return OK;
}