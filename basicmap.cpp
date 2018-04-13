#include "treeandmap.h"
#include <memory>
#include <queue>
#include <iostream>

template<typename T> 
void MyMap<T>::connect(T objA, T objB)
{
	if (!isExistingNode(objA)) 
	{
		m_nodes[objA] = std::make_shared<Node>(objA, objB, this);
	}
	else
	{
		if (isNeighbor(objA,objB))
		{
			// if it's already in our neighbor list, we'll ignore it
		}
		else
		{
			m_nodes[objA]->m_neighbors.insert(objB);
		}
	}

	if (!isExistingNode(objB)) 
	{
		m_nodes[objB] = std::make_shared<Node>(objB, objA, this);
	}
	else
	{
		if (isNeighbor(objB,objA))
		{
			// if it's already in our neighbor list, we'll ignore it
		}
		else
		{
			m_nodes[objB]->m_neighbors.insert(objA);
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
	std::vector<T> path; 
	path.push_back(objA);
	if (isNeighbor(objA, objB))
	{
		shortest = 1;
		return shortest;
	}

	std::map<T, int> previous; // keeps track of previous nodes and neighbors of nodes
	addPrevious(objA, previous);
	for (T neighbor : m_nodes[objA]->m_neighbors)
	{
		addPrevious(neighbor, previous);
		path.push_back(neighbor);
		findPath(neighbor, objB, shortest, path, previous);
		path.pop_back();
		delPrevious(neighbor, previous);
	}
	return shortest;
}



template<typename T> 
void MyMap<T>::findPath(T current, T dest, int& shortest, std::vector<T>& path, std::map<T, int>& previous)
{
	// Base case 1: Current path is >= than the the shortest path we've found thus far
	// Base case 2: No neighbors except for places we've already been. If we run into a node we've been to previously
	// 				or any of its neighbors, the shorter path to that place is to go from the previous node. 
	//				Therefore it's redundant to continue and we should return.
	int currentPathDist = path.size();
	if ((currentPathDist >= shortest) && (shortest > 0))
	{
		return;
	}

	int numPrevious = 0;
	for (T neighbor : m_nodes[current]->m_neighbors)
	{
		if (!isPrevious(neighbor, previous))
		{
			break;
		}
		else
		{
			++numPrevious;
		}
	}
	if (numPrevious == m_nodes[current]->m_neighbors.size())	
	{
		return;
	}

	for (T neighbor : m_nodes[current]->m_neighbors)
	{
		if (neighbor == dest) // found a path
		{
			if (shortest < 0)
			{
				shortest = currentPathDist;
				break; // we can stop looking at this node and beyond it, since no neighbors will have a shorter distance to the dest
				// NOTE: this is not the case in DistMap
			}
			else if (currentPathDist < shortest)
			{
				shortest = currentPathDist;
				break;
			}
		}
		else if (isPrevious(neighbor, previous))
		{
			continue;
		}
		else
		{
			addPrevious(neighbor, previous);
			path.push_back(neighbor);
			findPath(neighbor, dest, shortest, path, previous);
			path.pop_back();
			delPrevious(neighbor, previous);
		}
	}
}

// increment the number of times we've seen this object
template<typename T> 
void MyMap<T>::addPrevious(T obj, std::map<T, int>& previous)
{
	if (isPrevious(obj, previous))
	{
		previous[obj] = previous[obj] + 1;
	}
	else
	{
		previous[obj] = 1;
	}
}

// decrement the number of times we've seen this object, or delete it from 'previous' if the number hits 0
template<typename T> 
void MyMap<T>::delPrevious(T obj, std::map<T, int>& previous)
{
	if (!isPrevious(obj, previous))
	{
		return; // it's already not there
	}

	else
	{
		previous[obj] = previous[obj] - 1;

		if (previous[obj] == 0)
		{
			previous.erase(obj);
		}
	}
}

template<typename T> 
bool MyMap<T>::isPrevious(T obj, std::map<T, int>& previous)
{
	return previous.find(obj) != previous.end();
}

template<typename T> 
bool MyMap<T>::isNeighbor(T current, T neighbor)
{
	return m_nodes[current]->m_neighbors.find(neighbor) != m_nodes[current]->m_neighbors.end();
}

template<typename T> 
bool MyMap<T>::isExistingNode(T obj)
{
	return m_nodes.find(obj) != m_nodes.end(); // if an object is not in a map, find() returns an it to the end
}

template<typename T>
MyMap<T>::Node::Node(T data, T neighbor, MyMap<T>* map)
{
	m_data = data;
	m_map = map; 
	m_neighbors.insert(neighbor);
}

// Template Declarations
#define DECLARE(type) template class MyMap<type>;
DECLARE(int);