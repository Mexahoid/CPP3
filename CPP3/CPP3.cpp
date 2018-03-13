// CPP3.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>
#include <ctime>

void message(int arg)
{
	std::cout << arg << ' ';
}

int main()
{
	Tree<int> *t = new Tree<int>();

	srand(time(nullptr));
	for (int i = 1; i < 11; i++)
	{
		t->insert(i * rand() % 10);
	}

	std::cout << std::endl << "pre-order: " << std::endl;
	t->print(message, 0);
	std::cout << std::endl << "in-order: " << std::endl;
	t->print(message, 1);
	std::cout << std::endl << "post-order: " << std::endl;
	t->print(message, 2);

	delete t;
    return 0;
}

