#include "libpascalreal.h"

#include <check.h>

#include <stdlib.h>

static double real_mantissa_all_set(void) {
  double rv = 1.0;
  double divi = 0.5;
  for (int i = 0; i < 39; ++i) {
    rv += divi;
    divi /= 2;
  }
  return rv;
}

START_TEST(to_double_1_25) {
  const uint8_t real_1_25[] = {0x81, 0x00, 0x00, 0x00, 0x00, 0x20};
  const double res = libpascalreal_to_double(real_1_25);
  ck_assert_double_eq(res, 1.25);
}
END_TEST

START_TEST(to_double_m_24_125) {
  const uint8_t real_m_24_125[] = {0x85, 0x00, 0x00, 0x00, 0x00, 0xc1};
  const double res = libpascalreal_to_double(real_m_24_125);
  ck_assert_double_eq(res, -24.125);
}
END_TEST

START_TEST(to_double_closest_to_zero) {
  const uint8_t real_almost_zero[] = {0x00, 0xff, 0xff, 0xff, 0xff, 0x7f};
  const double res = libpascalreal_to_double(real_almost_zero);
  ck_assert_double_eq(res, ldexp(real_mantissa_all_set(), -129));
}
END_TEST

START_TEST(to_double_largest_possible) {
  const uint8_t real_largest_possible[] = {0xff, 0xff, 0xff, 0xff, 0xff, 0x7f};
  const double res = libpascalreal_to_double(real_largest_possible);
  ck_assert_double_eq(res, ldexp(real_mantissa_all_set(), 126));
}
END_TEST

START_TEST(from_double_infinity) {
  const uint8_t expected_real[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x80};
  uint8_t real[sizeof(expected_real)];
  libpascalreal_from_double(real, HUGE_VAL);
  ck_assert_mem_eq(real, expected_real, sizeof(real));
}
END_TEST

START_TEST(from_double_too_large) {
  const uint8_t expected_real[] = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff};
  uint8_t real[sizeof(expected_real)];
  libpascalreal_from_double(real, ldexp(-1.0, 200));
  ck_assert_mem_eq(real, expected_real, sizeof(real));
}
END_TEST

START_TEST(from_double_too_small) {
  const uint8_t expected_real[6] = {0};
  uint8_t real[sizeof(expected_real)];
  libpascalreal_from_double(real, ldexp(1.0, -200));
  ck_assert_mem_eq(real, expected_real, sizeof(real));
}
END_TEST

START_TEST(from_double_3_125) {
  const uint8_t expected_real[] = {0x82, 0x00, 0x00, 0x00, 0x00, 0x48};
  uint8_t real[sizeof(expected_real)];
  libpascalreal_from_double(real, 3.125);
  ck_assert_mem_eq(real, expected_real, sizeof(real));
}
END_TEST

START_TEST(from_double_m_42_625) {
  const uint8_t expected_real[] = {0x86, 0x00, 0x00, 0x00, 0x80, 0xAA};
  uint8_t real[sizeof(expected_real)];
  libpascalreal_from_double(real, -42.625);
  ck_assert_mem_eq(real, expected_real, sizeof(real));
}
END_TEST

static Suite *libpascalreal_suite(void) {
  Suite *s = suite_create("libpascalreal");

  TCase *to_double = tcase_create("to_double");
  tcase_add_test(to_double, to_double_1_25);
  tcase_add_test(to_double, to_double_m_24_125);
  tcase_add_test(to_double, to_double_closest_to_zero);
  tcase_add_test(to_double, to_double_largest_possible);
  suite_add_tcase(s, to_double);

  TCase *from_double = tcase_create("from_double");
  tcase_add_test(from_double, from_double_infinity);
  tcase_add_test(from_double, from_double_too_large);
  tcase_add_test(from_double, from_double_too_small);
  tcase_add_test(from_double, from_double_3_125);
  tcase_add_test(from_double, from_double_m_42_625);
  suite_add_tcase(s, from_double);

  return s;
}

int main(void) {
  Suite *const s = libpascalreal_suite();
  SRunner *const sr = srunner_create(s);

  srunner_run_all(sr, CK_VERBOSE);
  const int number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
