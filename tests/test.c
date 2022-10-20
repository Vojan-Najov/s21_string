#include <stdlib.h>
#include <check.h>
#include "s21_string.h"
#include "s21_test.h"

static int	run_test_suite(Suite *test_suite)
{
	int		number_failed = 0;
	SRunner	*sr = NULL;

	sr = srunner_create(test_suite);
	srunner_run_all(sr, CK_NORMAL);
	number_failed = srunner_ntests_failed(sr);
	srunner_free(sr);

	return number_failed;
}

int	main(void)
{
	int		number_failed = 0;
	Suite	*suite_array[] = {
		suite_s21_memchr(),	NULL
	};

	for (size_t i = 0; suite_array[i]; ++i)
	{
		number_failed += run_test_suite(suite_array[i]);
	}

	return number_failed ? EXIT_FAILURE : EXIT_SUCCESS;
}
