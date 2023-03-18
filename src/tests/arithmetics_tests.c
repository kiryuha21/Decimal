#include <stdio.h>

#include "s21_decimal_testing.h"

// -----------add incorrect inp-----------
START_TEST(add_null_inp) {
  s21_decimal a = DEFAULT_DECIMAL, b = DEFAULT_DECIMAL;

  ck_assert_int_eq(s21_add(a, b, NULL), ERROR);
}
END_TEST

START_TEST(add_too_lardge_inp) {
  s21_decimal a = MAX_DECIMAL, b = MAX_DECIMAL, c = DEFAULT_DECIMAL;

  ck_assert_int_eq(s21_add(a, b, &c), ERROR);
}
END_TEST

START_TEST(add_too_small_inp) {
  s21_decimal a = MIN_DECIMAL, b = MIN_DECIMAL, c = DEFAULT_DECIMAL;

  ck_assert_int_eq(s21_add(a, b, &c), ERROR);
}
END_TEST

// -----------add correct inp-------------
START_TEST(add_positive_numb) {
  s21_decimal a = {5, 0, 0, 0}, b = {5, 0, 0, 0}, c = DEFAULT_DECIMAL;

  ck_assert_int_eq(s21_add(a, b, &c), OK);
  ck_assert_uint_eq(c.bits[0], 10);
}
END_TEST

START_TEST(add_positive_greater_negative_numb) {
  s21_decimal a = {7, 0, 0, 0}, b = {5, 0, 0, NEGATIVE_DECIMAL},
              c = DEFAULT_DECIMAL;

  ck_assert_int_eq(s21_add(a, b, &c), OK);
  ck_assert_uint_eq(c.bits[0], 2);
  ck_assert_uint_eq(c.bits[3], 0);
}
END_TEST

START_TEST(add_positive_less_negative_numb) {
  s21_decimal a = {5, 0, 0, 0}, b = {7, 0, 0, NEGATIVE_DECIMAL},
              c = DEFAULT_DECIMAL;

  ck_assert_int_eq(s21_add(a, b, &c), OK);
  ck_assert_uint_eq(c.bits[0], 2);
  ck_assert(c.bits[3] & (NEGATIVE_DECIMAL));
}
END_TEST

START_TEST(add_negative_numb) {
  s21_decimal a = {7, 0, 0, NEGATIVE_DECIMAL}, b = {5, 0, 0, NEGATIVE_DECIMAL},
              c = DEFAULT_DECIMAL;

  ck_assert_int_eq(s21_add(a, b, &c), OK);
  ck_assert_uint_eq(c.bits[0], 12);
}
END_TEST

START_TEST(add_opposite_numb) {
  s21_decimal a = {7, 0, 0, NEGATIVE_DECIMAL}, b = {7, 0, 0, 0},
              c = DEFAULT_DECIMAL;

  ck_assert_int_eq(s21_add(a, b, &c), OK);
  ck_assert_uint_eq(c.bits[0], 0);
  ck_assert_uint_eq(c.bits[3], 0);
}
END_TEST

START_TEST(add_shift_0_to_1_bits) {
  s21_decimal a = {NEGATIVE_DECIMAL, 0, 0, 0}, b = {NEGATIVE_DECIMAL, 0, 0, 0},
              c = DEFAULT_DECIMAL;

  ck_assert_int_eq(s21_add(a, b, &c), OK);
  ck_assert_uint_eq(c.bits[1], 1);
  ck_assert_uint_eq(c.bits[0], 0);
}
END_TEST

START_TEST(add_shift_1_to_0_bits) {
  s21_decimal a = {0, 1, 0, 0}, b = {NEGATIVE_DECIMAL, 0, 0, NEGATIVE_DECIMAL},
              c = DEFAULT_DECIMAL;

  ck_assert_int_eq(s21_add(a, b, &c), OK);
  ck_assert(c.bits[0] & (NEGATIVE_DECIMAL));
  ck_assert_uint_eq(c.bits[1], 0);
  ck_assert_uint_eq(c.bits[3], 0);
}
END_TEST

START_TEST(add_shift_1_to_2_bits) {
  s21_decimal a = {0, NEGATIVE_DECIMAL, 0, 0}, b = {0, NEGATIVE_DECIMAL, 0, 0},
              c = DEFAULT_DECIMAL;

  ck_assert_int_eq(s21_add(a, b, &c), OK);
  ck_assert_uint_eq(c.bits[2], 1);
  ck_assert_uint_eq(c.bits[1], 0);
}
END_TEST

START_TEST(add_shift_2_to_1_bits) {
  s21_decimal a = {0, 0, 1, 0}, b = {0, NEGATIVE_DECIMAL, 0, NEGATIVE_DECIMAL},
              c = DEFAULT_DECIMAL;

  ck_assert_int_eq(s21_add(a, b, &c), OK);
  ck_assert(c.bits[1] & (NEGATIVE_DECIMAL));
  ck_assert_uint_eq(c.bits[2], 0);
  ck_assert_uint_eq(c.bits[3], 0);
}
END_TEST

START_TEST(add_positive_fractional_numb) {
  s21_decimal a = {5, 0, 0, 0}, b = {5, 0, 0, 0}, c = DEFAULT_DECIMAL;

  ck_assert_int_eq(s21_add(a, b, &c), OK);
  ck_assert_uint_eq(c.bits[0], 10);
}
END_TEST

// -----------sub correct inp-----------

START_TEST(sub_first_greater_second) {
  s21_decimal a = {7, 0, 0, 0}, b = {5, 0, 0, 0}, c = DEFAULT_DECIMAL;

  ck_assert_int_eq(s21_sub(a, b, &c), OK);
  ck_assert_uint_eq(c.bits[0], 2);
  ck_assert_uint_eq(c.bits[3], 0);
}
END_TEST

START_TEST(sub_first_less_second) {
  s21_decimal a = {5, 0, 0, 0}, b = {7, 0, 0, 0}, c = DEFAULT_DECIMAL;

  ck_assert_int_eq(s21_sub(a, b, &c), OK);
  ck_assert_uint_eq(c.bits[0], 2);
  ck_assert(c.bits[3] & (NEGATIVE_DECIMAL));
}
END_TEST

START_TEST(sub_first_negative_second_positive) {
  s21_decimal a = {7, 0, 0, NEGATIVE_DECIMAL}, b = {5, 0, 0, 0},
              c = DEFAULT_DECIMAL;

  ck_assert_int_eq(s21_sub(a, b, &c), OK);
  ck_assert_uint_eq(c.bits[0], 12);
  // ck_assert_uint_eq(c.bits[3] && , NEGATIVE_DECIMAL) don't work
  ck_assert(c.bits[3] & (NEGATIVE_DECIMAL));
}
END_TEST

START_TEST(sub_euqal_negative_number) {
  s21_decimal a = {7, 0, 0, NEGATIVE_DECIMAL}, b = {7, 0, 0, NEGATIVE_DECIMAL},
              c = DEFAULT_DECIMAL;

  ck_assert_int_eq(s21_sub(a, b, &c), OK);
  ck_assert_uint_eq(c.bits[0], 0);
}
END_TEST

START_TEST(sub_euqal_positive_number) {
  s21_decimal a = {7, 0, 0, 0}, b = {7, 0, 0, 0}, c = DEFAULT_DECIMAL;

  ck_assert_int_eq(s21_sub(a, b, &c), OK);
  ck_assert_uint_eq(c.bits[0], 0);
}
END_TEST

Suite *get_arithmetics_suite() {
  Suite *s;
  TCase *t_case;

  s = suite_create("Arithmetics suite");

  t_case = tcase_create("Add incorrect inp");
  tcase_add_test(t_case, add_null_inp);
  tcase_add_test(t_case, add_too_lardge_inp);
  tcase_add_test(t_case, add_too_small_inp);
  suite_add_tcase(s, t_case);

  t_case = tcase_create("Add correct inp");
  tcase_add_test(t_case, add_positive_numb);
  tcase_add_test(t_case, add_positive_greater_negative_numb);
  tcase_add_test(t_case, add_positive_less_negative_numb);
  tcase_add_test(t_case, add_negative_numb);
  tcase_add_test(t_case, add_opposite_numb);
  tcase_add_test(t_case, add_shift_0_to_1_bits);
  tcase_add_test(t_case, add_shift_1_to_0_bits);
  tcase_add_test(t_case, add_shift_1_to_2_bits);
  tcase_add_test(t_case, add_shift_2_to_1_bits);
  suite_add_tcase(s, t_case);

  t_case = tcase_create("Sub correct inp");
  tcase_add_test(t_case, sub_first_greater_second);
  tcase_add_test(t_case, sub_first_less_second);
  tcase_add_test(t_case, sub_first_negative_second_positive);
  tcase_add_test(t_case, sub_euqal_negative_number);
  tcase_add_test(t_case, sub_euqal_positive_number);
  suite_add_tcase(s, t_case);

  return s;
}
