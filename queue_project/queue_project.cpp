#include <iostream>
#include <vector>
#include <string>
#include <Windows.h>
#include <utility>
#include "LQueue.h"

using namespace std;

void swap(LQueue* q1, LQueue* q2) {
	LQueue* tmp = new LQueue(std::move(*q1));
	*q1 = std::move(*q2);
	*q2 = std::move(*tmp);
}


int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);


	vector<LQueue> query_vector(2);
	int vector_index = 0;

	char Continue = 'y';

	cout << "Вам доступны 2 очереди" << endl;

	while (Continue == 'y') {

		int option, tmp_priority;
		string str_tmp;

		cout << "\nСейчас выбрана очередь " << vector_index + 1 <<
			"\nВам доступны следующие опции\n"
			"1.Добавить элемент в очередь\n"
			"2.Удалить элемент из очереди\n"
			"3.Показать информацию об элементе в голове списка\n"
			"4.Вывод всех элементов очереди\n"
			"5.Проверка на пустоту очереди\n"
			"6.Вывод числа элементов\n"
			"7.Выбрать другую очередь\n"
			"8.Копировать выбранную очередь в другую\n"
			"9.Произвести обмен между очередями\n"
			"Ваш выбор: ";
		cin >> option;

		switch (option) {
		case(1):
			int tmp_num;
			cout << "\nВведите число: ";
			cin >> tmp_num;

			cout << "\nВыберите приоритет:\n"
				"1.Высокий приоритет\n"
				"2.Средний приоритет\n"
				"3.Низкий приоритет\n"
				"Ваш выбор: ";
			cin >> tmp_priority;

			Priority priority;
			switch (tmp_priority) {
			case 1:
				priority = HIGH;
				break;
			case 2:
				priority = MEDIUM;
				break;
			case 3:
				priority = LOW;
				break;
			}

			query_vector[vector_index].Push(tmp_num, priority);
			break;
		case(2):
			query_vector[vector_index].Pop();
			break;
		case(3):
			try {
				cout << "\nЗначение:" << query_vector[vector_index].GetFirstValue() << "\nПриоритет: ";

				switch (query_vector[vector_index].GetFirstPriority()) {
				case HIGH:
					str_tmp = "высокий";
					break;
				case MEDIUM:
					str_tmp = "средний";
					break;
				case LOW:
					str_tmp = "низкий";
					break;
				}
				cout << str_tmp;
			}
			catch (exception& err) {
				cout <<err.what();
			}
			break;
		case(4):
			cout << "\nОчередь " << vector_index + 1 << " состоит из следующих элементов: ";
			for (int i = 0; i < query_vector[vector_index].GetSize(); i++) {
				cout << query_vector[vector_index][i] << " ";
			}
			break;
		case 5:
			cout << "\nОчередь " << (query_vector[vector_index].IsEmpty() ? "пустая" : "не пустая");
			break;
		case 6:
			cout << "\nВыберите приоритет:\n"
				"1.Высокий приоритет\n"
				"2.Средний приоритет\n"
				"3.Низкий приоритет\n"
				"4.Без приоритета";
			do {
				cout << "\nВаш выбор: ";
				cin >> tmp_priority;

				switch (tmp_priority) {
				case 1:
					priority = HIGH;
					break;
				case 2:
					priority = MEDIUM;
					break;
				case 3:
					priority = LOW;
					break;
				case 4:
					break;
				default:
					cout << "Пожалуйста, выберите число от 1 до 4";
				}
			} while (tmp_priority > 4 || tmp_priority < 1);
			if (tmp_priority !=4)
				cout << "\nЧисло элементов с данным приоритетом: " << query_vector[vector_index].Count(priority);
			else
				cout << "\nВсего элементов: " << query_vector[vector_index].GetSize();
			break;
		case 7:
			vector_index = !vector_index;
			break;
		case 8:
			query_vector[!vector_index] = query_vector[vector_index]; 
			break;
		case 9:
			swap(query_vector[0],query_vector[1]);
			break;
		default:
			cout << "Вы выбрали не то число" << endl;
			cin.clear();
			cin.ignore(32767, '\n');
			break;
		}
		cout << "\n";
	}
}
