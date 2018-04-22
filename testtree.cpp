#include "unittests.h"
#include "treeandmap.h"
#include <iostream>
#include <algorithm>
#include <vector>
#include <ctime>

// Test_Registrar<TreeTests> TreeTests::registrar;

int cmp(int val1, int val2) 
{
	if (val1 < val2) 
	{
		return -1;
	}
	else if (val1 > val2) 
	{
		return 1;
	}
	else 
	{
		return 0;
	}
}

// inserts 10k shuffled integers, checks if it contains() all of them
bool TreeTests::insertMany()
{
	std::srand ( unsigned ( std::time(0) ) );

	std::vector<int> vec;
	for (int ii = 0; ii < 10000; ++ii)
	{
		vec.push_back(ii);
	}
	std::random_shuffle(vec.begin(), vec.end());

	int root = rand() % 10000;
	MySearchTree<int> tree(cmp);
	if (tree.insert(root))
	{
		// continue
	}
	for (int ii = 0; ii < 10000; ++ii)
	{
		if (tree.insert(vec[ii])) 
		{
			// successful insert
		}
		else
		{
			// ignore duplicate 
		}
	}

	for (int ii = 0; ii < 10000; ++ii)
	{
		if (tree.contains(ii))
		{
			continue;
		}
		else
		{
			return false;
		}
	}

	return true;
}

// inserts 10k shuffled integers, chooses a random integer to leave alone, deletes the rest in a random fashion. Returns true if the value of the root is the chosen integer
bool TreeTests::deleteMany()
{
	int numInts = 10000;
	std::srand ( unsigned ( std::time(0) ) );

	std::vector<int> vec;
	for (int ii = 0; ii < numInts; ++ii)
	{
		vec.push_back(ii);
	}
	std::random_shuffle(vec.begin(), vec.end());

	int root = rand() % numInts;
	int final = rand() % numInts; 

	while (root == final) 
	{
		final = rand() % numInts;
	}

	MySearchTree<int> tree(cmp);
	if (tree.insert(root))
	{
		// continue
	}
	// std::cout << "Final: " << final << "\n";
	// std::cout << "Root: " << tree.getRoot()->getVal() << "\n";
	// std::cout << "Insertion sequence: ";

	for (int ii = 0; ii < vec.size(); ++ii)
	{
		if (tree.insert(vec[ii])) 
		{
			// successful insert
		}
		else
		{
			// ignore duplicate 
		}
	}

	std::random_shuffle(vec.begin(), vec.end());
	for (int ii = 0; ii < numInts; ++ii) 
	{
		if (final == vec[ii])
		{
			continue;
		}
		else if (tree.remove(vec[ii]))
		{

		}
		else
		{
			return false; // signifies we have somehow removed something twice
		}
	}

	// std::cout << "Value of root: " << tree.getRoot()->getVal() << "\n\n";
	if (tree.getRoot()->getVal() == final)
	{
		return true;			
	}
	return false;
}

// verifies basic insert(), contain(), remove() functionality
bool TreeTests::singleElementTest() 
{
	int root = 2; 
	MySearchTree<int> tree(cmp); 
	if (tree.insert(root))
	{
		// continue
	}
	if ( !( tree.getRoot()->getVal() == root ) )
	{
		return false;
	} 

	if ( !tree.contains(root) )
	{
		return false;
	}

	if ( !( tree.insert(5) ) )
	{
		return false;
	}

	// inserting duplicate here
	if ( tree.insert(5) ) 
	{
		return false;
	}

	if ( !tree.contains(5) )
	{
		return false;
	}

	if ( !tree.remove(5) )
	{
		return false;
	}

	if ( tree.contains(5) )
	{
		return false; 
	}

	// remove a nonexistent value
	if ( tree.remove(5) ) 
	{
		return false;
	}

	return true;
}

// void verifyChildChecking() 
// {
// 	std::cout << "\nInitializing bare root of value 6\n";
// 	int y = 6;
// 	MySearchTree<int> tree(y);
// 	auto parent = tree.getRoot();
// 	std::cout << "Checking this node for children R/L: " << parent->hasL() << "/" << parent->hasR() << "\n";
// 	// hasChildren(tree.getRoot());
// 	std::cout << "Inserting nodes on R/L of values 3, 8\n";
// 	tree.insert(8);
// 	tree.insert(3);
// 	std::cout << "Checking this node for children R/L: " << parent->hasL() << "/" << parent->hasR() << "\n";
// }

// void verifyInsertMultiple()
// {
// 	std::cout << "\nInitializing bare root of value 6\n";
// 	int y = 6;
// 	MySearchTree<int> tree(y);
// 	auto current = tree.getRoot();

// 	std::cout << "Inserting values 7, 8, 9, 10\n";	
// 	tree.insert(8);
// 	tree.insert(9);	
// 	tree.insert(7);
// 	tree.insert(10);
// 	std::cout << "Verifying our tree contains 6/7/8/9/10/11 : " << tree.contains(6) << "/" << tree.contains(7)
// 		<< "/" << tree.contains(8) << "/" << tree.contains(9) << "/" << tree.contains(10) 
// 		<< "/" <<  tree.contains(11) << "\n";

// 	std::cout << "Traveling to right child and checking if it contains 2 children now...\n";
// 	current = current->getR().get();
// 	std::cout << "Checking this node for children L/R: " << current->hasL() << "/" << current->hasR() << "\n";

// 	std::cout << "Traveling to right child and checking if it contains 1 child now...\n";

// 	current = current->getR().get();


// 	std::cout << "Checking this node for children L/R: " << current->hasL() << "/" << current->hasR() << "\n";
// 	std::cout << "The value of the right child is: " << current->getR().get()->getVal() << "\n";

// }