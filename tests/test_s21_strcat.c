#include <check.h>
#include <string.h>
#include "s21_string.h"

START_TEST (empty_src_1)
{
	char	src21[] = "";
	char	src[] = "";
	char	dest21[] = "abc";
	char	dest[] = "abc";

	ck_assert_ptr_eq(s21_strcat(dest21, src21), dest21);
	strcat(dest, src);
	ck_assert(strcmp(dest, dest21) == 0);
}
END_TEST

START_TEST (empty_src_2)
{
	char	src21[] = "\0abc";
	char	src[] = "\0abc";
	char	dest21[10] = "abc";
	char	dest[10] = "abc";

	ck_assert_ptr_eq(s21_strcat(dest21, src21), dest21);
	strcat(dest, src);
	ck_assert(strcmp(dest, dest21) == 0);
}
END_TEST

START_TEST (cat_1)
{
	char	src21[1024];
	char	src[1024];
	char	dest21[2048];
	char	dest[2048];

	for (int c = 'a', i = 0; i < 1023; ++i, ++c)
	{
		dest[i] = dest21[i] = src[i] = src21[i] = (char) c;
		c = (c > 'z' ? 'a' : c);	
	}
	dest[1023] = dest21[1023] = src[1023] = src21[1023] = '\0';
	ck_assert_ptr_eq(s21_strcat(dest21, src21), dest21);
	strcat(dest, src);
	ck_assert(strcmp(dest, dest21) == 0);
}
END_TEST

START_TEST (cat_2)
{
	char	src[] = "dsalaskl332023020221340";
	char	dest21[2048] = "\0\0\0\0";
	char	dest[2048] = "\0\0\0\0";

	ck_assert_ptr_eq(s21_strcat(dest21, src), dest21);
	strcat(dest, src);
	ck_assert(strcmp(dest, dest21) == 0);
}
END_TEST

Suite	*suite_s21_strcat(void)
{
	Suite	*s = suite_create("suite_s21_strcat");
	TCase	*tc = tcase_create("tcase_s21_strcat");

	tcase_add_test(tc, empty_src_1);
	tcase_add_test(tc, empty_src_2);
	tcase_add_test(tc, cat_1);
	tcase_add_test(tc, cat_2);
	suite_add_tcase(s, tc);

	return s;
}
