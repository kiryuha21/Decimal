#ifndef C5_S21_DECIMAL_0_S21_DECIMAL_H
#define C5_S21_DECIMAL_0_S21_DECIMAL_H

#define BITS_IN_INT 32
#define OVERFLOW_BIT (unsigned long long)(0x100000000)
#define SIGN_BIT 31
#define NEGATIVE 1
#define NEGATIVE_DECIMAL 0x80000000
#define POSITIVE 0
#define EXPONENT_MASK 0x00FF0000
#define NULL_BITS_MASK 0x80FF0000
#define DEFAULT_DECIMAL \
  {                     \
    { 0 }               \
  }

typedef struct s21_decimal {
  unsigned int bits[4];
} s21_decimal;

typedef struct s21_2n_decimal {
  unsigned int bits[7];
} s21_2n_decimal;

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
int get_bit(unsigned int val, int index);
int get_decimal_bit(const s21_decimal *val, int index);
void set_bit(unsigned int *val, int index, int bit);
void set_decimal_bit(s21_decimal *val, int index, int bit);
int get_sign(const s21_decimal *val);
void set_sign(s21_decimal *val, int sign);
void change_sign(s21_decimal *val);
unsigned int get_exponent(const s21_decimal *val);
void set_exponent(s21_decimal *val, unsigned int exp);
int is_zero(const s21_decimal *val);
int add_int_to_dec(s21_decimal val, int num, s21_decimal *res);
int sub_int_fr_dec(s21_decimal val, int num, s21_decimal *res);
int mul_dec_on_int(s21_decimal val, int num, s21_decimal *res);
int mul_without_signs(s21_decimal a, s21_decimal b, s21_decimal *rh,
                      s21_decimal *rl);
int div_dec_on_int(s21_decimal val, int num, s21_decimal *res);
int div_without_signs(s21_2n_decimal a, s21_2n_decimal b, s21_2n_decimal *rh,
                      s21_2n_decimal *rl);
int add_same_signs(s21_decimal value_1, s21_decimal value_2,
                   s21_decimal *result);
int sub_diff_signs(s21_decimal value_1, s21_decimal value_2,
                   s21_decimal *result);
int sub_diff_signs_2n(s21_2n_decimal value_1, s21_2n_decimal value_2,
                      s21_2n_decimal *result);
s21_2n_decimal convert(s21_decimal val);
s21_decimal rconvert(s21_2n_decimal val);
s21_decimal rsconvert(s21_2n_decimal val);
int scale_decimals(s21_decimal *num1, s21_decimal *num2, unsigned int *scale,
                   s21_decimal *overflow);
int scale_2n_decimal(s21_2n_decimal *val1, s21_2n_decimal *val2,
                     unsigned int *exp);
void null_decimal(s21_decimal *val);
void null_decimal_val(s21_decimal *val);
void swap_decimals(s21_decimal *val1, s21_decimal *val2);
void swap_decimals_2n(s21_2n_decimal *val1, s21_2n_decimal *val2);
void reduce_exponent(s21_decimal *val);
int get_elder_bit_index(const s21_decimal *val);
int left_shift(s21_decimal *val);
int left_shift_2n(s21_decimal *dh, s21_decimal *dl);
int left_shift_4n(s21_2n_decimal *dh, s21_2n_decimal *dl);
int right_shift(s21_decimal *val);
void right_shift_2n(s21_decimal *dh, s21_decimal *dl);
void handle_decimal_inc(s21_decimal *val);
int make_first_bigger_no_signs(s21_decimal *first, s21_decimal *second);
int is_bigger(s21_decimal first, s21_decimal second);
int is_equal(s21_decimal first, s21_decimal second);
int decimal_size_10(s21_decimal val);
int try_add_overflow(s21_decimal *val, s21_decimal overflow);
int should_round_up(unsigned long long extended_bit, int thrown_digits);
int should_bround_up(unsigned long long extended_bit, int thrown_digits,
                     unsigned int low_integer);
int bank_round(s21_decimal *val, s21_decimal overflow);

#endif  // C5_S21_DECIMAL_0_S21_DECIMAL_H
