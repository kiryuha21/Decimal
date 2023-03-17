#include "../s21_decimal.h"

int get_bit(unsigned int val, int index) {
  return (val & (1 << index)) ? 1 : 0;
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

int get_higher_bit(int val) {
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
    for (int i = 2; i >= 0; ++i) {
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
  for (int i = 0; i < 8 && exp > 0; ++i) {
    set_bit(&val->bits[3], 16 + i, (int)(exp % 2));
    exp /= 2;
  }
}

int is_zero(const s21_decimal* val) {
  int res = FALSE;
  if (val->bits[0] == 0 && val->bits[1] == 0 && val->bits[3] == 0) {
    res = TRUE;
  }
  return res;
}

int scal_mul(s21_decimal val, int num, s21_decimal* res) {
  set_sign(res, get_sign(&val));
  if (num < 0) {
    num = -num;
    change_sign(res);
  }

  int ret = OK;
  while (num != 0) {
    if (num % 2 == 1) {
      ret = s21_add(*res, val, res);
      if (ret != OK) {
        return ret;
      }
    }

    num /= 2;
    if (num != 0) {
      ret = left_shift(&val);
      if (ret != OK) {
        return ret;
      }
    }
  }

  return ret;
}

int scal_div(s21_decimal val, int num, s21_decimal* res, s21_decimal* mod) {
  if (num == 0) {
    return ZERO_DIVISION;
  }

  set_sign(res, get_sign(&val));
  if (num < 0) {
    num = -num;
    change_sign(res);
  }

  int ret = OK;

  null_decimal(mod);
  for (int i = decimal_size(val); i >= 0; --i) {
    ret = left_shift(res);
    if (ret != OK) {
      return ret;
    }
    ret = left_shift(mod);
    if (ret != OK) {
      return ret;
    }
    set_decimal_bit(mod, 0, get_decimal_bit(&val, i));
    if (mod->bits[0] >= num) {
      ret = s21_sub(*mod, create_decimal(num, 0, 0, 0), mod);
      if (ret != OK) {
        return ret;
      }
      set_decimal_bit(res, 0, 1);
    }
  }

  return ret;
}

int add_same_signs(const s21_decimal* value_1, const s21_decimal* value_2,
                   s21_decimal* result) {
  int ret = OK;
  set_sign(result, get_sign(value_1));
  unsigned long long int overflow = 0;
  for (int i = 0; i < 3; ++i) {
    unsigned long long int bit_val = value_1->bits[i] + value_2->bits[i];
    if (bit_val > MAX_BIT) {
      result->bits[i] = bit_val % MAX_BIT;
      overflow = 1;
    } else {
      result->bits[i] = bit_val;
      overflow = 0;
    }
  }
  if (overflow != 0) {
    ret = TOO_LARGE;
  }
  reduce_exponent(result);
  return ret;
}

s21_decimal decimal_abs(s21_decimal val) {
  s21_decimal res = val;
  set_sign(&res, POSITIVE);
  return res;
}

int sub_diff_signs(s21_decimal value_1, s21_decimal value_2,
                   s21_decimal* result) {
  int ret = OK;
  set_sign(result, get_sign(&value_1));
  if (s21_is_greater_or_equal(decimal_abs(value_1), decimal_abs(value_2)) ==
      FALSE) {
    swap_decimals(&value_1, &value_2);
  }
  unsigned long long int overflow = 0;
  unsigned long long int bit_val;
  for (int i = 0; i < 3; ++i) {
    if (value_1.bits[i] >= value_2.bits[i] + overflow) {
      bit_val = value_1.bits[i] - value_2.bits[i] - overflow;
      overflow = 0;
    } else {
      bit_val = MAX_BIT - value_2.bits[i] + value_1.bits[i] - overflow;
      overflow = 1;
    }
    result->bits[i] = bit_val;
  }
  if (overflow != 0) {
    ret = TOO_LARGE;
  }
  reduce_exponent(result);
  return ret;
}

int scale_decimals(s21_decimal* num1, s21_decimal* num2, unsigned int* exp) {
  int ret = OK;

  unsigned int exp1 = get_exponent(num1), exp2 = get_exponent(num2);

  if (exp1 > exp2) {
    *exp = exp1;
    for (unsigned int i = exp2; i < exp1 && ret == OK; ++i) {
      ret = scal_mul(*num2, 10, num2);
    }
  } else {
    *exp = exp2;
    for (unsigned int i = exp1; i < exp2 && ret == OK; ++i) {
      ret = scal_mul(*num1, 10, num1);
    }
  }

  return ret;
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
  unsigned int exp = get_exponent(val);
  s21_decimal reduced = *val, mod = DEFAULT_DECIMAL;

  while (exp > 0 && is_zero(&mod) == TRUE) {
    --exp;
    int ret = scal_div(reduced, 10, &reduced, &mod);
    if (ret != OK) {
      return;
    }
    if (is_zero(&mod)) {
      *val = reduced;
    }
  }

  set_exponent(val, exp);
}

s21_decimal create_decimal(unsigned int bit0, unsigned int bit1,
                           unsigned int bit2, unsigned int bit3) {
  s21_decimal res = {{bit0, bit1, bit2, bit3}};
  reduce_exponent(&res);
  return res;
}

int get_elder_bit_index(const s21_decimal* val) {
  if (val->bits[1] == 0) {
    return 2;
  }

  if (val->bits[0] == 0) {
    return 1;
  }

  return 0;
}

int left_shift(s21_decimal* val) {
  reduce_exponent(val);
  int overflow = get_bit(val->bits[0], SIGN_BIT);

  for (int i = 0; i < 3; ++i) {
    val->bits[i] = (val->bits[i] << 1) + overflow;
    overflow = get_bit(val->bits[i], SIGN_BIT);
  }

  if (overflow != 0) {
    return TOO_LARGE;
  }

  return OK;
}
