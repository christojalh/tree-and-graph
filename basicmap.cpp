#include "treeandmap.h"
#include <memory>
#include <queue>
#include <iostream>

template<typename T> 
void MyMap<T>::connect(T objA, T objB)
{
	// if the nodes don't exist yet we want to make them
	if (!isExistingNode(objA)) 
	{
		m_nodes.push_back(std::make_shared<Node>(objA));
	}
	if (!isExistingNode(objB)) 
	{
		m_nodes.push_back(std::make_shared<Node>(objB));
	}

	// if the nodes aren't neighbors yet we want to make them neighbors
	if (isNeighbor(objA,objB))
	{
		// if it's already in our neighbor list, we'll ignore it
	}
	else
	{
		get(objA)->m_neighbors.push_back(get(objB));
	}

	if (isNeighbor(objB,objA))
	{
		// if it's already in our neighbor list, we'll ignore it
	}
	else
	{
		get(objB)->m_neighbors.push_back(get(objA));
	}
}

template<typename T> 
void MyMap<T>::remove(T obj)
{
	// remove all external references to this object 
	for (auto& neighbor : get(obj)->m_neighbors)
	{
		for (auto it = get(neighbor->m_data)->m_neighbors.begin(); it != get(neighbor->m_data)->m_neighbors.end(); ++it)
		{
			if ((*it)->m_data == obj)
			{
				get(neighbor->m_data)->m_neighbors.erase(it);
				break;
			}
		}
	}
	// delete obj
	for (auto i = m_nodes.begin(); i != m_nodes.end(); ++i)
	{
		if ((*i)->m_data == obj)
		{
			m_nodes.erase(i);
			break;
		}
	}
}

// returns -1 if objects don't exist and -2 if the objects are in separate groups. Otherwise returns shortest distance
template<typename T> 
int MyMap<T>::shortestDistance(T objA, T objB)
{
	if (!isExistingNode(objA) || !isExistingNode(objB))
	{
		return -1;
	}

	if (objA == objB) 
	{
		return 0;
	}

	int shortest = -2;
	int path = 1;
	if (isNeighbor(objA, objB))
	{
		shortest = 1;
		return shortest;
	}
	std::vector<PastNode> previous;
	// std::map<T, int> previous; // keeps track of previous nodes and neighbors of nodes
	addPrevious(objA, previous);
	for (auto& neighbor : get(objA)->m_neighbors)
	{
		addPrevious(neighbor->m_data, previous);
		++path;
		findPath(neighbor->m_data, objB, shortest, path, previous);
		--path;
		delPrevious(neighbor->m_data, previous);
	}
	return shortest;
}



template<typename T> 
void MyMap<T>::findPath(T current, T dest, int& shortest, int& path, std::vector<PastNode>& previous)
{
	// Base case 1: Current path is >= the the shortest path we've found thus far
	// Base case 2: No neighbors except for places we've already been. If we run into a node we've been to previously
	// 				or any of its neighbors, the shorter path to that place is to go from the previous node. 
	//				Therefore it's redundant to continue and we should return.
	if ((path >= shortest) && (shortest > 0))
	{
		return;
	}

	int numPrevious = 0;
	for (auto& neighbor : get(current)->m_neighbors)
	{
		if (!isPrevious(neighbor->m_data, previous))
		{
			break;
		}
		else
		{
			++numPrevious;
		}
	}
	if (numPrevious == get(current)->m_neighbors.size())	
	{
		return;
	}

	for (auto& neighbor : get(current)->m_neighbors)
	{
		if (neighbor->m_data == dest) // found a path
		{
			if (shortest < 0)
			{
				shortest = path;
				break; // we can stop looking at this node and beyond it, since no neighbors will have a shorter distance to the dest
				// NOTE: this is not the case in DistMap
			}
			else if (path < shortest)
			{
				shortest = path;
				break;
			}
		}
		else if (isPrevious(neighbor->m_data, previous))
		{
			continue;
		}
		else
		{
			addPrevious(neighbor->m_data, previous);
			++path;
			findPath(neighbor->m_data, dest, shortest, path, previous);
			--path;
			delPrevious(neighbor->m_data, previous);
		}
	}
}

// increment the number of times we've seen this object
template<typename T> 
void MyMap<T>::addPrevious(T obj, std::vector<PastNode>& previous)
{
	if (isPrevious(obj, previous))
	{
		auto pastNodeIt = getPreviousIt(obj, previous);
		(*pastNodeIt).m_timesEncountered = (*pastNodeIt).m_timesEncountered + 1;
	}
	else
	{
		T* dataPtr = &get(obj)->m_data;
		previous.push_back(PastNode(dataPtr));
	}
}

// decrement the number of times we've seen this object, or delete it from 'previous' if the number hits 0
template<typename T> 
void MyMap<T>::delPrevious(T obj, std::vector<PastNode>& previous)
{
	if (!isPrevious(obj, previous))
	{
		return; // it's already not there
	}

	else
	{
		auto pastNodeIt = getPreviousIt(obj, previous);
		(*pastNodeIt).m_timesEncountered = (*pastNodeIt).m_timesEncountered - 1;

		if ((*pastNodeIt).m_timesEncountered == 0)
		{
			previous.erase(pastNodeIt);
		}
	}
}

template<typename T> 
bool MyMap<T>::isPrevious(T obj, std::vector<PastNode>& previous)
{
	for (auto& node : previous)
	{
		if (*(node.m_data) == obj)
		{
			return true;
		}
	}
	return false;
}

template<typename T> 
auto MyMap<T>::getPreviousIt(T obj, std::vector<PastNode>& previous)
{
	if (!isPrevious(obj, previous))
	{
		throw std::invalid_argument("Can't return nonexistent object");
	}

	for (auto it = previous.begin(); it != previous.end(); ++it)
	{
		if (*((*it).m_data) == obj)
		{
			return it;
		}
	}
}

template<typename T> 
bool MyMap<T>::isNeighbor(T current, T neighbor)
{
	for (auto& it : get(current)->m_neighbors)
	{
		if (it->m_data == neighbor)
		{
			return true;
		}
	}
	return false; 
}

template<typename T> 
bool MyMap<T>::isExistingNode(T obj)
{
	for (auto& it : m_nodes)
	{
		if (it->m_data == obj)
		{
			return true;
		}
	}
	return false;	
}

template<typename T> 
std::shared_ptr<typename MyMap<T>::Node>& MyMap<T>::get(T obj)
{
	for (auto& it : m_nodes)
	{
		if (it->m_data == obj)
		{
			return it;
		}
	}

	throw std::invalid_argument("Can't return nonexistent object");

}

template<typename T>
MyMap<T>::Node::Node(T data)
{
	m_data = data;
}

template<typename T>
MyMap<T>::PastNode::PastNode(T* data)
{
	m_data = data;
	++m_timesEncountered;
}

// Template Declarations
#define DECLARE(type) template class MyMap<type>;
DECLARE(int);