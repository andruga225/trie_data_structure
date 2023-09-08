// trie.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#include <map>
#include <unordered_map>
#include <iostream>
#include <fstream>
#include <chrono>
#include "Trie.h"


int main()
{
	setlocale(LC_ALL, "Russian");

	Trie<std::string, int> test;
	while (true)
	{
		std::cout << "Доступные операции:\n";
		std::cout << "1. Добавить новое значение\n";
		std::cout << "2. Изменить значение\n";
		std::cout << "3. Проверить наличие ключа\n";
		std::cout << "4. Удалить значение\n";
		std::cout << "5. Вывод дерева\n";
		std::cout << "6. Выйти из программы\n";
		int input;
		std::cin >> input;

		std::string key;
		int value;

		switch (input) {
		case 1:
			std::cin >> key >> value;
			test[key] = value;
			std::cout << "Значение добавлено\n";
			break;
		case 2:
			std::cin >> key >> value;
			//Не очень логично с точки зрения пользователя
			//test[key] = value;
			if (test.isKey(key))
			{
				test[key] = value;
				std::cout << "Значение обновлено\n";
			}
			else 
			{
				std::cout << "Ключ не найден\n";
			}
			break;
		case 3:
			std::cin >> key;
			if (test.isKey(key))
				std::cout << "Ключ найден\n";
			else
				std::cout << "Ключ не найден\n";
			break;
		case 4:
			std::cin >> key;
			if (test.erase(key) == 0)
				std::cout << "Ключ не найден\n";
			else
				std::cout << "Успешно удалено\n";
			break;
		case 5:
			test.print();
			break;
		case 6:
			return 0;
			break;
		default:
			continue;
		}
	}
}
