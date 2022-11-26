#include <check.h>
#include <string.h>
#include "s21_string.h"

START_TEST(empty_strings)
{
	const char *h = "";
	const char *n = "";

	ck_assert_ptr_eq(strstr(h, n), s21_strstr(h, n));
}
END_TEST

START_TEST(empty_needle)
{
	const char *h = "abssak aksdk lala 123";
	const char *n = "";

	ck_assert_ptr_eq(strstr(h, n), s21_strstr(h, n));
}
END_TEST

START_TEST(empty_haystack)
{
	const char *h = "";
	const char *n = "abcd";

	ck_assert_ptr_eq(strstr(h, n), s21_strstr(h, n));
}
END_TEST

START_TEST(not_found)
{
	const char *h = "PlAneT EaRtH";
	const char *n = "planeta";

	ck_assert_ptr_eq(strstr(h, n), s21_strstr(h, n));
	n = "pLaEt";
	ck_assert_ptr_eq(strstr(h, n), s21_strstr(h, n));
	n = " Et";
	ck_assert_ptr_eq(strstr(h, n), s21_strstr(h, n));
	n = "tH0";
	ck_assert_ptr_eq(strstr(h, n), s21_strstr(h, n));
	h = "hOl\0a";
	n = "hOLa";
	ck_assert_ptr_eq(strstr(h, n), s21_strstr(h, n));
}
END_TEST

START_TEST(found)
{
	const char *h = "PlAnEt EaRtH";
	const char *n = "pLaNeT";

	ck_assert_ptr_eq(strstr(h, n), s21_strstr(h, n));
	n = "eT ";
	ck_assert_ptr_eq(strstr(h, n), s21_strstr(h, n));
	n = " eA";
	ck_assert_ptr_eq(strstr(h, n), s21_strstr(h, n));
	n = "a";
	ck_assert_ptr_eq(strstr(h, n), s21_strstr(h, n));
	n = "T";
	ck_assert_ptr_eq(strstr(h, n), s21_strstr(h, n));
	n = "Th";
	ck_assert_ptr_eq(strstr(h, n), s21_strstr(h, n));
	h = "plaNet Earth PlaN";
	n = "PlaN";
	ck_assert_ptr_eq(strstr(h, n), s21_strstr(h, n));
	h = "PLazet Earth plAn";
	n = "PLaN";
	ck_assert_ptr_eq(strstr(h, n), s21_strstr(h, n));
}
END_TEST


Suite *suite_s21_strcasestr(void)
{
	Suite *s = NULL;
	TCase *tc = NULL;

	s = suite_create("suite_s21_strcasestr");
	tc = tcase_create("tcase_s21_strcasestr");
	if (s != NULL && tc != NULL) {
		tcase_add_test(tc, empty_strings);
		tcase_add_test(tc, empty_needle);
		tcase_add_test(tc, empty_haystack);
		tcase_add_test(tc, not_found);
		tcase_add_test(tc, found);
		suite_add_tcase(s, tc);
	}

	return (s);
}
