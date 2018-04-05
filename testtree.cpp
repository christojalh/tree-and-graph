#include "unittests.h"
#include "treeandmap.h"
#include <iostream>

void verifyChildChecking() 
{
	std::cout << "\nInitializing bare root of value 6\n";
	int y = 6;
	MySearchTree<int> tree(y);
	auto parent = tree.getRoot();
	std::cout << "Checking this node for children R/L: " << parent->hasL() << "/" << parent->hasR() << "\n";
	// hasChildren(tree.getRoot());
	std::cout << "Inserting nodes on R/L of values 3, 8\n";
	tree.insert(8);
	tree.insert(3);
	std::cout << "Checking this node for children R/L: " << parent->hasL() << "/" << parent->hasR() << "\n";
}

void verifyInsertMultiple()
{
	std::cout << "\nInitializing bare root of value 6\n";
	int y = 6;
	MySearchTree<int> tree(y);
	auto current = tree.getRoot();

	std::cout << "Inserting values 7, 8, 9, 10\n";	
	tree.insert(8);
	tree.insert(9);	
	tree.insert(7);
	tree.insert(10);
	std::cout << "Verifying our tree contains 6/7/8/9/10/11 : " << tree.contains(6) << "/" << tree.contains(7)
		<< "/" << tree.contains(8) << "/" << tree.contains(9) << "/" << tree.contains(10) 
		<< "/" <<  tree.contains(11) << "\n";

	std::cout << "Traveling to right child and checking if it contains 2 children now...\n";
	current = current->getR().get();
	std::cout << "Checking this node for children L/R: " << current->hasL() << "/" << current->hasR() << "\n";

	std::cout << "Traveling to right child and checking if it contains 1 child now...\n";

	// auto swapper1 = &current->getR();
	auto myptr = &current->getR();
	current = current->getR().get();

	// auto swapper2 = &current->getR();

	std::cout << "Checking this node for children L/R: " << current->hasL() << "/" << current->hasR() << "\n";
	std::cout << "The value of the right child is: " << current->getR().get()->getVal() << "\n";

	std::cout << "Reset()ing the right child\n";
	current.reset();
	std::cout << "Checking this node for children L/R: " << current->hasL() << "/" << current->hasR() << "\n";

	// std::cout << "first swapper: " << swapper1->get()->getVal();
	// std::cout << "second swapper: " << swapper2->get()->getVal();
	// tree.swap(*swapper1, *swapper2);
	// std::cout << "first swapper: " << swapper1->get()->getVal();
	// std::cout << "second swapper: " << swapper2->get()->getVal();

}

void verifyDeleteMultiple()
{
	std::cout << "\nInitializing bare root of value 6\n";
	int y = 6;
	MySearchTree<int> tree(y);

	std::cout << "Inserting values 8, 9, 7, 10\n";	
	tree.insert(8);
	// tree.insert(9);	
	// tree.insert(7);
	// tree.insert(10);	

	std::cout << "Inserting values 3, 1, 4\n";
	tree.insert(3);
	tree.insert(1);
	tree.insert(4);

	std::cout << "Deleting all children except 1 and 7\n";
	// tree.remove(8);
	// tree.remove(9);
	// tree.remove(4);
	// tree.remove(10);
	// tree.remove(3);

	std::cout << "6's left child is now: " << tree.getRoot()->getL()->getVal() << "\n";
	std::cout << "6's right child is now: " << tree.getRoot()->hasR();
}

// template <typename T>
// void hasChildren(typename MySearchTree<T>::Node* parent)
// {
// 	std::cout << "Checking this node for children R/L: " << parent->hasL() << "/" << parent->hasR();
// }