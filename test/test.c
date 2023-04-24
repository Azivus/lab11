#include "../src/lib.h"
#include <stdlib.h>
#include <check.h>

START_TEST(test_filter_arr_standart)
{
	int test_arr[] = { 23, 89, 89, 23, 67, 89, 0, 37, 37 };
	int *arr_test = test_arr;
	int qua_elemnts_test_arr = 8;
	int expected_test_arr[] = { 23, 2, 37, 2 };
	int *arr_expected = expected_test_arr;
	int qua_elemnts_expected_arr = 3;

	for (int i = 0; i <= qua_elemnts_expected_arr; i++) {
		int actual_result = filter_arr(arr_test, qua_elemnts_test_arr, i);
		ck_assert_int_eq(*(arr_expected + i), actual_result);
	}
}
END_TEST

START_TEST(test_filter_arr_parni)
{
	int test_arr[] = { 24, 54, 88, 24, 66, 88, 88, 36, 36 };
	int *arr_test = test_arr;
	int qua_elemnts_test_arr = 8;
	int expected_test_result = 0;
	int actual_test_result = filter_arr(arr_test, qua_elemnts_test_arr, 0);

	ck_assert_int_eq(expected_test_result, actual_test_result);
}
END_TEST

START_TEST(test_filter_arr_zero)
{
	int test_arr[] = { 0, 0, 0 };
	int *arr_test = test_arr;
	int qua_elemnts_test_arr = 2;
	int expected_test_result = 0;
	int actual_test_result = filter_arr(arr_test, qua_elemnts_test_arr, 0);

	ck_assert_int_eq(expected_test_result, actual_test_result);
}
END_TEST

Suite *lab_test_suite(void)
{
	Suite *s;
	TCase *tc_filter_arr;

	s = suite_create("lab11");

	tc_filter_arr = tcase_create("filter_arr");

	tcase_add_test(tc_filter_arr, test_filter_arr_standart);
	tcase_add_test(tc_filter_arr, test_filter_arr_parni);
	tcase_add_test(tc_filter_arr, test_filter_arr_zero);

	suite_add_tcase(s, tc_filter_arr);

	return s;
}

int main(void)
{
	int number_failed;
	Suite *s;
	SRunner *sr;

	s = lab_test_suite();
	sr = srunner_create(s);

	srunner_run_all(sr, CK_NORMAL);
	number_failed = srunner_ntests_failed(sr);
	srunner_free(sr);

	return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
