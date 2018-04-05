#include <cstdlib>
#include "treeandmap.h"
#include <iostream>
#include <memory>
#include <stdexcept>

// template<typename T> 
// using Node_t = typename MySearchTree<T>::Node;
/*  TODO
write insert()
write contains() to search through the tree
test contains() after you insert a node
write remove()
test contains() after you remove a node

    7
  7  11


*/



// if you want to call a constructor for the initialization of member variables
// you have to do it in a member-initialization list

// you have to dynamically allocate the variable the smart pointer is 
// managing because the smart pointer calls a delete when it goes out 
// of scope 
template<typename T>
MySearchTree<T>::MySearchTree(T value): root(new Node(value))
{
	// our only step here is to initialize the root 
}

template<typename T>
MySearchTree<T>::~MySearchTree() 
{
	// remove() all nodes. it will have at most H deletes on the stack 
	// where H is the height of the tree 
	// remove(root); 
}

template<typename T>
typename MySearchTree<T>::Node* MySearchTree<T>::getRoot() 
{
	return root.get();
}

// strategy: start from top, follow the tree down until an empty node is found. 
// Create the new node. Make the parent node's L/R variable point to the new node. 
// notes: assuming we're looking for a value, it's okay if multiple of the same value are in random places.
//			as long as the first one is in place, we know that the tree contains it. However, if we want to sort
//			the tree, this might become a problem.........
template<typename T>
void MySearchTree<T>::insert(T value) 
{
	Node* current = root.get();

	// we'll continue traversing the tree until a spot is found for the node
	while (true)
	{
		if (value == current->getVal())
		{
			// if the value matches the current node, we'll randomly assign it L/R to keep the tree
			//   balanced 
			if (rand() % 2 == 0)
			{
				if (current->hasL()) 
				{
					// a child is found, so we travel to it to check if it can hold a new node
					current = current->getL().get();
				}
				else
				{
					// a spot is found for the node, so we initialize it and break out of the loop
					current->getL() = std::make_unique<Node>(value);
					break;
				}
			}
			else
			{
				if (current->hasR()) 
				{
					// a child is found, so we travel to it to check if it can hold a new node
					current = current->getR().get();
				}
				else
				{
					current->getR() = std::make_unique<Node>(value);
					break;	
				}			
			}
		}

		if (value > current->getVal())
		{

			if (current->hasR()) 
			{
				// a child is found, so we travel to it to check if it can hold a new node
				current = current->getR().get();
			}
			else
			{
				// a spot is found for the node, so we initialize it and break out of the loop
				current->getR() = std::make_unique<Node>(value);
				break;
			}
		}

		else if (value < current->getVal())
		{
			if (current->hasL()) 
			{
				// a child is found, so we travel to it to check if it can hold a new node
				current = current->getL().get();
			}
			else
			{
				// a spot is found for the node, so we initialize it and break out of the loop
				current->getL() = std::make_unique<Node>(value);
				break;
			}
		}	
	}
}


template<typename T>
bool MySearchTree<T>::contains(T value) 
{
	Node* current = root.get();

	// we'll keep traversing the tree until we find the value or an empty node
	while (true)
	{
		if (current->getVal() == value) 
		{
			return true;
		}
		else
		{
			if (value > current->getVal())
			{
				if (current->hasR()) 
				{
					// a child is found, so we travel to it to continue our traversal
					current = current->getR().get();
				}
				else
				{
					// an empty node is found, signifying the tree doesn't contain the value
					return false;
				}
			}

			else if (value < current->getVal())
			{
				if (current->hasL()) 
				{
					// a child is found, so we travel to it to continue our traversal
					current = current->getL().get();
				}
				else
				{
					// an empty node is found, signifying the tree doesn't contain the value
					return false;
				}
			}		
		}
	}
}

// strategy: start from node to be removed. arbitrarily choose a subtree (check if it exists first). If the left tree is chosen, 
//				continue swapping the node with the largest of the subtree until you hit the bottom. If the right tree is chosen,
//				do the same but with the smallest of the subtree. This is because the only values that retain ordering if they're
//				swapped with the root are the largest of the left subtree or the smallest of the right subtree.
template<typename T>
void MySearchTree<T>::remove(T value) 
{
	// we'll do nothing if the value is not in our tree
	if (!contains(value))
	{
		return;
	}

	std::unique_ptr<MySearchTree<T>::Node>* toRemove = find(value);

	// if the node doesn't have children, we can safely remove it 
	if ( !hasChildren(toRemove) )
	{
		toRemove->reset();
	}
	// to keep the tree balanced, we'll choose a random subtree and replace the node to be removed with
	//	 the optimal value from it
	else if ( (toRemove->get()->hasL()) && (toRemove->get()->hasR()) )
	{
		if (rand() % 2 == 0) // go left and swap with the largest value
		{
			swap( *toRemove, *largest(&toRemove->get()->getL()) );
			while (hasChildren(toRemove))
			{
				swap(*toRemove, *largest(toRemove));
			}
			// since current is now a node without children, we can safely remove it
			toRemove->reset();
		}
		else // go right and swap with the smallest value
		{
			swap( *toRemove, *smallest(&toRemove->get()->getR()) );
			while (hasChildren(toRemove))
			{
				swap(*toRemove, *smallest(toRemove));
			}
			// since current is now a node without children, we can safely remove it
			toRemove->reset();
		}
	}
	// if we don't have a left subtree, we'll go right
	else if (!toRemove->get()->hasL())
	{
		swap( *toRemove, *smallest(&toRemove->get()->getR()) );
		while (hasChildren(toRemove))
		{
			swap(*toRemove, *smallest(toRemove));
		}
		// since current is now a node without children, we can safely remove it
		toRemove->reset();		
	}
	// otherwise go left
	else 
	{
		swap( *toRemove, *largest(&toRemove->get()->getL()) );
		while (hasChildren(toRemove))
		{
			swap(*toRemove, *largest(toRemove));
		}
		// since current is now a node without children, we can safely remove it
		toRemove->reset();		
	}
}

// for some reason i can enter an arg without "typename" but not the return value. why?
template<typename T>
void MySearchTree<T>::swap(std::unique_ptr<Node>& a, std::unique_ptr<Node>& b) 	
{
	std::unique_ptr<Node> temp = std::move(a);
	a = std::move(b);
	b = std::move(temp);
}

// strategy: if it has a right child, keep going right until you hit an empty node. If it only has a left child,
// 				go to the left child. If this left child has a right child, keep going right until you hit an empty
//				node. Otherwise, return this left child. 
template<typename T>
std::unique_ptr<typename MySearchTree<T>::Node>* MySearchTree<T>::largest(std::unique_ptr<Node>* current) 
{
	if ( !hasChildren(current) )
	{
		throw std::invalid_argument( "Cannot find largest child of node without children" );
	}

	if (current->get()->hasR())
	{
		while (current->get()->hasR())
		{
			current = &current->get()->getR();	
		}
		return current;
	}
	else
	{
		current = &current->get()->getL(); // we are now at the left child of the arg
		if (current->get()->hasR())
		{
			while (current->get()->hasR())
			{
				current = &current->get()->getR();	
			}
			return current;
		}
		else
		{
			return current;
		}
	}
}

// strategy: opposite of largest()
template<typename T>
std::unique_ptr<typename MySearchTree<T>::Node>* MySearchTree<T>::smallest(std::unique_ptr<Node>* current) 
{
	if ( !hasChildren(current) )
	{
		throw std::invalid_argument( "Cannot find largest child of node without children" );
	}

	if (current->get()->hasL())
	{
		while (current->get()->hasL())
		{
			current = &current->get()->getL();	
		}
		return current;
	}
	else
	{
		current = &current->get()->getR(); // we are now at the right child of the arg
		if (current->get()->hasL())
		{
			while (current->get()->hasL())
			{
				current = &current->get()->getL();	
			}
			return current;
		}
		else
		{
			return current;
		}
	}
}

template<typename T>
bool MySearchTree<T>::hasChildren(std::unique_ptr<Node>* current)
{
	if (current->get()->hasL())
	{
		return false;
	}
	else if (current->get()->hasR())
	{
		return false;
	}
	else
	{
		return true;
	}
}

template<typename T>
std::unique_ptr<typename MySearchTree<T>::Node>* MySearchTree<T>::find(T value) 
{
	if (!contains(value))
	{
		throw std::invalid_argument( "Cannot return unique_ptr to a value the tree does not contain" );
	}

	std::unique_ptr<MySearchTree<T>::Node>* current = &root;
	while (true)
	{
		if (current->get()->getVal() == value) 
		{
			return current;
		}
		else
		{
			if (value > current->get()->getVal())
			{
				current = &current->get()->getR();
			}
			else if (value < current->get()->getVal())
			{
				current = &current->get()->getL();
			}		
		}
	}	
}

template<typename T>
MySearchTree<T>::Node::Node(T value) 
{
	m_data = value;
}

template<typename T>
T MySearchTree<T>::Node::getVal() 
{
	return m_data;
}

template<typename T>
bool MySearchTree<T>::Node::hasL() 
{
	return static_cast<bool>(m_left);
}

template<typename T>
bool MySearchTree<T>::Node::hasR() 
{
	return static_cast<bool>(m_right);
}

template<typename T>
std::unique_ptr<typename MySearchTree<T>::Node>& MySearchTree<T>::Node::getL() 
{
	return m_left;
}

template<typename T>
std::unique_ptr<typename MySearchTree<T>::Node>& MySearchTree<T>::Node::getR() 
{
	return m_right;
}

template<typename T>
MySearchTree<T>::Node::~Node() 
{

}

// Template Declarations
#define DECLARE(type) template class MySearchTree<type>;
DECLARE(int);