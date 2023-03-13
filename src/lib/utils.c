#include "../s21_decimal.h"

int get_bit(unsigned int val, int index) {
  return (val & (1 << index)) ? 1 : 0;
}

void set_bit(unsigned int* val, int index, int bit) {
  if (bit == 1) {
    (*val) |= 1 << index;
  } else {
    (*val) &= ~(1 << index);
  }
}

int get_sign(const s21_decimal* val) {
  return (val->bits[3] & (1 << SIGN_BIT)) ? NEGATIVE : POSITIVE;
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

int scal_mul(s21_decimal* val, unsigned int num) {
  int ret = OK;
  unsigned long long int overflow = 0;
  for (int i = 0; i < 3; ++i) {
    unsigned long long int bit_val = val->bits[i] * num + overflow;
    if (bit_val > MAX_BIT) {
      val->bits[i] = bit_val % MAX_BIT;
      overflow = (bit_val - bit_val % MAX_BIT) / MAX_BIT;
    } else {
      val->bits[i] *= num;
      overflow = 0;
    }
  }
  if (overflow != 0) {
    ret = TOO_LARGE;
  }
  return ret;
}

int add_one_sign_decimals(const s21_decimal* value_1,
                          const s21_decimal* value_2, s21_decimal* result) {
  int ret = OK;
  unsigned long long int overflow = 0;
  for (int i = 0; i < 3; ++i) {
    unsigned long long int bit_val = value_1->bits[i] + value_2->bits[i];
    if (bit_val > MAX_BIT) {
      result->bits[i] = bit_val % MAX_BIT;
      overflow = (bit_val - bit_val % MAX_BIT) / MAX_BIT;
    } else {
      result->bits[i] = bit_val;
      overflow = 0;
    }
  }
  if (overflow != 0) {
    ret = TOO_LARGE;
  }
  return ret;
}

int sub_diff_sign_decimals(const s21_decimal* value_1,
                           const s21_decimal* value_2, s21_decimal* result) {
  // TODO: if value_1 < value_2 then value_1 <=> value_2, sign = -sign
  int ret = OK;
  unsigned long long int overflow = 0;
  unsigned long long int bit_val;
  for (int i = 0; i < 3; ++i) {
    if (value_1->bits[i] >= value_2->bits[i] + overflow) {
      bit_val = value_1->bits[i] - value_2->bits[i] - overflow;
      overflow = 0;
    } else {
      bit_val = MAX_BIT - value_2->bits[i] + value_1->bits[i] - overflow;
      overflow = 1;
    }
    result->bits[i] = bit_val;
  }
  if (overflow != 0) {
    ret = TOO_LARGE;  // if used with value_1 < value_2
  }
  return ret;
}

int scale_decimals(s21_decimal* num1, s21_decimal* num2, unsigned int* exp) {
  int ret = OK;

  unsigned int exp1 = get_exponent(num1), exp2 = get_exponent(num2);

  if (exp1 > exp2) {
    *exp = exp1;
    for (unsigned int i = exp2; i < exp1 && ret == OK; ++i) {
      ret = scal_mul(num2, 10);
    }
  } else {
    *exp = exp2;
    for (unsigned int i = exp1; i < exp2 && ret == OK; ++i) {
      ret = scal_mul(num1, 10);
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