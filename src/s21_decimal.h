#ifndef C5_S21_DECIMAL_0_S21_DECIMAL_H
#define C5_S21_DECIMAL_0_S21_DECIMAL_H

#define MAX_BIT 0xFFFFFFFF
#define MIN_BIT 0
#define SIGN_BIT 31
#define NEGATIVE 1
#define POSITIVE 0
#define EXPONENT_MASK 0x00FF0000
#define DEFAULT_DECIMAL \
  { 0, 0, 0, 0 }

typedef struct s21_decimal {
  int bits[4];
} s21_decimal;

// common for all functions except compare ones
#define OK 0
#define ERROR 1

// return codes for 5 functions below
#define TOO_LARGE 1
#define TOO_SMALL 2
#define ZERO_DIVISION 3

// arithmetics.c
int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_mod(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

// conversions.c
int s21_from_int_to_decimal(int src, s21_decimal *dst);
int s21_from_float_to_decimal(float src, s21_decimal *dst);
int s21_from_decimal_to_int(s21_decimal src, int *dst);
int s21_from_decimal_to_float(s21_decimal src, float *dst);

// extras.c
int s21_floor(s21_decimal value, s21_decimal *result);
int s21_round(s21_decimal value, s21_decimal *result);
int s21_truncate(s21_decimal value, s21_decimal *result);
int s21_negate(s21_decimal value, s21_decimal *result);

// return codes for 6 functions below
#define FALSE 0
#define TRUE 1

// comparisons.c
int s21_is_less(s21_decimal, s21_decimal);
int s21_is_less_or_equal(s21_decimal, s21_decimal);
int s21_is_greater(s21_decimal, s21_decimal);
int s21_is_greater_or_equal(s21_decimal, s21_decimal);
int s21_is_equal(s21_decimal, s21_decimal);
int s21_is_not_equal(s21_decimal, s21_decimal);

// utils
int get_bit(int val, int index);
void set_bit(int *val, int index, int bit);
int get_sign(const s21_decimal *val);
void set_sign(s21_decimal *val, int sign);
int get_exponent(const s21_decimal *val);

#endif  // C5_S21_DECIMAL_0_S21_DECIMAL_H
