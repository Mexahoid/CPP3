// CPP3.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>
#include <ctime>
#include <list>




template <class T> T mtd(T a)
{
	return a;
}

template <class T> T mtd(T a, T b)
{
	return a + b;
}

template <class T> T mtd()
{
	return nullptr;
}




void message(tree<int>::node* nd)
{
	std::cout << "Node: \n" << nd->get_data() << std::endl;
}

int main()
{
	int kek = 10;
	int sos = 20;

	int sas = mtd(kek);
	int ses = mtd(kek, sos);

	tree<int> *t = new tree<int>();

	t->insert(10, false);
	srand(time(nullptr));

	std::cout << "Tree head-only: ";
	std::cout << std::endl << "pre-order: " << std::endl;
	t->invoke_procedure(message, 0);
	std::cout << std::endl << "in-order: " << std::endl;
	t->invoke_procedure(message, 1);
	std::cout << std::endl << "post-order: " << std::endl;
	t->invoke_procedure(message, 2);

	t->insert(20, true, t->get_node(10));
	std::cout << "Trying to insert to existing" << std::endl;

	try {
		t->insert(10, true, t->get_node(10));
	}
	catch (tree<int>::tree_exception ex)
	{
		std::cout << ex.get_message() << std::endl;
	}

	std::cout << "Trying to add new head" << std::endl;
	try {
		t->insert(140, true);
	}
	catch (tree<int>::tree_exception ex)
	{
		std::cout << ex.get_message() << std::endl;
	}

	t->insert(30, false, t->get_node(10));

	std::cout << "Tree head + l-r: ";
	std::cout << std::endl << "pre-order: " << std::endl;
	t->invoke_procedure(message, 0);
	std::cout << std::endl << "in-order: " << std::endl;
	t->invoke_procedure(message, 1);
	std::cout << std::endl << "post-order: " << std::endl;
	t->invoke_procedure(message, 2);
/*
	tree<int>::iterator *wi = t->get_iterator(true);

	std::cout << "Width iterator:" << std::endl;
	while(wi->has_next())
	{
		std::cout << wi->get_val() << std::endl;
		wi++;
	}

	tree<int>::iterator *di = t->get_iterator(false);
	std::cout << "Depth iterator:" << std::endl;
	while (di->has_next())
	{
		std::cout << di->get_val() << std::endl;
		di++;
	}*/

	tree<int>::iterator wi = t->get_iterator(true);

	std::cout << "Width iterator:" << std::endl;
	while (wi.has_next())
	{
		std::cout << wi.get_val() << std::endl;
		wi++;
	}

	tree<int>::iterator di = t->get_iterator(false);
	std::cout << "Depth iterator:" << std::endl;
	while (di.has_next())
	{
		std::cout << di.get_val() << std::endl;
		di++;
	}
	std::cin.get();
	delete t;
    return 0;
}

