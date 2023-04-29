## **Лабораторна робота 11**

## **Панкеєв Владислав Олексійович 922-Б**

### 11.Дано масив з N цілих чисел. Визначити, чи є в масиві елементи, що повторюються; якщо такі є, то створити масив, в якому вказати, скільки разів які елементи повторюються. 
### Таким чином, в результуючому масиві кожен непарний елемент - число, що повторюються; кожен парний елемент - кількість повторювань.

## сновна частина:

### **Вміст файлу main.c**
```c
#include "lib.h"

int main()
{
    	int arr_const[] = {23, 89, 89, 23, 67, 89, 0, 37, 37};
	int *arr = arr_const;
	int qua_elemnts = 8;
	
	filter_arr(arr, qua_elemnts,0);

    return 0;
}
``` 

### **Вміст файлу lib.c**

```c
#include <stdio.h>
#include <malloc.h>

int filter_arr(int *arr_const, int qua_elements, int num)
{
	int *arr = 0;
	int elements = 0;
	int qua_repeat = 0;
	unsigned long int add_byte_in_arr = 0;
	int index_elements_in_arr = 0;
	int dont_repeat = 0;
	int error = 0;

	for (int i = 0; i <= qua_elements; i++) {
		elements = *(arr_const + i);
		qua_repeat = 0;
		error = 0;

		if (i > 0) {
			for (dont_repeat = 0; dont_repeat < i; dont_repeat++) {
				if (*(arr_const + dont_repeat) == elements) {
					error = 1;
					break;
				}
			}
		}

		if (elements % 2 == 0) {
			error = 1;
		}

		if (error == 0) {
			for (int n = i; n <= qua_elements; n++) {
				if (elements == *(arr_const + n)) {
					qua_repeat++;
				}
			}
		}

		if (qua_repeat > 0 && qua_repeat % 2 == 0) {
			add_byte_in_arr += 2;

			arr = realloc(arr, sizeof(int) * add_byte_in_arr);
			*(arr + index_elements_in_arr) = *(arr_const + i);
			*(arr + index_elements_in_arr + 1) = qua_repeat;

			index_elements_in_arr += 2;
		}
	}

	if (arr == 0) {
		elements = 0;
	} else {
		elements = *(arr + num);
	}

	free(arr);
	arr = NULL;

	return elements;
}
```
### **Вміст файлу lib.h**
```c
int filter_arr(int a[], int b, int i);
```

### **Вміст файлу test.c**

```c
#include "../src/lib.h"
#include <stdlib.h>
#include <check.h>

START_TEST(test_filter_arr_standart)
{
	int test_arr[] = {23,89,89,23,67,89,0,37,37};
	int *arr_test = test_arr;
	int qua_elemnts_test_arr = 8; 
	int expected_test_arr[] = {23,2,37,2};
	int *arr_expected = expected_test_arr;
	int qua_elemnts_expected_arr = 3;
	 
	for(int i = 0; i <= qua_elemnts_expected_arr;i++)
	{
		int actual_result = filter_arr(arr_test, qua_elemnts_test_arr,i);
		ck_assert_int_eq(*(arr_expected + i), actual_result);
	}	
}
END_TEST

START_TEST(test_filter_arr_parni)
{
	int test_arr[] = {24,54,88,24,66,88,88,36,36};
	int *arr_test = test_arr;
	int qua_elemnts_test_arr = 8; 
	int expected_test_result = 0;
	int actual_test_result = filter_arr(arr_test, qua_elemnts_test_arr,0);
	
	ck_assert_int_eq(expected_test_result, actual_test_result);		
}
END_TEST

START_TEST(test_filter_arr_zero)
{
	int test_arr[] = {0,0,0};
	int *arr_test = test_arr;
	int qua_elemnts_test_arr = 2; 
	int expected_test_result = 0;
	int actual_test_result = filter_arr(arr_test, qua_elemnts_test_arr,0);
	
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
```

### **Відладник lldb**
```
Process 59689 launched: '/home/progalaba/lab11/dist/main.bin' (x86_64)
Process 59689 stopped
* thread #1, name = 'main.bin', stop reason = breakpoint 1.1
    frame #0: 0x0000555555555330 main.bin`filter_arr(arr_const=0x00007fffffffde00, qua_elements=8, number=0) at lib.c:125:13
   122      else
   123      {
   124          elements = *(arr + number);
-> 125          return elements;
   126      }
   127      
   128      free(arr);
(lldb) p *arr
(int) $0 = 23
(lldb) p *(arr+1)
(int) $1 = 2
(lldb) p *(arr+2)
(int) $2 = 37
(lldb) p *(arr+3)
(int) $3 = 2
(lldb) 
```
### **Результат тесту та покриття коду**
```
Running suite(s): lab11
100%: Checks: 3, Failures: 0, Errors: 0
llvm-profdata merge -sparse dist/test.profraw -o dist/test.profdata
llvm-cov report dist/test.bin -instr-profile=dist/test.profdata src/*.c
Filename                                         Regions    Missed Regions     Cover   Functions  Missed Functions  Executed       Lines      Missed Lines     Cover    Branches   Missed Branches     Cover
------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
/home/progalaba/lab11/src/lib.c          27                 0   100.00%           1                 0   100.00%          47                 0   100.00%          22                 0   100.00%
------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
TOTAL                                                 27                 0   100.00%           1                 0   100.00%          47                 0   100.00%          22                 0   100.00%

----------------------------------------------------------------------------
```

### **Дослідження витоків**
```

==40989== Memcheck, a memory error detector
==40989== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==40989== Using Valgrind-3.18.1 and LibVEX; rerun with -h for copyright info
==40989== Command: dist/main.bin
==40989== Parent PID: 40982
==40989==
==40989==
==40989== HEAP SUMMARY:
==40989==     in use at exit: 0 bytes in 0 blocks
==40989==   total heap usage: 2 allocs, 2 frees, 24 bytes allocated
==40989==
==40989== All heap blocks were freed -- no leaks are possible
==40989==
==40989== For lists of detected and suppressed errors, rerun with: -s
==40989== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
```
----------------------------------------------------------------------------

### **Структура проекту лабораторної роботи:**
```   
├── Doxyfile
├── Makefile
├── README.md
├── test
│   └── test.c
└── src
    ├── lib.c
    ├── lib.h
    └── main.c
```
![Memory leak result](https://github.com/Azivus/lab11/blob/main/photo_2023-04-29_10-02-16.jpg)
