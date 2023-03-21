#include <stdio.h>

#include "s21_decimal_testing.h"

START_TEST(decimal_add_1) {
  s21_decimal x = {{4294967295, 4294967295, 0, 0}};
  s21_decimal y = {{1, 0, 0, 0}};
  s21_decimal z = {{0, 0, 0, 0}};
  s21_add(x, y, &z);
  char ourRes[1000], expect[1000] = "0 0 1 0";
  snprintf(ourRes, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(ourRes, expect);
}
END_TEST

START_TEST(decimal_add_2) {
  s21_decimal x = {{20, 1, 0, 2147483648}};
  s21_decimal y = {{21, 0, 0, 0}};
  s21_decimal z = {{0, 0, 0, 0}};
  s21_add(x, y, &z);
  char ourRes[1000], expect[1000] = "4294967295 0 0 2147483648";
  snprintf(ourRes, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(ourRes, expect);
}
END_TEST

START_TEST(decimal_add_3) {
  s21_decimal x = {{20, 1, 0, 2147483648}};
  s21_decimal y = {{21, 0, 0, 2147483648}};
  s21_decimal z = {{0, 0, 0, 0}};
  s21_add(x, y, &z);
  char ourRes[1000], expect[1000] = "41 1 0 2147483648";
  snprintf(ourRes, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(ourRes, expect);
}
END_TEST

START_TEST(decimal_add_4) {
  s21_decimal x = {{20, 1, 0, 0}};
  s21_decimal y = {{21, 0, 0, 2147483648}};
  s21_decimal z = {{0, 0, 0, 0}};
  s21_add(x, y, &z);
  char ourRes[1000], expect[1000] = "4294967295 0 0 0";
  snprintf(ourRes, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(ourRes, expect);
}
END_TEST

START_TEST(decimal_add_5) {
  s21_decimal x = {{20, 0, 0, 2147483648}};
  s21_decimal y = {{21, 0, 0, 0}};
  s21_decimal z = {{0, 0, 0, 0}};
  s21_add(x, y, &z);
  char ourRes[1000], expect[1000] = "1 0 0 0";
  snprintf(ourRes, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(ourRes, expect);
}
END_TEST

START_TEST(decimal_add_6) {
  s21_decimal x = {{25, 1, 0, 2147483648}};
  s21_decimal y = {{21, 0, 0, 0}};
  s21_decimal z = {{0, 0, 0, 0}};
  s21_add(x, y, &z);
  char ourRes[1000], expect[1000] = "4 1 0 2147483648";
  snprintf(ourRes, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(ourRes, expect);
}
END_TEST

START_TEST(decimal_add_7) {
  s21_decimal x = {{100, 0, 0, 2147483648}};
  s21_decimal y = {{100, 0, 0, 0}};
  s21_decimal z = {{0, 0, 0, 0}};
  s21_add(x, y, &z);
  char ourRes[1000], expect[1000] = "0 0 0 0";
  snprintf(ourRes, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(ourRes, expect);
}
END_TEST

START_TEST(decimal_add_8) {
  s21_decimal x = {{99, 0, 0, 0}};
  s21_decimal y = {{100, 0, 0, 2147483648}};
  s21_decimal z = {{0, 0, 0, 0}};
  s21_add(x, y, &z);
  char ourRes[1000], expect[1000] = "1 0 0 2147483648";
  snprintf(ourRes, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(ourRes, expect);
}
END_TEST

START_TEST(decimal_add_9) {
  s21_decimal x = {{0, 0, 300000000, 1835008}};
  s21_decimal y = {{0, 0, 300000000, 1835008}};
  s21_decimal z = {{0, 0, 0, 0}};
  s21_add(x, y, &z);
  char ourRes[1000], expect[1000] = "0 0 6 1310720";
  snprintf(ourRes, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(ourRes, expect);
}
END_TEST

START_TEST(decimal_add_10) {
  s21_decimal x = {{0, 0, 3000000000, 0}};
  s21_decimal y = {{0, 0, 3000000000, 0}};
  s21_decimal z = {{0, 0, 0, 0}};
  int err = s21_add(x, y, &z);
  ck_assert_int_eq(err, 1);
}
END_TEST

START_TEST(decimal_add_11) {
  s21_decimal x = {{1, 0, 0, 1835008}};
  s21_decimal y = {{1, 0, 0, 2149318656}};
  s21_decimal z = {{0, 0, 0, 0}};
  s21_add(x, y, &z);
  char ourRes[1000], expect[1000] = "0 0 0 0";
  snprintf(ourRes, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(ourRes, expect);
}
END_TEST

START_TEST(special_test_add_1) {
  s21_decimal x = {{1, 1, 1, 65536}};
  s21_decimal y = {{1, 1, 1, 65536}};
  s21_decimal z = {{0, 0, 0, 0}};
  s21_add(x, y, &z);
  char ourRes[1000], expect[1000] = "2 2 2 65536";
  snprintf(ourRes, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(ourRes, expect);
}
END_TEST

START_TEST(special_test_add_2) {
  s21_decimal x = {{1, 1, 1, 65536}};
  s21_decimal y = {{1, 1, 1, 655360}};
  s21_decimal z = {{0, 0, 0, 0}};
  s21_add(x, y, &z);
  char ourRes[1000], expect[1000] = "1000000001 1000000001 1000000001 655360";
  snprintf(ourRes, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(ourRes, expect);
}
END_TEST

START_TEST(special_test_add_3) {
  s21_decimal x = {{24, 1, 1, -2147418112}};
  s21_decimal y = {{1, 15, 1, 655360}};
  s21_decimal z = {{0, 0, 0, 0}};
  s21_add(x, y, &z);
  char ourRes[1000], expect[1000] = "2525163519 999999990 999999999 2148139008";
  snprintf(ourRes, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(ourRes, expect);
}
END_TEST

START_TEST(special_test_add_4) {
  s21_decimal x = {{1, 1, 1, 655360}};
  s21_decimal y = {{1, 1, 1, -2147418112}};
  s21_decimal z = {{0, 0, 0, 0}};
  s21_add(x, y, &z);
  char ourRes[1000], expect[1000] = "999999999 999999999 999999999 2148139008";
  snprintf(ourRes, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(ourRes, expect);
}
END_TEST

Suite *suite_s21_add() {
  Suite *suite = suite_create("s21_add");
  TCase *tcase = tcase_create("s21_add");
  suite_add_tcase(suite, tcase);

  tcase_add_test(tcase, decimal_add_1);
  tcase_add_test(tcase, decimal_add_2);
  tcase_add_test(tcase, decimal_add_3);
  tcase_add_test(tcase, decimal_add_4);
  tcase_add_test(tcase, decimal_add_5);
  tcase_add_test(tcase, decimal_add_6);
  tcase_add_test(tcase, decimal_add_7);
  tcase_add_test(tcase, decimal_add_8);
  tcase_add_test(tcase, decimal_add_9);
  tcase_add_test(tcase, decimal_add_10);
  tcase_add_test(tcase, decimal_add_11);
  tcase_add_test(tcase, special_test_add_1);
  tcase_add_test(tcase, special_test_add_2);
  tcase_add_test(tcase, special_test_add_3);
  tcase_add_test(tcase, special_test_add_4);

  return suite;
}

START_TEST(decimal_sub_1) {
  s21_decimal x = {{1, 0, 0, 0}};
  s21_decimal y = {{1, 0, 0, 0}};
  s21_decimal z = {{0, 0, 0, 0}};
  s21_sub(x, y, &z);
  char ourRes[1000], expect[1000] = "0 0 0 0";
  snprintf(ourRes, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(ourRes, expect);
}
END_TEST

START_TEST(decimal_sub_2) {
  s21_decimal x = {{2, 0, 0, 0}};
  s21_decimal y = {{1, 0, 0, 0}};
  s21_decimal z = {{0, 0, 0, 0}};
  s21_sub(x, y, &z);
  char ourRes[1000], expect[1000] = "1 0 0 0";
  snprintf(ourRes, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(ourRes, expect);
}
END_TEST

START_TEST(decimal_sub_3) {
  s21_decimal x = {{1, 0, 0, 0}};
  s21_decimal y = {{2, 0, 0, 0}};
  s21_decimal z = {{0, 0, 0, 0}};
  s21_sub(x, y, &z);
  char ourRes[1000], expect[1000] = "1 0 0 2147483648";
  snprintf(ourRes, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(ourRes, expect);
}
END_TEST

START_TEST(decimal_sub_4) {
  s21_decimal x = {{2, 0, 0, 2147483648}};
  s21_decimal y = {{2, 0, 0, 2147483648}};
  s21_decimal z = {{0, 0, 0, 0}};
  s21_sub(x, y, &z);
  char ourRes[1000], expect[1000] = "0 0 0 0";
  snprintf(ourRes, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(ourRes, expect);
}
END_TEST

START_TEST(decimal_sub_5) {
  s21_decimal x = {{1, 0, 0, 2147483648}};
  s21_decimal y = {{2, 0, 0, 2147483648}};
  s21_decimal z = {{0, 0, 0, 0}};
  s21_sub(x, y, &z);
  char ourRes[1000], expect[1000] = "1 0 0 0";
  snprintf(ourRes, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(ourRes, expect);
}
END_TEST

START_TEST(decimal_sub_6) {
  s21_decimal x = {{2, 0, 0, 2147483648}};
  s21_decimal y = {{1, 0, 0, 2147483648}};
  s21_decimal z = {{0, 0, 0, 0}};
  s21_sub(x, y, &z);
  char ourRes[1000], expect[1000] = "1 0 0 2147483648";
  snprintf(ourRes, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(ourRes, expect);
}
END_TEST

START_TEST(decimal_sub_7) {
  s21_decimal x = {{2, 0, 0, 0}};
  s21_decimal y = {{1, 0, 0, 2147483648}};
  s21_decimal z = {{0, 0, 0, 0}};
  s21_sub(x, y, &z);
  char ourRes[1000], expect[1000] = "3 0 0 0";
  snprintf(ourRes, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(ourRes, expect);
}
END_TEST

START_TEST(decimal_sub_8) {
  s21_decimal x = {{2, 0, 0, 2147483648}};
  s21_decimal y = {{1, 0, 0, 0}};
  s21_decimal z = {{0, 0, 0, 0}};
  s21_sub(x, y, &z);
  char ourRes[1000], expect[1000] = "3 0 0 2147483648";
  snprintf(ourRes, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(ourRes, expect);
}
END_TEST

START_TEST(special_test_sub_1) {
  s21_decimal x = {{1, 1, 1, 65536}};
  s21_decimal y = {{1, 1, 1, -2147418112}};
  s21_decimal z = {{0, 0, 0, 0}};
  s21_sub(x, y, &z);
  char ourRes[1000], expect[1000] = "2 2 2 65536";
  snprintf(ourRes, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(ourRes, expect);
}
END_TEST

START_TEST(special_test_sub_2) {
  s21_decimal x = {{1, 1, 1, -2147418112}};
  s21_decimal y = {{1, 1, 1, -2147418112}};
  s21_decimal z = {{0, 0, 0, 0}};
  s21_sub(x, y, &z);
  char ourRes[1000], expect[1000] = "0 0 0 0";
  snprintf(ourRes, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(ourRes, expect);
}
END_TEST

START_TEST(special_test_sub_3) {
  s21_decimal x = {{24, 1, 1, -2147418112}};
  s21_decimal y = {{1, 1, 1, 65536}};
  s21_decimal z = {{0, 0, 0, 0}};
  s21_sub(x, y, &z);
  char ourRes[1000], expect[1000] = "25 2 2 2147549184";
  snprintf(ourRes, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(ourRes, expect);
}
END_TEST

Suite *suite_s21_sub() {
  Suite *suite = suite_create("s21_sub");
  TCase *tcase = tcase_create("s21_sub");
  suite_add_tcase(suite, tcase);

  tcase_add_test(tcase, decimal_sub_1);
  tcase_add_test(tcase, decimal_sub_2);
  tcase_add_test(tcase, decimal_sub_3);
  tcase_add_test(tcase, decimal_sub_4);
  tcase_add_test(tcase, decimal_sub_5);
  tcase_add_test(tcase, decimal_sub_6);
  tcase_add_test(tcase, decimal_sub_7);
  tcase_add_test(tcase, decimal_sub_8);
  tcase_add_test(tcase, special_test_sub_1);
  tcase_add_test(tcase, special_test_sub_2);
  tcase_add_test(tcase, special_test_sub_3);

  return suite;
}

START_TEST(decimal_is_equal_1) {
  s21_decimal x = {{0, 0, 1, 0}};
  s21_decimal y = {{0, 0, 1, 0}};
  int ourRes = s21_is_equal(x, y);
  int expect = 1;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(decimal_is_equal_2) {
  s21_decimal x = {{0, 0, 1, NEGATIVE_DECIMAL}};
  s21_decimal y = {{0, 0, 1, NEGATIVE_DECIMAL}};

  int ourRes = s21_is_equal(x, y);
  int expect = 1;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(decimal_is_equal_3) {
  s21_decimal x = {{0, 0, 1, 0}};
  s21_decimal y = {{0, 0, 1, NEGATIVE_DECIMAL}};

  int ourRes = s21_is_equal(x, y);
  int expect = 0;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(decimal_is_equal_4) {
  s21_decimal x = {{0, 0, 1, NEGATIVE_DECIMAL}};
  s21_decimal y = {{0, 0, 1, 0}};

  int ourRes = s21_is_equal(x, y);
  int expect = 0;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(decimal_is_equal_5) {
  s21_decimal x = {{0, 52, 1, 0}};
  s21_decimal y = {{0, 0, 1, 0}};
  int ourRes = s21_is_equal(x, y);
  int expect = 0;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(decimal_is_equal_6) {
  s21_decimal x = {{0, 0, 1, 0}};
  s21_decimal y = {{1747, 0, 1, 0}};
  int ourRes = s21_is_equal(x, y);
  int expect = 0;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(decimal_is_equal_7) {
  s21_decimal x = {{0, 0, 1, NEGATIVE_DECIMAL}};
  s21_decimal y = {{1747, 0, 1, 0}};

  int ourRes = s21_is_equal(x, y);
  int expect = 0;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(decimal_is_equal_8) {
  s21_decimal x = {{0, 0, 0, NEGATIVE_DECIMAL}};
  s21_decimal y = {{1, 0, 0, 0}};

  int ourRes = s21_is_equal(x, y);
  int expect = 0;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(decimal_is_equal_9) {
  s21_decimal x = {{1, 0, 0, 0}};
  s21_decimal y = {{0, 0, 0, NEGATIVE_DECIMAL}};

  int ourRes = s21_is_equal(x, y);
  int expect = 0;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(decimal_is_equal_10) {
  s21_decimal x = {{0, 0, 0, 0}};
  s21_decimal y = {{0, 0, 0, NEGATIVE_DECIMAL}};

  int ourRes = s21_is_equal(x, y);
  int expect = 1;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(special_test_is_equal_1) {
  s21_decimal x = {{1, 2, 3, 655360}};
  s21_decimal y = {{3, 2, 1, -2146828288}};
  int ourRes = s21_is_equal(x, y);
  int expect = 0;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(special_test_is_equal_2) {
  s21_decimal x = {{1, 2, 3, -2146828288}};
  s21_decimal y = {{3, 2, 1, -2146828288}};
  int ourRes = s21_is_equal(x, y);
  int expect = 0;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(special_test_is_equal_3) {
  s21_decimal x = {{1, 2, 3, -2146566144}};
  s21_decimal y = {{3, 2, 1, -2146959360}};
  int ourRes = s21_is_equal(x, y);
  int expect = 0;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(special_test_is_equal_4) {
  s21_decimal x = {{10, 2, 3, -2146566144}};
  s21_decimal y = {{3, 2, 1, 524288}};
  int ourRes = s21_is_equal(x, y);
  int expect = 0;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(special_test_is_equal_5) {
  s21_decimal x = {{1, 2, 3, 917504}};
  s21_decimal y = {{1, 2, 3, 917504}};
  int ourRes = s21_is_equal(x, y);
  int expect = 1;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

Suite *suite_s21_is_equal() {
  Suite *suite = suite_create("s21_is_equal");
  TCase *tcase = tcase_create("case_s21_is_equal");

  tcase_add_test(tcase, decimal_is_equal_1);
  tcase_add_test(tcase, decimal_is_equal_2);
  tcase_add_test(tcase, decimal_is_equal_3);
  tcase_add_test(tcase, decimal_is_equal_4);
  tcase_add_test(tcase, decimal_is_equal_5);
  tcase_add_test(tcase, decimal_is_equal_6);
  tcase_add_test(tcase, decimal_is_equal_7);
  tcase_add_test(tcase, decimal_is_equal_8);
  tcase_add_test(tcase, decimal_is_equal_9);
  tcase_add_test(tcase, decimal_is_equal_10);

  tcase_add_test(tcase, special_test_is_equal_1);
  tcase_add_test(tcase, special_test_is_equal_2);
  tcase_add_test(tcase, special_test_is_equal_3);
  tcase_add_test(tcase, special_test_is_equal_4);
  tcase_add_test(tcase, special_test_is_equal_5);

  suite_add_tcase(suite, tcase);
  return suite;
}

START_TEST(decimal_is_greater_or_equal_1) {
  s21_decimal x = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x001C0000}};
  s21_decimal y = {{10, 0, 0, 0}};
  int ourRes = s21_is_greater_or_equal(x, y);
  int expect = TRUE;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(decimal_is_greater_or_equal_2) {
  s21_decimal x = {{0, 0, 1, 0}};
  s21_decimal y = {{0, 0, 2, 0}};
  int ourRes = s21_is_greater_or_equal(y, x);
  int expect = 1;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(decimal_is_greater_or_equal_3) {
  s21_decimal x = {{0, 0, 1, 0}};
  s21_decimal y = {{0, 0, 1, 0}};
  int ourRes = s21_is_greater_or_equal(y, x);
  int expect = 1;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(decimal_is_greater_or_equal_4) {
  s21_decimal x = {{0, 0, 1, NEGATIVE_DECIMAL}};
  s21_decimal y = {{0, 0, 2, NEGATIVE_DECIMAL}};

  int ourRes = s21_is_greater_or_equal(x, y);
  int expect = 1;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(decimal_is_greater_or_equal_5) {
  s21_decimal x = {{0, 0, 1, NEGATIVE_DECIMAL}};
  s21_decimal y = {{0, 0, 2, NEGATIVE_DECIMAL}};

  int ourRes = s21_is_greater_or_equal(y, x);
  int expect = 0;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(decimal_is_greater_or_equal_6) {
  s21_decimal x = {{0, 0, 1, NEGATIVE_DECIMAL}};
  s21_decimal y = {{0, 0, 1, NEGATIVE_DECIMAL}};

  int ourRes = s21_is_greater_or_equal(y, x);
  int expect = 1;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(decimal_is_greater_or_equal_7) {
  s21_decimal x = {{0, 0, 1, NEGATIVE_DECIMAL}};
  s21_decimal y = {{0, 0, 1, 0}};

  int ourRes = s21_is_greater_or_equal(x, y);
  int expect = 0;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(decimal_is_greater_or_equal_8) {
  s21_decimal x = {{0, 0, 1, 0}};
  s21_decimal y = {{0, 0, 1, NEGATIVE_DECIMAL}};

  int ourRes = s21_is_greater_or_equal(x, y);
  int expect = 1;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(special_test_is_greater_or_equal_1) {
  s21_decimal x = {{1, 2, 3, 655360}};
  s21_decimal y = {{3, 2, 1, -2146828288}};

  int ourRes = s21_is_greater_or_equal(x, y);
  int expect = 1;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(special_test_is_greater_or_equal_2) {
  s21_decimal x = {{1, 2, 3, -2146828288}};
  s21_decimal y = {{3, 2, 1, -2146828288}};

  int ourRes = s21_is_greater_or_equal(x, y);
  int expect = 0;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(special_test_is_greater_or_equal_3) {
  s21_decimal x = {{1, 2, 3, -2146566144}};
  s21_decimal y = {{3, 2, 1, -2146959360}};

  int ourRes = s21_is_greater_or_equal(x, y);
  int expect = 1;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(special_test_is_greater_or_equal_4) {
  s21_decimal x = {{10, 2, 3, -2146566144}};
  s21_decimal y = {{3, 2, 1, 524288}};

  int ourRes = s21_is_greater_or_equal(x, y);
  int expect = 0;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(special_test_is_greater_or_equal_5) {
  s21_decimal x = {{1, 2, 3, 917504}};
  s21_decimal y = {{1, 2, 3, 917504}};

  int ourRes = s21_is_greater_or_equal(x, y);
  int expect = 1;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

Suite *suite_s21_is_greater_or_equal() {
  Suite *suite = suite_create("s21_greater_or_equal");
  TCase *tcase = tcase_create("case_s21_greater_or_equal");

  tcase_add_test(tcase, decimal_is_greater_or_equal_1);
  tcase_add_test(tcase, decimal_is_greater_or_equal_2);
  tcase_add_test(tcase, decimal_is_greater_or_equal_3);
  tcase_add_test(tcase, decimal_is_greater_or_equal_4);
  tcase_add_test(tcase, decimal_is_greater_or_equal_5);
  tcase_add_test(tcase, decimal_is_greater_or_equal_6);
  tcase_add_test(tcase, decimal_is_greater_or_equal_7);
  tcase_add_test(tcase, decimal_is_greater_or_equal_8);
  tcase_add_test(tcase, special_test_is_greater_or_equal_1);
  tcase_add_test(tcase, special_test_is_greater_or_equal_2);
  tcase_add_test(tcase, special_test_is_greater_or_equal_3);
  tcase_add_test(tcase, special_test_is_greater_or_equal_4);
  tcase_add_test(tcase, special_test_is_greater_or_equal_5);

  suite_add_tcase(suite, tcase);
  return suite;
}

START_TEST(decimal_is_greater_1) {
  s21_decimal x = {{0, 0, 1, 0}};
  s21_decimal y = {{0, 0, 2, 0}};
  int ourRes = s21_is_greater(x, y);
  int expect = 0;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(decimal_is_greater_2) {
  s21_decimal x = {{0, 0, 1, 0}};
  s21_decimal y = {{0, 0, 2, 0}};
  int ourRes = s21_is_greater(y, x);
  int expect = 1;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(decimal_is_greater_3) {
  s21_decimal x = {{0, 0, 1, 0}};
  s21_decimal y = {{0, 0, 1, 0}};
  int ourRes = s21_is_greater(y, x);
  int expect = 0;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(decimal_is_greater_4) {
  s21_decimal x = {{0, 0, 1, NEGATIVE_DECIMAL}};
  s21_decimal y = {{0, 0, 2, NEGATIVE_DECIMAL}};

  int ourRes = s21_is_greater(x, y);
  int expect = 1;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(decimal_is_greater_5) {
  s21_decimal x = {{0, 0, 1, NEGATIVE_DECIMAL}};
  s21_decimal y = {{0, 0, 2, NEGATIVE_DECIMAL}};

  int ourRes = s21_is_greater(y, x);
  int expect = 0;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(decimal_is_greater_6) {
  s21_decimal x = {{0, 0, 1, NEGATIVE_DECIMAL}};
  s21_decimal y = {{0, 0, 1, NEGATIVE_DECIMAL}};
  int ourRes = s21_is_greater(y, x);
  int expect = 0;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(decimal_is_greater_7) {
  s21_decimal x = {{0, 0, 1, NEGATIVE_DECIMAL}};
  s21_decimal y = {{0, 0, 1, 0}};

  int ourRes = s21_is_greater(x, y);
  int expect = 0;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(decimal_is_greater_8) {
  s21_decimal x = {{0, 0, 1, 0}};
  s21_decimal y = {{0, 0, 1, NEGATIVE_DECIMAL}};

  int ourRes = s21_is_greater(x, y);
  int expect = 1;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(special_test_is_greater_1) {
  s21_decimal x = {{1, 2, 3, 655360}};
  s21_decimal y = {{3, 2, 1, -2146828288}};
  int ourRes = s21_is_greater(x, y);
  int expect = 1;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(special_test_is_greater_2) {
  s21_decimal x = {{1, 2, 3, -2146828288}};
  s21_decimal y = {{3, 2, 1, -2146828288}};
  int ourRes = s21_is_greater(x, y);
  int expect = 0;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(special_test_is_greater_3) {
  s21_decimal x = {{1, 2, 3, -2146566144}};
  s21_decimal y = {{3, 2, 1, -2146959360}};
  int ourRes = s21_is_greater(x, y);
  int expect = 1;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(special_test_is_greater_4) {
  s21_decimal x = {{10, 2, 3, -2146566144}};
  s21_decimal y = {{3, 2, 1, 524288}};
  int ourRes = s21_is_greater(x, y);
  int expect = 0;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(special_test_is_greater_5) {
  s21_decimal x = {{1, 2, 3, 917504}};
  s21_decimal y = {{1, 2, 3, 917504}};
  int ourRes = s21_is_greater(x, y);
  int expect = 0;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

Suite *suite_s21_is_greater() {
  Suite *suite = suite_create("s21_is_greater");
  TCase *tcase = tcase_create("case_s21_is_greater");

  tcase_add_test(tcase, decimal_is_greater_1);
  tcase_add_test(tcase, decimal_is_greater_2);
  tcase_add_test(tcase, decimal_is_greater_3);
  tcase_add_test(tcase, decimal_is_greater_4);
  tcase_add_test(tcase, decimal_is_greater_5);
  tcase_add_test(tcase, decimal_is_greater_6);
  tcase_add_test(tcase, decimal_is_greater_7);
  tcase_add_test(tcase, decimal_is_greater_8);
  tcase_add_test(tcase, special_test_is_greater_1);
  tcase_add_test(tcase, special_test_is_greater_2);
  tcase_add_test(tcase, special_test_is_greater_3);
  tcase_add_test(tcase, special_test_is_greater_4);
  tcase_add_test(tcase, special_test_is_greater_5);

  suite_add_tcase(suite, tcase);
  return suite;
}

START_TEST(decimal_is_less_or_equal_1) {
  s21_decimal x = {{0, 0, 1, 0}};
  s21_decimal y = {{0, 0, 2, 0}};
  int ourRes = s21_is_less_or_equal(x, y);
  int expect = 1;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(decimal_is_less_or_equal_2) {
  s21_decimal x = {{0, 0, 1, 0}};
  s21_decimal y = {{0, 0, 2, 0}};
  int ourRes = s21_is_less_or_equal(y, x);
  int expect = 0;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(decimal_is_less_or_equal_3) {
  s21_decimal x = {{0, 0, 1, 0}};
  s21_decimal y = {{0, 0, 1, 0}};
  int ourRes = s21_is_less_or_equal(y, x);
  int expect = 1;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(decimal_is_less_or_equal_4) {
  s21_decimal x = {{0, 0, 1, NEGATIVE_DECIMAL}};
  s21_decimal y = {{0, 0, 2, NEGATIVE_DECIMAL}};

  int ourRes = s21_is_less_or_equal(x, y);
  int expect = 0;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(decimal_is_less_or_equal_5) {
  s21_decimal x = {{0, 0, 1, NEGATIVE_DECIMAL}};
  s21_decimal y = {{0, 0, 2, NEGATIVE_DECIMAL}};

  int ourRes = s21_is_less_or_equal(y, x);
  int expect = 1;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(decimal_is_less_or_equal_6) {
  s21_decimal x = {{0, 0, 1, NEGATIVE_DECIMAL}};
  s21_decimal y = {{0, 0, 1, NEGATIVE_DECIMAL}};

  int ourRes = s21_is_less_or_equal(y, x);
  int expect = 1;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(decimal_is_less_or_equal_7) {
  s21_decimal x = {{0, 0, 1, NEGATIVE_DECIMAL}};
  s21_decimal y = {{0, 0, 1, 0}};

  int ourRes = s21_is_less_or_equal(x, y);
  int expect = 1;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(decimal_is_less_or_equal_8) {
  s21_decimal x = {{0, 0, 1, 0}};
  s21_decimal y = {{0, 0, 1, NEGATIVE_DECIMAL}};

  int ourRes = s21_is_less_or_equal(x, y);
  int expect = 0;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(special_test_is_less_or_equal_1) {
  s21_decimal x = {{1, 2, 3, 655360}};
  s21_decimal y = {{3, 2, 1, -2146828288}};
  int ourRes = s21_is_less_or_equal(x, y);
  int expect = 0;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(special_test_is_less_or_equal_2) {
  s21_decimal x = {{1, 2, 3, -2146828288}};
  s21_decimal y = {{3, 2, 1, -2146828288}};
  int ourRes = s21_is_less_or_equal(x, y);
  int expect = 1;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(special_test_is_less_or_equal_3) {
  s21_decimal x = {{1, 2, 3, -2146566144}};
  s21_decimal y = {{3, 2, 1, -2146959360}};
  int ourRes = s21_is_less_or_equal(x, y);
  int expect = 0;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(special_test_is_less_or_equal_4) {
  s21_decimal x = {{10, 2, 3, -2146566144}};
  s21_decimal y = {{3, 2, 1, 524288}};
  int ourRes = s21_is_less_or_equal(x, y);
  int expect = 1;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(special_test_is_less_or_equal_5) {
  s21_decimal x = {{1, 2, 3, 917504}};
  s21_decimal y = {{1, 2, 3, 917504}};
  int ourRes = s21_is_less_or_equal(x, y);
  int expect = 1;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

Suite *suite_s21_is_less_or_equal() {
  Suite *suite = suite_create("s21_is_less_or_equal");
  TCase *tcase = tcase_create("case_s21_is_less_or_equal");

  tcase_add_test(tcase, decimal_is_less_or_equal_1);
  tcase_add_test(tcase, decimal_is_less_or_equal_2);
  tcase_add_test(tcase, decimal_is_less_or_equal_3);
  tcase_add_test(tcase, decimal_is_less_or_equal_4);
  tcase_add_test(tcase, decimal_is_less_or_equal_5);
  tcase_add_test(tcase, decimal_is_less_or_equal_6);
  tcase_add_test(tcase, decimal_is_less_or_equal_7);
  tcase_add_test(tcase, decimal_is_less_or_equal_8);
  tcase_add_test(tcase, special_test_is_less_or_equal_1);
  tcase_add_test(tcase, special_test_is_less_or_equal_2);
  tcase_add_test(tcase, special_test_is_less_or_equal_3);
  tcase_add_test(tcase, special_test_is_less_or_equal_4);
  tcase_add_test(tcase, special_test_is_less_or_equal_5);

  suite_add_tcase(suite, tcase);
  return suite;
}

START_TEST(decimal_is_less_1) {
  s21_decimal x = {{4294967295, 0, 0, 0}};
  s21_decimal y = {{0, 1, 0, 0}};
  int ourRes = s21_is_less(x, y);
  int expect = 1;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(decimal_is_less_2) {
  s21_decimal x = {{0, 0, 1, 0}};
  s21_decimal y = {{0, 0, 2, 0}};
  int ourRes = s21_is_less(y, x);
  int expect = 0;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(decimal_is_less_3) {
  s21_decimal x = {{0, 0, 1, 0}};
  s21_decimal y = {{0, 0, 1, 0}};
  int ourRes = s21_is_less(y, x);
  int expect = 0;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(decimal_is_less_4) {
  s21_decimal x = {{0, 0, 1, NEGATIVE_DECIMAL}};
  s21_decimal y = {{0, 0, 2, NEGATIVE_DECIMAL}};

  int ourRes = s21_is_less(x, y);
  int expect = 0;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(decimal_is_less_5) {
  s21_decimal x = {{0, 0, 1, NEGATIVE_DECIMAL}};
  s21_decimal y = {{0, 0, 2, NEGATIVE_DECIMAL}};

  int ourRes = s21_is_less(y, x);
  int expect = 1;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(decimal_is_less_6) {
  s21_decimal x = {{0, 0, 1, NEGATIVE_DECIMAL}};
  s21_decimal y = {{0, 0, 1, NEGATIVE_DECIMAL}};

  int ourRes = s21_is_less(y, x);
  int expect = 0;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(decimal_is_less_7) {
  s21_decimal x = {{0, 0, 1, NEGATIVE_DECIMAL}};
  s21_decimal y = {{0, 0, 1, 0}};

  int ourRes = s21_is_less(x, y);
  int expect = 1;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(decimal_is_less_8) {
  s21_decimal x = {{0, 0, 1, 0}};
  s21_decimal y = {{0, 0, 1, NEGATIVE_DECIMAL}};

  int ourRes = s21_is_less(x, y);
  int expect = 0;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(special_test_is_less_1) {
  s21_decimal x = {{1, 2, 3, 655360}};
  s21_decimal y = {{3, 2, 1, -2146828288}};
  int ourRes = s21_is_less(x, y);
  int expect = 0;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(special_test_is_less_2) {
  s21_decimal x = {{1, 2, 3, -2146828288}};
  s21_decimal y = {{3, 2, 1, -2146828288}};
  int ourRes = s21_is_less(x, y);
  int expect = 1;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(special_test_is_less_3) {
  s21_decimal x = {{1, 2, 3, -2146566144}};
  s21_decimal y = {{3, 2, 1, -2146959360}};
  int ourRes = s21_is_less(x, y);
  int expect = 0;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(special_test_is_less_4) {
  s21_decimal x = {{10, 2, 3, -2146566144}};
  s21_decimal y = {{3, 2, 1, 524288}};
  int ourRes = s21_is_less(x, y);
  int expect = 1;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(special_test_is_less_5) {
  s21_decimal x = {{1, 2, 3, 917504}};
  s21_decimal y = {{1, 2, 3, 917504}};
  int ourRes = s21_is_less(x, y);
  int expect = 0;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

Suite *suite_s21_is_less() {
  Suite *suite = suite_create("s21_is_less");
  TCase *tcase = tcase_create("case_s21_is_less");

  tcase_add_test(tcase, decimal_is_less_1);
  tcase_add_test(tcase, decimal_is_less_2);
  tcase_add_test(tcase, decimal_is_less_3);
  tcase_add_test(tcase, decimal_is_less_4);
  tcase_add_test(tcase, decimal_is_less_5);
  tcase_add_test(tcase, decimal_is_less_6);
  tcase_add_test(tcase, decimal_is_less_7);
  tcase_add_test(tcase, decimal_is_less_8);
  tcase_add_test(tcase, special_test_is_less_1);
  tcase_add_test(tcase, special_test_is_less_2);
  tcase_add_test(tcase, special_test_is_less_3);
  tcase_add_test(tcase, special_test_is_less_4);
  tcase_add_test(tcase, special_test_is_less_5);

  suite_add_tcase(suite, tcase);
  return suite;
}

START_TEST(decimal_is_not_equal_1) {
  s21_decimal x = {{0, 0, 1, 0}};
  s21_decimal y = {{0, 0, 1, 0}};
  int ourRes = s21_is_not_equal(x, y);
  int expect = 0;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(decimal_is_not_equal_2) {
  s21_decimal x = {{0, 0, 1, NEGATIVE_DECIMAL}};
  s21_decimal y = {{0, 0, 1, NEGATIVE_DECIMAL}};

  int ourRes = s21_is_not_equal(x, y);
  int expect = 0;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(decimal_is_not_equal_3) {
  s21_decimal x = {{0, 0, 1, 0}};
  s21_decimal y = {{0, 0, 1, NEGATIVE_DECIMAL}};

  int ourRes = s21_is_not_equal(x, y);
  int expect = 1;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(decimal_is_not_equal_4) {
  s21_decimal x = {{0, 0, 1, NEGATIVE_DECIMAL}};
  s21_decimal y = {{0, 0, 1, 0}};

  int ourRes = s21_is_not_equal(x, y);
  int expect = 1;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(decimal_is_not_equal_5) {
  s21_decimal x = {{0, 52, 1, 0}};
  s21_decimal y = {{0, 0, 1, 0}};
  int ourRes = s21_is_not_equal(x, y);
  int expect = 1;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(decimal_is_not_equal_6) {
  s21_decimal x = {{0, 0, 1, 0}};
  s21_decimal y = {{1747, 0, 1, 0}};
  int ourRes = s21_is_not_equal(x, y);
  int expect = 1;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(decimal_is_not_equal_7) {
  s21_decimal x = {{0, 0, 1, NEGATIVE_DECIMAL}};
  s21_decimal y = {{1747, 0, 1, 0}};

  int ourRes = s21_is_not_equal(x, y);
  int expect = 1;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(special_test_is_not_equal_1) {
  s21_decimal x = {{1, 2, 3, 655360}};
  s21_decimal y = {{3, 2, 1, -2146828288}};
  int ourRes = s21_is_not_equal(x, y);
  int expect = 1;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(special_test_is_not_equal_2) {
  s21_decimal x = {{1, 2, 3, -2146828288}};
  s21_decimal y = {{3, 2, 1, -2146828288}};
  int ourRes = s21_is_not_equal(x, y);
  int expect = 1;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(special_test_is_not_equal_3) {
  s21_decimal x = {{1, 2, 3, -2146566144}};
  s21_decimal y = {{3, 2, 1, -2146959360}};
  int ourRes = s21_is_not_equal(x, y);
  int expect = 1;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(special_test_is_not_equal_4) {
  s21_decimal x = {{10, 2, 3, -2146566144}};
  s21_decimal y = {{3, 2, 1, 524288}};
  int ourRes = s21_is_not_equal(x, y);
  int expect = 1;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(special_test_is_not_equal_5) {
  s21_decimal x = {{1, 2, 3, 917504}};
  s21_decimal y = {{1, 2, 3, 917504}};
  int ourRes = s21_is_not_equal(x, y);
  int expect = 0;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

Suite *suite_s21_is_not_equal() {
  Suite *suite = suite_create("s21_is_not_equal");
  TCase *tcase = tcase_create("case_s21_is_not_equal");

  tcase_add_test(tcase, decimal_is_not_equal_1);
  tcase_add_test(tcase, decimal_is_not_equal_2);
  tcase_add_test(tcase, decimal_is_not_equal_3);
  tcase_add_test(tcase, decimal_is_not_equal_4);
  tcase_add_test(tcase, decimal_is_not_equal_5);
  tcase_add_test(tcase, decimal_is_not_equal_6);
  tcase_add_test(tcase, decimal_is_not_equal_7);
  tcase_add_test(tcase, special_test_is_not_equal_1);
  tcase_add_test(tcase, special_test_is_not_equal_2);
  tcase_add_test(tcase, special_test_is_not_equal_3);
  tcase_add_test(tcase, special_test_is_not_equal_4);
  tcase_add_test(tcase, special_test_is_not_equal_5);

  suite_add_tcase(suite, tcase);
  return suite;
}

START_TEST(test_s21_negate_1) {
  s21_decimal num = {{1, 0, 0, 2147483648u}};
  s21_decimal res = {{1, 0, 0, 0}};
  int error = 0;
  error = s21_negate(num, &num);
  ck_assert_int_eq(num.bits[0], res.bits[0]);
  ck_assert_int_eq(num.bits[1], res.bits[1]);
  ck_assert_int_eq(num.bits[2], res.bits[2]);
  ck_assert_int_eq(num.bits[3], res.bits[3]);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(test_s21_negate_2) {
  s21_decimal num = {{1, 0, 0, 0}};
  s21_decimal res = {{1, 0, 0, 2147483648u}};
  int error = 0;
  error = s21_negate(num, &num);
  ck_assert_int_eq(num.bits[0], res.bits[0]);
  ck_assert_int_eq(num.bits[1], res.bits[1]);
  ck_assert_int_eq(num.bits[2], res.bits[2]);
  ck_assert_int_eq(num.bits[3], res.bits[3]);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(test_s21_negate_3) {
  s21_decimal num = {{1, 0, 0, 0}};
  int error = 0;
  error = s21_negate(num, NULL);
  ck_assert_int_eq(error, 1);
}
END_TEST

START_TEST(special_test_negate_1) {
  s21_decimal x = {{32444, 100, 343253, -2145976320}};
  s21_decimal z = {{0, 0, 0, 0}};
  s21_negate(x, &z);
  char ourRes[1000], expect[1000] = "32444 100 343253 1507328";
  snprintf(ourRes, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(ourRes, expect);
}
END_TEST

START_TEST(special_test_negate_2) {
  s21_decimal x = {{1, 1, 1, 917504}};
  s21_decimal z = {{0, 0, 0, 0}};
  s21_negate(x, &z);
  char ourRes[1000], expect[1000] = "1 1 1 2148401152";
  snprintf(ourRes, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(ourRes, expect);
}
END_TEST

START_TEST(special_test_negate_3) {
  s21_decimal x = {{0, 0, 0, 917504}};
  s21_decimal z = {{0, 0, 0, 0}};
  s21_negate(x, &z);
  char ourRes[1000], expect[1000] = "0 0 0 917504";
  snprintf(ourRes, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(ourRes, expect);
}
END_TEST

Suite *suite_s21_negate() {
  Suite *suite = suite_create("s21_negate");
  TCase *tcase = tcase_create("case_s21_negate");

  tcase_add_test(tcase, test_s21_negate_1);
  tcase_add_test(tcase, test_s21_negate_2);
  tcase_add_test(tcase, test_s21_negate_3);
  tcase_add_test(tcase, special_test_negate_1);
  tcase_add_test(tcase, special_test_negate_2);
  tcase_add_test(tcase, special_test_negate_3);

  suite_add_tcase(suite, tcase);

  return suite;
}

START_TEST(decimal_mul_1) {
  s21_decimal x = {{2, 0, 0, 0}};
  s21_decimal y = {{5, 0, 0, 0}};
  s21_decimal z = {{0, 0, 0, 0}};
  s21_mul(x, y, &z);
  char ourRes[1000], expect[1000] = "10 0 0 0";
  snprintf(ourRes, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(ourRes, expect);
}
END_TEST

START_TEST(decimal_mul_2) {
  s21_decimal x = {{2, 1, 2, 0}};
  s21_decimal y = {{5, 0, 0, 0}};
  s21_decimal z = {{0, 0, 0, 0}};
  s21_mul(x, y, &z);
  char ourRes[1000], expect[1000] = "10 5 10 0";
  snprintf(ourRes, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(ourRes, expect);
}
END_TEST

START_TEST(decimal_mul_3) {
  s21_decimal x = {{2, 0, 0, 0}};
  s21_decimal y = {{0, 0, 10, 0}};
  s21_decimal z = {{0, 0, 0, 0}};
  s21_mul(x, y, &z);
  char ourRes[1000], expect[1000] = "0 0 20 0";
  snprintf(ourRes, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(ourRes, expect);
}
END_TEST

START_TEST(decimal_mul_4) {
  s21_decimal x = {{1000000000, 0, 0, 0}};
  s21_decimal y = {{6, 0, 0, 0}};
  s21_decimal z = {{0, 0, 0, 0}};
  s21_mul(x, y, &z);
  char ourRes[1000], expect[1000] = "1705032704 1 0 0";
  snprintf(ourRes, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(ourRes, expect);
}
END_TEST

START_TEST(decimal_mul_5) {
  s21_decimal x = {{1000000000, 0, 0, 2147483648}};
  s21_decimal y = {{6, 0, 0, 2147483648}};
  s21_decimal z = {{0, 0, 0, 0}};
  s21_mul(x, y, &z);
  char ourRes[1000], expect[1000] = "1705032704 1 0 0";
  snprintf(ourRes, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(ourRes, expect);
}
END_TEST

START_TEST(decimal_mul_6) {
  s21_decimal x = {{1000000000, 0, 0, 2147483648}};
  s21_decimal y = {{6, 0, 0, 0}};
  s21_decimal z = {{0, 0, 0, 0}};
  s21_mul(x, y, &z);
  char ourRes[1000], expect[1000] = "1705032704 1 0 2147483648";
  snprintf(ourRes, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(ourRes, expect);
}
END_TEST

START_TEST(decimal_mul_7) {
  s21_decimal x = {{1, 0, 0, 0}};
  s21_decimal y = {{165, 22, 6587456, 0}};
  s21_decimal z = {{0, 0, 0, 0}};
  s21_mul(x, y, &z);
  char ourRes[1000], expect[1000] = "165 22 6587456 0";
  snprintf(ourRes, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(ourRes, expect);
}
END_TEST

START_TEST(special_test_mul_1) {
  s21_decimal x = {{1, 1, 1, 655360}};
  s21_decimal y = {{1, 1, 1, 655360}};
  s21_decimal z = {{0, 0, 0, 0}};
  s21_mul(x, y, &z);
  char ourRes[1000], expect[1000] = "1652684285 987621807 1844674408 655360";
  snprintf(ourRes, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(ourRes, expect);
}
END_TEST

START_TEST(special_test_mul_2) {
  s21_decimal x = {{1, 0, 0, 655360}};
  s21_decimal y = {{1, 0, 0, 655360}};
  s21_decimal z = {{0, 0, 0, 0}};
  s21_mul(x, y, &z);
  char ourRes[1000], expect[1000] = "1 0 0 1310720";
  snprintf(ourRes, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(ourRes, expect);
}
END_TEST

START_TEST(special_test_mul_3) {
  s21_decimal x = {{1, 0, 0, 655360}};
  s21_decimal y = {{1, 0, 0, -2146828288}};
  s21_decimal z = {{0, 0, 0, 0}};
  s21_mul(x, y, &z);
  char ourRes[1000], expect[1000] = "1 0 0 2148794368";
  snprintf(ourRes, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(ourRes, expect);
}
END_TEST

START_TEST(special_test_mul_4) {
  s21_decimal x = {{1, 0, 1, 917504}};
  s21_decimal y = {{1, 0, 0, -2146828288}};
  s21_decimal z = {{0, 0, 0, 0}};
  s21_mul(x, y, &z);
  char ourRes[1000], expect[1000] = "1 0 1 2149056512";
  snprintf(ourRes, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(ourRes, expect);
}
END_TEST

Suite *suite_s21_mul() {
  Suite *suite = suite_create("s21_mul");
  TCase *tcase = tcase_create("s21_mul");
  suite_add_tcase(suite, tcase);

  tcase_add_test(tcase, decimal_mul_1);
  tcase_add_test(tcase, decimal_mul_2);
  tcase_add_test(tcase, decimal_mul_3);
  tcase_add_test(tcase, decimal_mul_4);
  tcase_add_test(tcase, decimal_mul_5);
  tcase_add_test(tcase, decimal_mul_6);
  tcase_add_test(tcase, decimal_mul_7);
  tcase_add_test(tcase, special_test_mul_1);
  tcase_add_test(tcase, special_test_mul_2);
  tcase_add_test(tcase, special_test_mul_3);
  tcase_add_test(tcase, special_test_mul_4);

  return suite;
}

START_TEST(test_s21_floor_1) {
  s21_decimal num = {{15, 0, 0, 65536}};
  s21_decimal res = {{1, 0, 0, 0}};
  int error = 0;
  error = s21_floor(num, &num);
  ck_assert_int_eq(num.bits[0], res.bits[0]);
  ck_assert_int_eq(num.bits[1], res.bits[1]);
  ck_assert_int_eq(num.bits[2], res.bits[2]);
  ck_assert_int_eq(num.bits[3], res.bits[3]);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(test_s21_floor_2) {
  s21_decimal num = {{19, 0, 0, 65536}};
  s21_decimal res = {{1, 0, 0, 0}};
  int error = 0;
  error = s21_floor(num, &num);
  ck_assert_int_eq(num.bits[0], res.bits[0]);
  ck_assert_int_eq(num.bits[1], res.bits[1]);
  ck_assert_int_eq(num.bits[2], res.bits[2]);
  ck_assert_int_eq(num.bits[3], res.bits[3]);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(test_s21_floor_3) {
  s21_decimal num = {{155, 0, 0, 131072}};
  s21_decimal res = {{1, 0, 0, 0}};
  int error = 0;
  error = s21_floor(num, &num);
  ck_assert_int_eq(num.bits[0], res.bits[0]);
  ck_assert_int_eq(num.bits[1], res.bits[1]);
  ck_assert_int_eq(num.bits[2], res.bits[2]);
  ck_assert_int_eq(num.bits[3], res.bits[3]);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(test_s21_floor_4) {
  s21_decimal num = {{15, 0, 0, 2147549184u}};
  s21_decimal res = {{2, 0, 0, 2147483648u}};
  int error = 0;
  error = s21_floor(num, &num);
  ck_assert_int_eq(num.bits[0], res.bits[0]);
  ck_assert_int_eq(num.bits[1], res.bits[1]);
  ck_assert_int_eq(num.bits[2], res.bits[2]);
  ck_assert_int_eq(num.bits[3], res.bits[3]);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(test_s21_floor_5) {
  s21_decimal num = {{268435457, 1042612833, 542101086, 2149318656u}};
  s21_decimal res = {{2, 0, 0, 2147483648u}};
  int error = 0;
  error = s21_floor(num, &num);
  ck_assert_int_eq(num.bits[0], res.bits[0]);
  ck_assert_int_eq(num.bits[1], res.bits[1]);
  ck_assert_int_eq(num.bits[2], res.bits[2]);
  ck_assert_int_eq(num.bits[3], res.bits[3]);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(test_s21_floor_6) {
  s21_decimal num = {{0, 0, 0, 0}};
  int error = 0;
  error = s21_floor(num, NULL);
  ck_assert_int_eq(error, 1);
}
END_TEST

START_TEST(test_s21_floor_7) {
  s21_decimal num = {{21, 0, 0, NEGATIVE_DECIMAL}};
  s21_decimal res = {{3, 0, 0, NEGATIVE_DECIMAL}};
  set_exponent(&num, 1);
  int error = 0;
  error = s21_floor(num, &num);
  ck_assert_int_eq(num.bits[0], res.bits[0]);
  ck_assert_int_eq(num.bits[1], res.bits[1]);
  ck_assert_int_eq(num.bits[2], res.bits[2]);
  ck_assert_int_eq(num.bits[3], res.bits[3]);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(special_test_floor_1) {
  s21_decimal x = {{1, 2, 3, 917504}};
  s21_decimal z = {{0, 0, 0, 0}};
  s21_floor(x, &z);
  char ourRes[1000], expect[1000] = "553402 0 0 0";
  snprintf(ourRes, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(ourRes, expect);
}
END_TEST

START_TEST(special_test_floor_2) {
  s21_decimal x = {{1, 2, 3, -2146566144}};
  s21_decimal z = {{0, 0, 0, 0}};
  s21_floor(x, &z);
  char ourRes[1000], expect[1000] = "553403 0 0 2147483648";
  snprintf(ourRes, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(ourRes, expect);
}
END_TEST

START_TEST(special_test_floor_3) {
  s21_decimal x = {{33, 2, 3000, -2146107392}};
  s21_decimal z = {{0, 0, 0, 0}};
  s21_floor(x, &z);
  char ourRes[1000], expect[1000] = "56 0 0 2147483648";
  snprintf(ourRes, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(ourRes, expect);
}
END_TEST

Suite *suite_s21_floor() {
  Suite *suite = suite_create("s21_floor");
  TCase *tcase = tcase_create("case_s21_floor");

  tcase_add_test(tcase, test_s21_floor_1);
  tcase_add_test(tcase, test_s21_floor_2);
  tcase_add_test(tcase, test_s21_floor_3);
  tcase_add_test(tcase, test_s21_floor_4);
  tcase_add_test(tcase, test_s21_floor_5);
  tcase_add_test(tcase, test_s21_floor_6);
  tcase_add_test(tcase, test_s21_floor_7);
  tcase_add_test(tcase, special_test_floor_1);
  tcase_add_test(tcase, special_test_floor_2);
  tcase_add_test(tcase, special_test_floor_3);

  suite_add_tcase(suite, tcase);

  return suite;
}

START_TEST(test_from_dec_to_float_1) {
  s21_decimal x = {{15008, 0, 0, 0}};
  set_exponent(&x, 3);
  float res1;
  int n1 = s21_from_decimal_to_float(x, &res1);
  float res2 = 15.008;
  ck_assert_float_eq(res1, res2);
  ck_assert_int_eq(n1, 0);
}
END_TEST

START_TEST(test_from_dec_to_float_2) {
  s21_decimal x = {{15008, 0, 0, 0}};
  set_exponent(&x, 3);
  set_bit(&x.bits[3], 31, 1);
  float res1;
  int n1 = s21_from_decimal_to_float(x, &res1);
  float res2 = -15.008;
  ck_assert_float_eq(res1, res2);
  ck_assert_int_eq(n1, 0);
}
END_TEST

START_TEST(test_from_dec_to_float_3) {
  s21_decimal x = {{15008, 0, 0, 0}};
  set_exponent(&x, 3);
  set_bit(&x.bits[3], 31, 1);
  float res1 = 0;
  int n1 = s21_from_decimal_to_float(x, NULL);
  float res2 = 0;
  ck_assert_float_eq(res1, res2);
  ck_assert_int_eq(n1, 1);
}
END_TEST

START_TEST(test_from_dec_to_float_4) {
  s21_decimal x = {{1505345008, 0, 0, 0}};
  set_exponent(&x, 3);
  set_bit(&x.bits[3], 31, 1);
  float res1;
  int n1 = s21_from_decimal_to_float(x, &res1);
  float res2 = -1505345.008;
  ck_assert_float_eq(res1, res2);
  ck_assert_int_eq(n1, 0);
}
END_TEST

Suite *suite_s21_from_decimal_to_float() {
  Suite *suite = suite_create("s21_from_decimal_to_float");
  TCase *tcase = tcase_create("case_s21_from_decimal_to_float");

  tcase_add_test(tcase, test_from_dec_to_float_1);
  tcase_add_test(tcase, test_from_dec_to_float_2);
  tcase_add_test(tcase, test_from_dec_to_float_3);
  tcase_add_test(tcase, test_from_dec_to_float_4);

  suite_add_tcase(suite, tcase);

  return suite;
}

START_TEST(test_from_dec_to_int_1) {
  s21_decimal x = {{150, 13658, 0, 0}};
  set_exponent(&x, 10);
  set_bit(&x.bits[3], 31, 1);
  int y;
  s21_from_decimal_to_int(x, &y);
  ck_assert_int_eq(y, -5866);
}
END_TEST

START_TEST(test_from_dec_to_int_2) {
  s21_decimal x = {{150, 13658, 0, 0}};
  set_exponent(&x, 10);
  int y;
  s21_from_decimal_to_int(x, &y);
  ck_assert_int_eq(y, 5866);
}
END_TEST

START_TEST(test_from_dec_to_int_3) {
  s21_decimal x = {{150, 13658, 155, 0}};
  set_exponent(&x, 10);
  int y = 0;
  s21_from_decimal_to_int(x, &y);
  ck_assert_int_eq(y, 0);
}
END_TEST

START_TEST(test_from_dec_to_int_4) {
  s21_decimal x = {{2100000000, 0, 0, 0}};
  set_exponent(&x, 0);
  int y;
  s21_from_decimal_to_int(x, &y);
  ck_assert_int_eq(y, 2100000000);
}
END_TEST

START_TEST(test_from_dec_to_int_5) {
  s21_decimal x = {{2100000000, 0, 0, 0}};
  set_exponent(&x, 0);
  set_bit(&x.bits[3], 31, 1);
  int y;
  s21_from_decimal_to_int(x, &y);
  ck_assert_int_eq(y, -2100000000);
}
END_TEST

START_TEST(test_from_dec_to_int_6) {
  s21_decimal x = {{3100000000, 0, 0, 0}};
  set_exponent(&x, 0);
  set_bit(&x.bits[3], 31, 1);
  int y = 0;
  s21_from_decimal_to_int(x, &y);
  ck_assert_int_eq(y, 0);
}

START_TEST(test_from_dec_to_int_7) {
  s21_decimal x = {{3100000000, 0, 0, 0}};
  set_exponent(&x, 0);
  int y;
  int n1 = s21_from_decimal_to_int(x, &y);
  ck_assert_int_eq(n1, 1);
}
END_TEST

START_TEST(test_from_dec_to_int_8) {
  s21_decimal x = {{9, 0, 0, 0}};
  set_exponent(&x, 1);
  int y;
  s21_from_decimal_to_int(x, &y);
  ck_assert_int_eq(y, 0);
}
END_TEST

START_TEST(test_from_dec_to_int_9) {
  s21_decimal x = {{9, 0, 0, 0}};
  set_exponent(&x, 1);
  int y = s21_from_decimal_to_int(x, NULL);
  ck_assert_int_eq(y, 1);
}
END_TEST

Suite *suite_s21_from_decimal_to_int() {
  Suite *suite = suite_create("s21_from_decimal_to_int");
  TCase *tcase = tcase_create("case_s21_from_decimal_to_int");

  tcase_add_test(tcase, test_from_dec_to_int_1);
  tcase_add_test(tcase, test_from_dec_to_int_2);
  tcase_add_test(tcase, test_from_dec_to_int_3);
  tcase_add_test(tcase, test_from_dec_to_int_4);
  tcase_add_test(tcase, test_from_dec_to_int_5);
  tcase_add_test(tcase, test_from_dec_to_int_6);
  tcase_add_test(tcase, test_from_dec_to_int_7);
  tcase_add_test(tcase, test_from_dec_to_int_8);
  tcase_add_test(tcase, test_from_dec_to_int_9);
  suite_add_tcase(suite, tcase);

  return suite;
}

START_TEST(test_from_float_to_dec_1) {
  float src = 56.986;
  s21_decimal z = {{0, 0, 0, 0}};
  int n1 = s21_from_float_to_decimal(src, &z);
  char res1[1000], res2[1000] = "56986 0 0 196608";
  snprintf(res1, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(res1, res2);
  ck_assert_int_eq(n1, 0);
}
END_TEST

START_TEST(test_from_float_to_dec_2) {
  float src = 1.0 / 0.0;
  s21_decimal z = {{0, 0, 0, 0}};
  int n1 = s21_from_float_to_decimal(src, &z);
  char res1[1000], res2[1000] = "0 0 0 0";
  snprintf(res1, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(res1, res2);
  ck_assert_int_eq(n1, 1);
}
END_TEST

START_TEST(test_from_float_to_dec_3) {
  float src = -1.596;
  s21_decimal z = {{0, 0, 0, 0}};
  int n1 = s21_from_float_to_decimal(src, &z);
  char res1[1000], res2[1000] = "1596 0 0 2147680256";
  snprintf(res1, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(res1, res2);
  ck_assert_int_eq(n1, 0);
}
END_TEST

START_TEST(test_from_float_to_dec_4) {
  float src = 1 / 0.0;
  s21_decimal z = {{0, 0, 0, 0}};
  int n1 = s21_from_float_to_decimal(src, &z);
  char res1[1000], res2[1000] = "0 0 0 0";
  snprintf(res1, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(res1, res2);
  ck_assert_int_eq(n1, 1);
}
END_TEST

START_TEST(test_from_float_to_dec_5) {
  double src = 0;
  s21_decimal z = {{0, 0, 0, 0}};
  int n1 = s21_from_float_to_decimal(src, &z);
  char res1[1000], res2[1000] = "0 0 0 0";
  snprintf(res1, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(res1, res2);
  ck_assert_int_eq(n1, 0);
}
END_TEST

START_TEST(test_from_float_to_dec_6) {
  long double src = 0;
  s21_decimal z = {{0, 0, 0, 0}};
  int n1 = s21_from_float_to_decimal(src, &z);
  char res1[1000], res2[1000] = "0 0 0 0";
  snprintf(res1, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(res1, res2);
  ck_assert_int_eq(n1, 0);
}
END_TEST

START_TEST(test_from_float_to_dec_7) {
  float src = 1612354.986;
  s21_decimal z = {{0, 0, 0, 0}};
  int n1 = s21_from_float_to_decimal(src, &z);
  char res1[1000], res2[1000] = "1612355 0 0 0";
  snprintf(res1, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(res1, res2);
  ck_assert_int_eq(n1, 0);
}
END_TEST

START_TEST(test_from_float_to_dec_8) {
  float src = 124.4;
  int error = 0;
  error = s21_from_float_to_decimal(src, NULL);
  ck_assert_int_eq(error, 1);
}
END_TEST

START_TEST(test_from_float_to_dec_9) {
  float src = 0.000000986;
  s21_decimal z = {{0, 0, 0, 0}};
  int n1 = s21_from_float_to_decimal(src, &z);
  char res1[1000], res2[1000] = "986 0 0 589824";
  snprintf(res1, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(res1, res2);
  ck_assert_int_eq(n1, 0);
}
END_TEST

Suite *suite_s21_from_float_to_decimal() {
  Suite *suite = suite_create("s21_from_float_to_decimal");
  TCase *tcase = tcase_create("case_s21_from_float_to_decimal");

  tcase_add_test(tcase, test_from_float_to_dec_1);
  tcase_add_test(tcase, test_from_float_to_dec_2);
  tcase_add_test(tcase, test_from_float_to_dec_3);
  tcase_add_test(tcase, test_from_float_to_dec_4);
  tcase_add_test(tcase, test_from_float_to_dec_5);
  tcase_add_test(tcase, test_from_float_to_dec_6);
  tcase_add_test(tcase, test_from_float_to_dec_7);
  tcase_add_test(tcase, test_from_float_to_dec_8);
  tcase_add_test(tcase, test_from_float_to_dec_9);

  suite_add_tcase(suite, tcase);

  return suite;
}

START_TEST(test_from_int_to_dec_1) {
  s21_decimal decimal;
  null_decimal(&decimal);
  int i = -3000, res = 0;
  s21_from_int_to_decimal(i, &decimal);
  s21_from_decimal_to_int(decimal, &res);
  ck_assert_int_eq(i, res);
}
END_TEST

START_TEST(test_from_int_to_dec_2) {
  s21_decimal x = {{0, 0, 0, 0}};
  s21_decimal y = {{15, 0, 0, 0}};
  int z = 15;
  s21_from_int_to_decimal(z, &x);
  char res1[1000], res2[1000];
  snprintf(res1, sizeof(char) * 1000, "%u %u %u %u", x.bits[0], x.bits[1],
           x.bits[2], x.bits[3]);
  snprintf(res2, sizeof(char) * 1000, "%u %u %u %u", y.bits[0], y.bits[1],
           y.bits[2], y.bits[3]);
  ck_assert_str_eq(res1, res2);
}
END_TEST

START_TEST(test_from_int_to_dec_3) {
  s21_decimal x = {{0, 0, 0, 0}};
  s21_decimal y = {{15, 0, 0, 2147483648}};
  int z = -15;
  s21_from_int_to_decimal(z, &x);
  char res1[1000], res2[1000];
  snprintf(res1, sizeof(char) * 1000, "%u %u %u %u", x.bits[0], x.bits[1],
           x.bits[2], x.bits[3]);
  snprintf(res2, sizeof(char) * 1000, "%u %u %u %u", y.bits[0], y.bits[1],
           y.bits[2], y.bits[3]);
  ck_assert_str_eq(res1, res2);
}
END_TEST

START_TEST(test_from_int_to_dec_4) {
  s21_decimal x = {{0, 0, 0, 0}};
  s21_decimal y = {{0, 0, 0, 0}};
  int z = 0;
  s21_from_int_to_decimal(z, &x);
  char res1[1000], res2[1000];
  snprintf(res1, sizeof(char) * 1000, "%u %u %u %u", x.bits[0], x.bits[1],
           x.bits[2], x.bits[3]);
  snprintf(res2, sizeof(char) * 1000, "%u %u %u %u", y.bits[0], y.bits[1],
           y.bits[2], y.bits[3]);
  ck_assert_str_eq(res1, res2);
}
END_TEST

START_TEST(test_from_int_to_dec_5) {
  int src = 124;
  int error = 0;
  error = s21_from_int_to_decimal(src, NULL);
  ck_assert_int_eq(error, 1);
}
END_TEST

Suite *suite_s21_from_int_to_decimal() {
  Suite *suite = suite_create("s21_from_int_to_decimal");
  TCase *tcase = tcase_create("case_s21_from_int_to_decimal");

  tcase_add_test(tcase, test_from_int_to_dec_1);
  tcase_add_test(tcase, test_from_int_to_dec_2);
  tcase_add_test(tcase, test_from_int_to_dec_3);
  tcase_add_test(tcase, test_from_int_to_dec_4);
  tcase_add_test(tcase, test_from_int_to_dec_5);
  suite_add_tcase(suite, tcase);

  return suite;
}

START_TEST(test_s21_round_1) {
  s21_decimal num = {{15, 0, 0, 65536}};
  s21_decimal res = {{2, 0, 0, 0}};
  int error = 0;
  error = s21_round(num, &num);
  ck_assert_int_eq(num.bits[0], res.bits[0]);
  ck_assert_int_eq(num.bits[1], res.bits[1]);
  ck_assert_int_eq(num.bits[2], res.bits[2]);
  ck_assert_int_eq(num.bits[3], res.bits[3]);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(test_s21_round_2) {
  s21_decimal num = {{149, 0, 0, 131072}};
  s21_decimal res = {{1, 0, 0, 0}};
  int error = 0;
  error = s21_round(num, &num);
  ck_assert_int_eq(num.bits[0], res.bits[0]);
  ck_assert_int_eq(num.bits[1], res.bits[1]);
  ck_assert_int_eq(num.bits[2], res.bits[2]);
  ck_assert_int_eq(num.bits[3], res.bits[3]);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(test_s21_round_3) {
  s21_decimal num = {{25, 0, 0, 65536}};
  s21_decimal res = {{3, 0, 0, 0}};
  int error = 0;
  error = s21_round(num, &num);
  ck_assert_int_eq(num.bits[0], res.bits[0]);
  ck_assert_int_eq(num.bits[1], res.bits[1]);
  ck_assert_int_eq(num.bits[2], res.bits[2]);
  ck_assert_int_eq(num.bits[3], res.bits[3]);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(test_s21_round_4) {
  s21_decimal num = {{251, 0, 0, 131072}};
  s21_decimal res = {{3, 0, 0, 0}};
  int error = 0;
  error = s21_round(num, &num);
  ck_assert_int_eq(num.bits[0], res.bits[0]);
  ck_assert_int_eq(num.bits[1], res.bits[1]);
  ck_assert_int_eq(num.bits[2], res.bits[2]);
  ck_assert_int_eq(num.bits[3], res.bits[3]);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(test_s21_round_5) {
  s21_decimal num = {{2818572289u, 2606532082u, 1355252715,
                      1835008}};  // 2.5000000000000000000000000001
  s21_decimal res = {{3, 0, 0, 0}};
  int error = 0;
  error = s21_round(num, &num);
  ck_assert_int_eq(num.bits[0], res.bits[0]);
  ck_assert_int_eq(num.bits[1], res.bits[1]);
  ck_assert_int_eq(num.bits[2], res.bits[2]);
  ck_assert_int_eq(num.bits[3], res.bits[3]);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(test_s21_round_6) {
  s21_decimal num = {{2818572289u, 2606532082u, 1355252715,
                      2149318656u}};  // 2.5000000000000000000000000001
  s21_decimal res = {{3, 0, 0, 2147483648u}};
  int error = 0;
  error = s21_round(num, &num);
  ck_assert_int_eq(num.bits[0], res.bits[0]);
  ck_assert_int_eq(num.bits[1], res.bits[1]);
  ck_assert_int_eq(num.bits[2], res.bits[2]);
  ck_assert_int_eq(num.bits[3], res.bits[3]);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(test_s21_round_7) {
  s21_decimal num = {{15, 0, 0, 2147549184u}};
  s21_decimal res = {{2, 0, 0, 2147483648u}};
  int error = 0;
  error = s21_round(num, &num);
  ck_assert_int_eq(num.bits[0], res.bits[0]);
  ck_assert_int_eq(num.bits[1], res.bits[1]);
  ck_assert_int_eq(num.bits[2], res.bits[2]);
  ck_assert_int_eq(num.bits[3], res.bits[3]);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(test_s21_round_8) {
  s21_decimal num = {{1, 0, 0, 0}};
  int error = 0;
  error = s21_round(num, NULL);
  ck_assert_int_eq(error, 1);
}
END_TEST

START_TEST(special_test_round_1) {
  s21_decimal x = {{1, 2, 3, 917504}};
  s21_decimal z = {{0, 0, 0, 0}};
  s21_round(x, &z);
  char ourRes[1000], expect[1000] = "553402 0 0 0";
  snprintf(ourRes, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(ourRes, expect);
}
END_TEST

START_TEST(special_test_round_2) {
  s21_decimal x = {{10, 100, 3, 1376256}};
  s21_decimal z = {{0, 0, 0, 0}};
  s21_round(x, &z);
  char ourRes[1000], expect[1000] = "0 0 0 0";
  snprintf(ourRes, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(ourRes, expect);
}
END_TEST

START_TEST(special_test_round_3) {
  s21_decimal x = {{16, 100, 3, 851968}};
  s21_decimal z = {{0, 0, 0, 0}};
  s21_round(x, &z);
  char ourRes[1000], expect[1000] = "5534023 0 0 0";
  snprintf(ourRes, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(ourRes, expect);
}
END_TEST

Suite *suite_s21_round() {
  Suite *suite = suite_create("s21_round");
  TCase *tcase = tcase_create("case_s21_round");

  tcase_add_test(tcase, test_s21_round_1);
  tcase_add_test(tcase, test_s21_round_2);
  tcase_add_test(tcase, test_s21_round_3);
  tcase_add_test(tcase, test_s21_round_4);
  tcase_add_test(tcase, test_s21_round_5);
  tcase_add_test(tcase, test_s21_round_6);
  tcase_add_test(tcase, test_s21_round_7);
  tcase_add_test(tcase, test_s21_round_8);
  tcase_add_test(tcase, special_test_round_1);
  tcase_add_test(tcase, special_test_round_2);
  tcase_add_test(tcase, special_test_round_3);

  suite_add_tcase(suite, tcase);

  return suite;
}

START_TEST(test_s21_truncate_1) {
  s21_decimal num = {{15, 0, 0, 65536}};
  s21_decimal res = {{1, 0, 0, 0}};
  int error = 0;
  error = s21_truncate(num, &num);
  ck_assert_int_eq(num.bits[0], res.bits[0]);
  ck_assert_int_eq(num.bits[1], res.bits[1]);
  ck_assert_int_eq(num.bits[2], res.bits[2]);
  ck_assert_int_eq(num.bits[3], res.bits[3]);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(test_s21_truncate_2) {
  s21_decimal num = {{2818572289u, 2606532082u, 1355252715, 2149318656u}};
  s21_decimal res = {{2, 0, 0, 2147483648u}};
  int error = 0;
  error = s21_truncate(num, &num);
  ck_assert_int_eq(num.bits[0], res.bits[0]);
  ck_assert_int_eq(num.bits[1], res.bits[1]);
  ck_assert_int_eq(num.bits[2], res.bits[2]);
  ck_assert_int_eq(num.bits[3], res.bits[3]);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(test_s21_truncate_3) {
  s21_decimal num = {{0, 0, 0, 0}};
  s21_decimal res = {{0, 0, 0, 0}};
  int error = 0;
  error = s21_truncate(num, &num);
  ck_assert_int_eq(num.bits[0], res.bits[0]);
  ck_assert_int_eq(num.bits[1], res.bits[1]);
  ck_assert_int_eq(num.bits[2], res.bits[2]);
  ck_assert_int_eq(num.bits[3], res.bits[3]);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(test_s21_truncate_4) {
  s21_decimal num = {{0, 0, 0, NEGATIVE_DECIMAL}};
  s21_decimal res = {{0, 0, 0, NEGATIVE_DECIMAL}};
  int error = 0;
  error = s21_truncate(num, &num);
  ck_assert_int_eq(num.bits[0], res.bits[0]);
  ck_assert_int_eq(num.bits[1], res.bits[1]);
  ck_assert_int_eq(num.bits[2], res.bits[2]);
  ck_assert_int_eq(num.bits[3], res.bits[3]);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(test_s21_truncate_5) {
  s21_decimal num = {{1, 0, 0, 0}};
  int error = 0;
  error = s21_truncate(num, NULL);
  ck_assert_int_eq(error, 1);
}
END_TEST

START_TEST(special_test_truncate_1) {
  s21_decimal x = {{32444, 100, 343253, -2145976320}};
  s21_decimal z = {{0, 0, 0, 0}};
  s21_truncate(x, &z);
  char ourRes[1000], expect[1000] = "63 0 0 2147483648";
  snprintf(ourRes, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(ourRes, expect);
}
END_TEST

START_TEST(special_test_truncate_2) {
  s21_decimal x = {{1, 1, 1, 917504}};
  s21_decimal z = {{0, 0, 0, 0}};
  s21_truncate(x, &z);
  char ourRes[1000], expect[1000] = "184467 0 0 0";
  snprintf(ourRes, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(ourRes, expect);
}
END_TEST

START_TEST(special_test_truncate_3) {
  s21_decimal x = {{0, 0, 0, 851968}};
  s21_decimal z = {{0, 0, 0, 0}};
  s21_truncate(x, &z);
  char ourRes[1000], expect[1000] = "0 0 0 0";
  snprintf(ourRes, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(ourRes, expect);
}
END_TEST

Suite *suite_s21_truncate() {
  Suite *suite = suite_create("s21_truncate");
  TCase *tcase = tcase_create("case_s21_truncate");

  tcase_add_test(tcase, test_s21_truncate_1);
  tcase_add_test(tcase, test_s21_truncate_2);
  tcase_add_test(tcase, test_s21_truncate_3);
  tcase_add_test(tcase, test_s21_truncate_4);
  tcase_add_test(tcase, test_s21_truncate_5);
  tcase_add_test(tcase, special_test_truncate_1);
  tcase_add_test(tcase, special_test_truncate_2);
  tcase_add_test(tcase, special_test_truncate_3);

  suite_add_tcase(suite, tcase);

  return suite;
}

START_TEST(decimal_div_1) {
  s21_decimal x = {{310000000, 0, 0, 0}};
  s21_decimal y = {{1, 0, 0, 0}};
  s21_decimal z = {{0, 0, 0, 0}};
  s21_div(x, y, &z);
  char ourRes[1000], expect[1000] = "310000000 0 0 0";
  snprintf(ourRes, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(ourRes, expect);
}
END_TEST

START_TEST(decimal_div_2) {
  s21_decimal x = {{0xffffffff, 0xffffffff, 0xffffffff, 0}};
  s21_decimal y = {{2, 0, 0, 28 << 16}};
  s21_decimal z = {{0, 0, 0, 0}};
  int err = 0;
  err = s21_div(x, y, &z);
  ck_assert_int_eq(err, 0);
}
END_TEST

START_TEST(decimal_div_3) {
  s21_decimal x = {{52525252, 0, 0, 0}};
  s21_decimal y = {{0, 0, 0, 0}};
  s21_decimal z = {{0, 0, 0, 0}};
  int err = 0;
  err = s21_div(x, y, &z);
  ck_assert_int_eq(err, 3);
}
END_TEST

START_TEST(decimal_div_4) {
  s21_decimal x = {{52525252, 0, 0, 2147483648}};
  s21_decimal y = {{0, 0, 0, 0}};
  s21_decimal z = {{0, 0, 0, 0}};
  int err = 0;
  err = s21_div(x, y, &z);
  ck_assert_int_eq(err, 3);
}
END_TEST

START_TEST(decimal_div_5) {
  s21_decimal x = {{52525252, 0, 0, 0}};
  s21_decimal y = {{0, 0, 0, 2147483648}};
  s21_decimal z = {{0, 0, 0, 0}};
  int err = 0;
  err = s21_div(x, y, &z);
  ck_assert_int_eq(err, 3);
}
END_TEST

START_TEST(decimal_div_6) {
  s21_decimal x = {{52525252, 0, 0, 8845}};
  s21_decimal y = {{0, 0, 0, 10}};
  s21_decimal z = {{0, 0, 0, 0}};
  int err = 0;
  err = s21_div(x, y, &z);
  ck_assert_int_eq(err, 3);
}
END_TEST

START_TEST(decimal_div_7) {
  s21_decimal x = {{52525252, 0, 0, 65465}};
  s21_decimal y = {{0, 0, 0, 9598595}};
  s21_decimal z = {{0, 0, 0, 0}};
  int err = 0;
  err = s21_div(x, y, &z);
  ck_assert_int_eq(err, 3);
}
END_TEST

START_TEST(decimal_div_8) {
  s21_decimal x = {{0xffffffff, 0xffffffff, 0xffffffff, NEGATIVE_DECIMAL}};
  s21_decimal y = {{2, 0, 0, 28 << 16}};
  s21_decimal z = {{0, 0, 0, 0}};
  int err = 0;
  err = s21_div(x, y, &z);
  ck_assert_int_eq(err, 0);
}
END_TEST

START_TEST(decimal_div_9) {
  s21_decimal x = {{5, 0, 50, NEGATIVE_DECIMAL}};
  s21_decimal y = {{5, 0, 0, NEGATIVE_DECIMAL}};
  s21_decimal z = {{0, 0, 0, 0}};
  int err = 0;
  err = s21_div(x, y, &z);
  ck_assert_int_eq(err, 0);
}
END_TEST

START_TEST(decimal_div_10) {
  s21_decimal x = {{0, 0, 0, NEGATIVE_DECIMAL}};
  s21_decimal y = {{5, 0, 0, NEGATIVE_DECIMAL}};
  s21_decimal z = {{0, 0, 0, 0}};
  set_exponent(&y, 20);
  int err = 0;
  err = s21_div(x, y, &z);
  char ourRes[1000], expect[1000] = "0 0 0 0";
  snprintf(ourRes, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(ourRes, expect);
  ck_assert_int_eq(err, 0);
}
END_TEST

START_TEST(decimal_div_11) {
  s21_decimal x = {{5, 0, 0, NEGATIVE_DECIMAL}};
  s21_decimal y = {{0, 0, 0, NEGATIVE_DECIMAL}};
  s21_decimal z = {{0, 0, 0, 0}};
  set_exponent(&y, 28);
  int err = 0;
  err = s21_div(x, y, &z);
  ck_assert_int_eq(err, 3);
}
END_TEST

START_TEST(decimal_div_12) {
  s21_decimal x = {{5, 0, 0, NEGATIVE_DECIMAL}};
  s21_decimal y = {{5, 0, 0, NEGATIVE_DECIMAL}};
  s21_decimal z = {{0, 0, 0, 0}};
  set_exponent(&x, 28);
  set_exponent(&y, 28);
  s21_div(x, y, &z);
  char ourRes[1000], expect[1000] = "1 0 0 0";
  snprintf(ourRes, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(ourRes, expect);
}
END_TEST

START_TEST(special_test_div_1) {
  s21_decimal x = {{1, 1, 1, 655360}};
  s21_decimal y = {{1, 1, 1, 655360}};
  s21_decimal z = {{0, 0, 0, 0}};
  s21_div(x, y, &z);
  char ourRes[1000], expect[1000] = "1 0 0 0";
  snprintf(ourRes, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(ourRes, expect);
}
END_TEST

START_TEST(special_test_div_2) {
  s21_decimal x = {{1, 1, 1, 655360}};
  s21_decimal y = {{2, 1, 1, 655360}};
  s21_decimal z = {{0, 0, 0, 0}};
  s21_div(x, y, &z);
  char ourRes[1000], expect[1000] = "100000 0 0 0";
  snprintf(ourRes, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(ourRes, expect);
}
END_TEST

START_TEST(special_test_div_3) {
  s21_decimal x = {{1, 1, 1, 10 << 16}};
  s21_decimal y = {{1, 10, 1, NEGATIVE_DECIMAL + (15 << 16)}};
  s21_decimal z = {{0, 0, 0, 0}};
  s21_div(x, y, &z);
  char ourRes[1000], expect[1000] = "1019311944 458670364 542101085 2148990976";
  snprintf(ourRes, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(ourRes, expect);
}
END_TEST

START_TEST(special_test_div_4) {
  s21_decimal x = {{1, 1, 1, 983040}};
  s21_decimal y = {{1, 1, 1, -2146500608}};
  s21_decimal z = {{0, 0, 0, 0}};
  s21_div(x, y, &z);
  char ourRes[1000], expect[1000] = "1 0 0 2147483648";
  snprintf(ourRes, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(ourRes, expect);
}
END_TEST

Suite *suite_s21_div() {
  Suite *suite = suite_create("s21_div");
  TCase *tcase = tcase_create("case_s21_div");

  tcase_add_test(tcase, decimal_div_1);
  tcase_add_test(tcase, decimal_div_2);
  tcase_add_test(tcase, decimal_div_3);
  tcase_add_test(tcase, decimal_div_4);
  tcase_add_test(tcase, decimal_div_5);
  tcase_add_test(tcase, decimal_div_6);
  tcase_add_test(tcase, decimal_div_7);
  tcase_add_test(tcase, decimal_div_8);
  tcase_add_test(tcase, decimal_div_9);
  tcase_add_test(tcase, decimal_div_10);
  tcase_add_test(tcase, decimal_div_11);
  tcase_add_test(tcase, decimal_div_12);
  tcase_add_test(tcase, special_test_div_1);
  tcase_add_test(tcase, special_test_div_2);
  tcase_add_test(tcase, special_test_div_3);
  tcase_add_test(tcase, special_test_div_4);

  suite_add_tcase(suite, tcase);

  return suite;
}

START_TEST(decimal_mod_1) {
  s21_decimal x = {{150000008, 0, 0, 0}};
  s21_decimal y = {{15, 0, 0, 0}};
  s21_decimal z = {{0, 0, 0, 0}};
  set_exponent(&x, 3);
  int err = 0;
  err = s21_mod(x, y, &z);
  char ourRes[1000], expect[1000] = "8 0 0 196608";
  sprintf(ourRes, "%u %u %u %u", z.bits[0], z.bits[1], z.bits[2], z.bits[3]);
  ck_assert_str_eq(ourRes, expect);
  ck_assert_int_eq(err, 0);
}
END_TEST

START_TEST(decimal_mod_2) {
  s21_decimal x = {{150000008, 0, 500000000, 0}};
  s21_decimal y = {{1, 0, 0, 0}};
  s21_decimal z = {{0, 0, 0, 0}};
  set_exponent(&x, 3);
  int err = 0;
  err = s21_mod(x, y, &z);
  char ourRes[1000], expect[1000] = "8 0 0 196608";
  snprintf(ourRes, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(ourRes, expect);
  ck_assert_int_eq(err, 0);
}
END_TEST

START_TEST(decimal_mod_3) {
  s21_decimal x = {{91, 0, 0, 0}};
  s21_decimal y = {{50, 0, 0, 0}};
  s21_decimal z = {{0, 0, 0, 0}};
  int err = 0;
  err = s21_mod(x, y, &z);
  char ourRes[1000], expect[1000] = "41 0 0 0";
  snprintf(ourRes, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(ourRes, expect);
  ck_assert_int_eq(err, 0);
}
END_TEST

START_TEST(decimal_mod_4) {
  s21_decimal x = {{91, 0, 0, 0}};
  s21_decimal y = {{95, 0, 0, 0}};
  s21_decimal z = {{0, 0, 0, 0}};
  int err = 0;
  err = s21_mod(x, y, &z);
  char ourRes[1000], expect[1000] = "91 0 0 0";
  snprintf(ourRes, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(ourRes, expect);
  ck_assert_int_eq(err, 0);
}
END_TEST

START_TEST(decimal_mod_5) {
  s21_decimal x = {{91, 0, 0, 0}};
  s21_decimal y = {{0, 0, 0, 0}};
  s21_decimal z = {{0, 0, 0, 0}};
  int err = 0;
  err = s21_mod(x, y, &z);
  char ourRes[1000], expect[1000] = "0 0 0 0";
  snprintf(ourRes, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(ourRes, expect);
  ck_assert_int_eq(err, 3);
}
END_TEST

START_TEST(decimal_mod_6) {
  s21_decimal x = {{91, 0, 0, 28 << 16}};
  s21_decimal y = {{5, 0, 0, 0}};
  s21_decimal z = {{0, 0, 0, 0}};
  // set_exponent(&x, 30);
  s21_mod(x, y, &z);
  char ourRes[1000], expect[1000] = "91 0 0 1835008";
  snprintf(ourRes, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(ourRes, expect);
}
END_TEST

START_TEST(decimal_mod_7) {
  s21_decimal x = {{125, 0, 0, 0}};
  s21_decimal y = {{3, 0, 0, 0}};
  s21_decimal z = {{0, 0, 0, 0}};
  set_exponent(&x, 1);
  int err = 0;
  err = s21_mod(x, y, &z);
  char ourRes[1000], expect[1000] = "5 0 0 65536";
  snprintf(ourRes, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(ourRes, expect);
  ck_assert_int_eq(err, 0);
}
END_TEST

START_TEST(decimal_mod_8) {
  s21_decimal x = {{125, 0, 0, 0}};
  s21_decimal y = {{3, 0, 0, 0}};
  s21_decimal z = {{0, 0, 0, 0}};
  set_exponent(&y, 1);
  int err = 0;
  err = s21_mod(x, y, &z);
  char ourRes[1000], expect[1000] = "2 0 0 65536";
  snprintf(ourRes, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(ourRes, expect);
  ck_assert_int_eq(err, 0);
}
END_TEST

START_TEST(decimal_mod_9) {
  s21_decimal x = {{14425, 1, 1, 0}};
  s21_decimal y = {{14425, 1, 1, 0}};
  s21_decimal z = {{0, 0, 0, 0}};
  set_exponent(&x, 22);
  set_exponent(&y, 22);
  int err = 0;
  err = s21_mod(x, y, &z);
  char ourRes[1000], expect[1000] = "0 0 0 0";
  snprintf(ourRes, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(ourRes, expect);
  ck_assert_int_eq(err, 0);
}
END_TEST

START_TEST(decimal_mod_10) {
  s21_decimal x = {{14425, 1, 1, 0}};
  s21_decimal y = {{14425, 1, 1, 0}};
  s21_decimal *z = NULL;
  set_exponent(&x, 22);
  set_exponent(&y, 22);
  int err = 0;
  err = s21_mod(x, y, z);
  ck_assert_int_eq(err, 0);
}
END_TEST

START_TEST(special_test_mod_1) {
  s21_decimal x = {{1, 1, 1, 65536}};
  s21_decimal y = {{1, 1, 1, -2147418112}};
  s21_decimal z = {{0, 0, 0, 0}};
  s21_mod(x, y, &z);
  char ourRes[1000], expect[1000] = "0 0 0 0";
  snprintf(ourRes, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(ourRes, expect);
}
END_TEST

START_TEST(special_test_mod_2) {
  s21_decimal x = {{1, 1, 1, -2147418112}};
  s21_decimal y = {{1, 1, 1, -2146828288}};
  s21_decimal z = {{0, 0, 0, 0}};
  s21_mod(x, y, &z);
  char ourRes[1000], expect[1000] = "0 0 0 0";
  snprintf(ourRes, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(ourRes, expect);
}
END_TEST

START_TEST(special_test_mod_3) {
  s21_decimal x = {{1, 2, 3, -2147418112}};
  s21_decimal y = {{3, 2, 1, -2146828288}};
  s21_decimal z = {{0, 0, 0, 0}};
  s21_mod(x, y, &z);
  char ourRes[1000], expect[1000] = "589934595 294967296 0 2148139008";
  snprintf(ourRes, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(ourRes, expect);
}
END_TEST

START_TEST(special_test_mod_4) {
  s21_decimal x = {{1, 2, 3, 655360}};
  s21_decimal y = {{3, 2, 1, -2146828288}};
  s21_decimal z = {{0, 0, 0, 0}};
  s21_mod(x, y, &z);
  char ourRes[1000], expect[1000] = "4294967291 4294967293 0 655360";
  snprintf(ourRes, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(ourRes, expect);
}
END_TEST

Suite *suite_s21_mod() {
  Suite *suite = suite_create("s21_mod");
  TCase *tcase = tcase_create("case_s21_mod");

  tcase_add_test(tcase, decimal_mod_1);
  tcase_add_test(tcase, decimal_mod_2);
  tcase_add_test(tcase, decimal_mod_3);
  tcase_add_test(tcase, decimal_mod_4);
  tcase_add_test(tcase, decimal_mod_5);
  tcase_add_test(tcase, decimal_mod_6);
  tcase_add_test(tcase, decimal_mod_7);
  tcase_add_test(tcase, decimal_mod_8);
  tcase_add_test(tcase, decimal_mod_9);
  tcase_add_test(tcase, decimal_mod_10);
  tcase_add_test(tcase, special_test_mod_1);
  tcase_add_test(tcase, special_test_mod_2);
  tcase_add_test(tcase, special_test_mod_3);
  tcase_add_test(tcase, special_test_mod_4);

  suite_add_tcase(suite, tcase);

  return suite;
}
