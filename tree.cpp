#include <cstdlib>
#include "treeandmap.h"
#include <iostream>
#include <memory>
#include <stdexcept>
#include <functional>

/* Christopher Lee	   
 * April 8th, 2018
 * 
 * This program is an implementation of a binary search tree. To create a tree using this program,
 * pass in the initial value you want as the root, then insert() the rest.
 *
 * Functionality:
 * -insert()
 *     NOTE: duplicate values are ignored and not inserted
 * -contains()
 * -remove()
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */


// template<typename T>
// MySearchTree<T>::MySearchTree(T value, std::function<int(T,T)> comparator): root(new Node(value)), compare(comparator)
// {
// 	// our only step here is to initialize the root 
// }

// template<typename T>
// MySearchTree<T>::~MySearchTree() 
// {
// 	// all allocated variables will be deleted by their respective unique_ptr when the search tree goes out of scope
// }

// template<typename T>
// typename MySearchTree<T>::Node* MySearchTree<T>::getRoot() 
// {
// 	return root.get();
// }

// // strategy: start from top, follow the tree down until an empty node is found. 
// // Create the new node. Make the parent node's L/R variable point to the new node. 
// // notes: assuming we're looking for a value, it's okay if multiple of the same value are in random places.
// //			as long as the first one is in place, we know that the tree contains it. However, if we want to sort
// //			the tree, this might become a problem.........
// template<typename T>
// bool MySearchTree<T>::insert(T value) 
// {
// 	Node* current = root.get();

// 	// we'll continue traversing the tree until a spot is found for the node
// 	while (true)
// 	{
// 		// if (value == current->getVal())
// 		if (compare(value, current->getVal()) == 0)
// 		{
// 			return false;
// 		}

// 		// else if (value > current->getVal())
// 		else if (compare(value, current->getVal()) == 1)
// 		{

// 			if (current->hasR()) 
// 			{
// 				// a child is found, so we travel to it to check if it can hold a new node
// 				current = current->getR().get();
// 			}
// 			else
// 			{
// 				// a spot is found for the node, so we initialize it and break out of the loop
// 				current->getR() = std::make_unique<Node>(value);
// 				return true;
// 			}
// 		}

// 		else if (compare(value, current->getVal()) == -1)
// 		{
// 			if (current->hasL()) 
// 			{
// 				// a child is found, so we travel to it to check if it can hold a new node
// 				current = current->getL().get();
// 			}
// 			else
// 			{
// 				// a spot is found for the node, so we initialize it and break out of the loop
// 				current->getL() = std::make_unique<Node>(value);
// 				return true;
// 			}
// 		}	
// 	}
// }


// template<typename T>
// bool MySearchTree<T>::contains(T value) 
// {
// 	Node* current = root.get();

// 	// we'll keep traversing the tree until we find the value or an empty node
// 	while (true)
// 	{
// 		if (current->getVal() == value) 
// 		{
// 			return true;
// 		}
// 		else
// 		{
// 			if (value > current->getVal())
// 			{
// 				if (current->hasR()) 
// 				{
// 					// a child is found, so we travel to it to continue our traversal
// 					current = current->getR().get();
// 				}
// 				else
// 				{
// 					// an empty node is found, signifying the tree doesn't contain the value
// 					return false;
// 				}
// 			}

// 			else if (value < current->getVal())
// 			{
// 				if (current->hasL()) 
// 				{
// 					// a child is found, so we travel to it to continue our traversal
// 					current = current->getL().get();
// 				}
// 				else
// 				{
// 					// an empty node is found, signifying the tree doesn't contain the value
// 					return false;
// 				}
// 			}		
// 		}
// 	}
// }

// strategy: start from node to be removed. arbitrarily choose a subtree (check if it exists first). If the left tree is chosen, 
//				continue swapping the node with the largest of the subtree until you hit the bottom. If the right tree is chosen,
//				do the same but with the smallest of the subtree. This is because the only values that retain ordering if they're
//				swapped with the root are the largest of the left subtree or the smallest of the right subtree.
// template<typename T>
// bool MySearchTree<T>::remove(T value) 
// {

// 	if (!contains(value))
// 	{
// 		return false;
// 	}

// 	std::unique_ptr<MySearchTree<T>::Node>* toRemove = find(value);

// 	// if the node doesn't have children, we can safely remove it 
// 	if ( !hasChildren(toRemove) )
// 	{
// 		toRemove->reset();
// 		return true;
// 	}
// 	// to keep the tree balanced, we'll choose a random subtree and replace the node to be removed with
// 	//	 the optimal value from it
// 	else if ( ((*toRemove)->hasL()) && ((*toRemove)->hasR()) )
// 	{
// 		if (rand() % 2 == 0) // go left and swap with the largest value
// 		{
// 			// first check if this node has both children. if it doesn't, the smallest/largest code may not work 
// 			//    correctly. If you want the smallest of the right tree and move right before calling smallest()
// 			//    you're finding the smallest node of the right child, not the smallest of the node to be removed
// 			if ( !(*toRemove)->getL()->hasR() )
// 			{
// 				// manually swap
// 				auto toSwap = &(*toRemove)->getL();
// 				swap( *toRemove, *toSwap);
// 				toRemove = toSwap;
// 			}
// 			else // the code will work normally in this case
// 			{
// 				auto toSwap = largest(&(*toRemove)->getL());
// 				swap( *toRemove, *toSwap );
// 				toRemove = toSwap;				
// 			}

// 			// if toRemove still has children, we can't remove it, so we continue swapping it out until it meets
// 			//   this criterion 
// 			while (hasChildren(toRemove))
// 			{
// 				auto toSwap = largest(toRemove);
// 				swap(*toRemove, *toSwap);
// 				toRemove = toSwap;
// 			}
// 			// since current is now a node without children, we can safely remove it
// 			toRemove->reset();
// 			return true;
// 		}
// 		else // go right and swap with the smallest value
// 		{
// 			// first check if this node has both children. if it doesn't, the smallest/largest code may not work 
// 			//    correctly. If you want the smallest of the right tree and move right before calling smallest()
// 			//    you're finding the smallest node of the right child, not the smallest of the node to be removed
// 			if ( !(*toRemove)->getR()->hasL() )
// 			{
// 				// manually swap
// 				auto toSwap = &(*toRemove)->getR();
// 				swap( *toRemove, *toSwap);
// 				toRemove = toSwap;
// 			}
// 			else // the code will work normally in this case
// 			{
// 				auto toSwap = smallest(&(*toRemove)->getR());
// 				swap( *toRemove, *toSwap );
// 				toRemove = toSwap;				
// 			}

// 			// if toRemove still has children, we can't remove it, so we continue swapping it out until it meets
// 			//   this criterion 
// 			while (hasChildren(toRemove))
// 			{
// 				auto toSwap = smallest(toRemove);
// 				swap(*toRemove, *toSwap);
// 				toRemove = toSwap;
// 			}
// 			// since current is now a node without children, we can safely remove it
// 			toRemove->reset();
// 			return true;
// 		}
// 	}
// 	// if we don't have a left subtree, we'll go right
// 	else if (!(*toRemove)->hasL())
// 	{
// 		// first check if this node has both children. if it doesn't, the smallest/largest code may not work 
// 		//    correctly. If you want the smallest of the right tree and move right before calling smallest()
// 		//    you're finding the smallest node of the right child, not the smallest of the node to be removed
// 		if ( !(*toRemove)->getR()->hasL() )
// 		{
// 			// manually swap
// 			auto toSwap = &(*toRemove)->getR();
// 			swap( *toRemove, *toSwap);
// 			toRemove = toSwap;
// 		}
// 		else // the code will work normally in this case
// 		{
// 			auto toSwap = smallest(&(*toRemove)->getR());
// 			swap( *toRemove, *toSwap );
// 			toRemove = toSwap;				
// 		}

// 		// if toRemove still has children, we can't remove it, so we continue swapping it out until it meets
// 		//   this criterion 
// 		while (hasChildren(toRemove))
// 		{
// 			auto toSwap = smallest(toRemove);
// 			swap(*toRemove, *toSwap);
// 			toRemove = toSwap;
// 		}
// 		// since current is now a node without children, we can safely remove it
// 		toRemove->reset();	
// 		return true;
// 	}
// 	// otherwise go left
// 	else 
// 	{
// 		if ( !(*toRemove)->getL()->hasR() )
// 		{
// 			// manually swap
// 			auto toSwap = &(*toRemove)->getL();
// 			swap( *toRemove, *toSwap);
// 			toRemove = toSwap;
// 		}
// 		else // the code will work normally in this case
// 		{
// 			auto toSwap = largest(&(*toRemove)->getL());
// 			swap( *toRemove, *toSwap );
// 			toRemove = toSwap;				
// 		}

// 		// if toRemove still has children, we can't remove it, so we continue swapping it out until it meets
// 		//   this criterion 
// 		while (hasChildren(toRemove))
// 		{
// 			auto toSwap = largest(toRemove);
// 			swap(*toRemove, *toSwap);
// 			toRemove = toSwap;
// 		}
// 		// since current is now a node without children, we can safely remove it
// 		toRemove->reset();	
// 		return true;
// 	}
// }

// template<typename T>
// void MySearchTree<T>::swap(std::unique_ptr<Node>& a, std::unique_ptr<Node>& b) 	
// {
// 	// std::cout << "\nSwapping vals " << a->getVal() << " " << b->getVal() << "\n";
// 	T temp = a->getVal();
// 	a->setVal(b->getVal());
// 	b->setVal(temp);
// }

// strategy: if it has a right child, keep going right until you hit an empty node. If it only has a left child,
// 				go to the left child. If this left child has a right child, keep going right until you hit an empty
//				node. Otherwise, return this left child. 
// template<typename T>
// std::unique_ptr<typename MySearchTree<T>::Node>* MySearchTree<T>::largest(std::unique_ptr<Node>* current) 
// {
// 	if ( !hasChildren(current) )
// 	{
// 		throw std::invalid_argument( "Cannot find largest child of node without children" );
// 	}

// 	if (current->get()->hasR())
// 	{
// 		while (current->get()->hasR())
// 		{
// 			current = &current->get()->getR();	
// 		}
// 		return current;
// 	}
// 	else
// 	{
// 		current = &current->get()->getL(); // we are now at the left child of the arg
// 		if (current->get()->hasR())
// 		{
// 			while (current->get()->hasR())
// 			{
// 				current = &current->get()->getR();	
// 			}
// 			return current;
// 		}
// 		else
// 		{
// 			return current;
// 		}
// 	}
// }

// // strategy: opposite of largest()
// template<typename T>
// std::unique_ptr<typename MySearchTree<T>::Node>* MySearchTree<T>::smallest(std::unique_ptr<Node>* current) 
// {
// 	if ( !hasChildren(current) )
// 	{
// 		throw std::invalid_argument( "Cannot find largest child of node without children" );
// 	}

// 	if (current->get()->hasL())
// 	{
// 		while (current->get()->hasL())
// 		{
// 			current = &current->get()->getL();	
// 		}
// 		return current;
// 	}
// 	else
// 	{
// 		current = &(*current)->getR(); // we are now at the right child of the arg
// 		if (current->get()->hasL())
// 		{
// 			while (current->get()->hasL())
// 			{
// 				current = &current->get()->getL();	
// 			}
// 			return current;
// 		}
// 		else
// 		{
// 			return current;
// 		}
// 	}
// }

// template<typename T>
// bool MySearchTree<T>::hasChildren(std::unique_ptr<Node>* current)
// {
// 	if ((*current)->hasL())
// 	{
// 		return true;
// 	}
// 	else if ((*current)->hasR())
// 	{
// 		return true;
// 	}
// 	else
// 	{
// 		return false;
// 	}
// }

// template<typename T>
// std::unique_ptr<typename MySearchTree<T>::Node>* MySearchTree<T>::find(T value) 
// {
// 	if (!contains(value))
// 	{
// 		throw std::invalid_argument( "Cannot return unique_ptr to a value the tree does not contain" );
// 	}

// 	std::unique_ptr<MySearchTree<T>::Node>* current = &root;
// 	while (true)
// 	{
// 		if (current->get()->getVal() == value) 
// 		{
// 			return current;
// 		}
// 		else
// 		{
// 			if (value > current->get()->getVal())
// 			{
// 				current = &current->get()->getR();
// 			}
// 			else if (value < current->get()->getVal())
// 			{
// 				current = &current->get()->getL();
// 			}		
// 		}
// 	}	
// }

// template<typename T>
// int MySearchTree<T>::cmp(T val1, T val2) 
// {
// 	if (val1 < val2) 
// 	{
// 		return -1;
// 	}
// 	else if (val1 > val2) 
// 	{
// 		return 1;
// 	}
// 	else 
// 	{
// 		return 0;
// 	}
// }

// template<typename T>
// MySearchTree<T>::Node::Node(T value) 
// {
// 	m_data = value;
// }

// template<typename T>
// T& MySearchTree<T>::Node::getVal() 
// {
// 	return m_data;
// }

// template<typename T>
// void MySearchTree<T>::Node::setVal(T value) 
// {
// 	m_data = value;
// }

// template<typename T>
// bool MySearchTree<T>::Node::hasL() 
// {
// 	return static_cast<bool>(m_left);
// }

// template<typename T>
// bool MySearchTree<T>::Node::hasR() 
// {
// 	return static_cast<bool>(m_right);
// }

// template<typename T>
// std::unique_ptr<typename MySearchTree<T>::Node>& MySearchTree<T>::Node::getL() 
// {
// 	return m_left;
// }

// template<typename T>
// std::unique_ptr<typename MySearchTree<T>::Node>& MySearchTree<T>::Node::getR() 
// {
// 	return m_right;
// }

// template<typename T>
// MySearchTree<T>::Node::~Node() 
// {

// }

// // Template Declarations
// #define DECLARE(type) template class MySearchTree<type>;
// DECLARE(int);