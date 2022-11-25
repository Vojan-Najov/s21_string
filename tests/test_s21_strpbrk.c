#include <check.h>
#include <string.h>
#include "s21_string.h"

START_TEST(empty_strings)
{
	const char *s = "";
	const char *a = "";

	ck_assert_ptr_eq(strpbrk(s, a), s21_strpbrk(s, a));
}
END_TEST

START_TEST(empty_accept)
{
	const char *s = "ashs 12231 sjasj";
	const char *a = "";

	ck_assert_ptr_eq(strpbrk(s, a), s21_strpbrk(s, a));
}
END_TEST

START_TEST(empty_str)
{
	const char *s = "";
	const char *a = "abcdefg";

	ck_assert_ptr_eq(strpbrk(s, a), s21_strpbrk(s, a));
}
END_TEST

START_TEST(not_found)
{
	const char *s = "abhdha asjdj asjsj asj aodpdc";
	const char *a = "13839102";

	ck_assert_ptr_eq(strpbrk(s, a), NULL);
	ck_assert_ptr_eq(strpbrk(s, a), s21_strpbrk(s, a));
}
END_TEST

START_TEST(found)
{
	const char *s = "abhdha asjdj 9  1 asjsj asj 1234 aodpdc";
	const char *a = "13839102";

	ck_assert_ptr_ne(strpbrk(s, a), NULL);
	ck_assert_ptr_eq(strpbrk(s, a), s21_strpbrk(s, a));
}
END_TEST


Suite *suite_s21_strpbrk(void)
{
	Suite *s = NULL;
	TCase *tc = NULL;

	s = suite_create("suite_s21_strpbrk");
	tc = tcase_create("tcase_s21_strpbrk");
	if (s != NULL && tc != NULL) {
		tcase_add_test(tc, empty_strings);
		tcase_add_test(tc, empty_accept);
		tcase_add_test(tc, empty_str);
		tcase_add_test(tc, not_found);
		tcase_add_test(tc, found);
		suite_add_tcase(s, tc);
	}

	return (s);
}
