/**
\file lib.c
\brief Бібліотечний файл

Цей файл, містить реалізацію функції filter_arr.
*/

#include <stdio.h>
#include <malloc.h>

/**
 
 Функція filter_arr
 \param *arr_const - Масив.
 \param qua_elements - кількість елементів у масиві.
 \param num - індекс єлемента у масиві для модульного тесту.
 
 
 Послідовність дій

- Створення змінних .

 *arr - динамічний масив у кий ми будемо записувати єлементи що повторюються.

 elements - зберігає елемент який ми будемо первіряти, повторюється він чи ні.
 
 qua_repeat - кількість повторювань.
 
 add_byte_in_arr - використовуються для збільшення динамічного масиву.
 
 index_elements_in_arr - індекс елемента у масиві.
 
 dont_repeat - використовується для превірки чи не превіряємо ми один і той самий елемент двічі.
 
 error - як що елемент у масиві не відповідає вимогам.
 
- Створюємо цикл який буде перебирати елементи у масиві що прийняла функція.

- Присвоюємо єлемент змінній.

- Встановлюємо кількість повторень та помилок при невідповідності вимогам.

- Первіряємо чи не працюємо ми з одним і тим самим єлементом двічі. Цикл у цій превірці пребирає елементи до того який ми перевіряємо зараз. Як що виявиться що цей елеиент вже опрацьовувався прериваємо операцію.

- Перевіряємо чи не є елемент парним.

- Перевіряємо як що єлемент відповідвє усім вимогам тоді починаємо шукати у масиві такіж елементи.

- Перевіряємо як що була знайдена парна кількість повторювань, тоді додаємо двійку до змінної яку потім використовуємо для збільшення нашого маисву. Записуємо число та кількість повторювань у масив. Додаємо двійку до зміннох яку потім віикористовуємо для запису єлементів у масив.

- Перевіряємо як що масив пусти то повертаємо 0, як що ні тоді повертаємо єелемент за індексом який передали у функцію.

- Звільнюємо пам'ять. 

*/

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
