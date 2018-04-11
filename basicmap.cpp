#include "treeandmap.h"
#include <memory>
#include <queue>

template<typename T> 
void MyMap<T>::connect(T objA, T objB)
{
	// if the nodes don't already exist, we'll make them
	if (m_nodes.find(objA) == m_nodes.end()) // if an object is not in a map, find() returns an it to the end
	{
		m_nodes[objA] = std::make_shared<Node>(objA, objB, this);
	}
	else
	{
		if (m_nodes[objA]->m_neighbors.find(objB) == m_nodes[objA]->m_neighbors.end())
		{
			// if it's already in our neighbor list, we'll ignore it
		}
		else
		{
			m_nodes[objA]->m_neighbors.insert(objB);
		}
	}

	if (m_nodes.find(objB) == m_nodes.end()) 
	{
		m_nodes[objB] = std::make_shared<Node>(objB, objA, this);
	}
	else
	{
		if (m_nodes[objB]->m_neighbors.find(objA) == m_nodes[objB]->m_neighbors.end())
		{
			// if it's already in our neighbor list, we'll ignore it
		}
		else
		{
			m_nodes[objB]->m_neighbors.insert(objA);
		}
	}

}

template<typename T> 
int MyMap<T>::shortestDistance(T objA, T objB)
{
	// if the objects don't exist, return -1
	if (objA == objB) 
	{
		return 0;
	}
	// first add objA to our path
	// to copy our path later, use std::queue<int> pathcpy (path); aka the copy constructor
	std::queue<int> path; 
	path.push(objA);

	for (int neighbor : m_nodes[objA]->m_neighbors)
	{
		
	}

}

template<typename T>
MyMap<T>::Node::Node(T data, T neighbor, MyMap<T>* map)
{
	m_data = data;
	m_map = map; 
	m_neighbors.insert(neighbor);
}