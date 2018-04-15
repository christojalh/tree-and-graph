#include "treeandmap.h"
#include <memory>
#include <queue>
#include <iostream>

template<typename T> 
void MyDistMap<T>::connect(T objA, T objB, int distance)
{
    if (!isExistingNode(objA)) 
    {
        m_nodes[objA] = std::make_shared<Node>(objA, objB, this, distance);
    }
    else
    {
        if (isNeighbor(objA,objB))
        {
            // if it's already in our neighbor list, we'll ignore it
        }
        else
        {
            m_nodes[objA]->m_neighbors[objB] = distance;
        }
    }

    if (!isExistingNode(objB)) 
    {
        m_nodes[objB] = std::make_shared<Node>(objB, objA, this, distance);
    }
    else
    {
        if (isNeighbor(objB,objA))
        {
            // if it's already in our neighbor list, we'll ignore it
        }
        else
        {
            m_nodes[objB]->m_neighbors[objA] = distance;
        }
    }
}

template<typename T> 
void MyDistMap<T>::remove(T obj)
{
    // remove all external references to this object 
    for (auto& neighbor : m_nodes[obj]->m_neighbors)
    {
        m_nodes[neighbor.first]->m_neighbors.erase(obj);
    }
    // delete obj
    m_nodes.erase(obj);
}

// returns -1 if objects don't exist and -2 if the objects are in separate groups. Otherwise returns shortest distance
template<typename T> 
int MyDistMap<T>::shortestDistance(T objA, T objB)
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
    int path = 0;
    std::map<T, int> previous; // keeps track of known distances from objA to all nodes 

// each time you run shortestdistance() make a new variable that keeps track of the shortest distance to each
// node we run into. If the next node we're traveling to has a shorter recorded distance than we've previously seen, 
// record the new shortest distance and continue on. Otherwise, if it's longer, ignore this path

    addPrevious(objA, path, previous);
    for (auto& neighbor : m_nodes[objA]->m_neighbors)
    {
        path += neighbor.second;
        findPath(neighbor.first, objB, shortest, path, previous);
        path -= neighbor.second;
    }
    return shortest;
}



template<typename T> 
void MyDistMap<T>::findPath(T current, T dest, int& shortest, int& path, std::map<T, int>& previous)
{
    // Base case 1: Current path is >= the the shortest path we've found thus far to this node or to the destination
    // Base case 2: No neighbors left to look through 
    // Base case 3: Found our destination (dest)


    if ((path >= shortest) && (shortest > 0))
    {
        // std::cout << "return status 1" << "\n";
        return;
    }

    if (isPrevious(current, previous))
    {
        if (path >= previous[current])
        {
        // std::cout << "return status 2" << "\n";
        // std::cout << "this node is " << current << "\n";
            return;
        }
    }
    addPrevious(current, path, previous); // record this path

    if (current == dest)
    {
        if (shortest < 0)
        {
            shortest = path;
        // std::cout << "return status 3" << "\n";
            return;
        }
        else if (path < shortest)
        {
            shortest = path;
        // std::cout << "return status 4" << "\n";
            return;
        }
    }

    for (auto& neighbor : m_nodes[current]->m_neighbors)
    {
        if (neighbor.first == dest) // found a path
        {
            path += neighbor.second;
            if (shortest < 0)
            {
                shortest = path;
            }
            else if (path < shortest)
            {
                shortest = path;
                // Note: we can't break here, since other neighbors could still have a shorter path to the dest
            }
            path -= neighbor.second;
        }
        else
        {
            path += neighbor.second;
            findPath(neighbor.first, dest, shortest, path, previous);
            path -= neighbor.second;
        }
    }
        // std::cout << "return status 5" << "\n";
}

// If the obj isn't already in 'previous', it inserts it. If the obj is in previous, if the new distance
// is shorter, the value is updated. Otherwise it is ignored. 
template<typename T> 
void MyDistMap<T>::addPrevious(T obj, int distance, std::map<T, int>& previous)
{
    if (isPrevious(obj, previous))
    {
        if (distance < previous[obj])
        {
            previous[obj] = distance;
        }
        else
        {
            // ignore longer distance 
        }
    }
    else
    {
        previous[obj] = distance;
    }
}

template<typename T> 
bool MyDistMap<T>::isPrevious(T obj, std::map<T, int>& previous)
{
    return previous.find(obj) != previous.end();
}

template<typename T> 
bool MyDistMap<T>::isNeighbor(T current, T neighbor)
{
    return m_nodes[current]->m_neighbors.find(neighbor) != m_nodes[current]->m_neighbors.end();
}

template<typename T> 
bool MyDistMap<T>::isExistingNode(T obj)
{
    return m_nodes.find(obj) != m_nodes.end(); // if an object is not in a map, find() returns an it to the end
}

template<typename T>
MyDistMap<T>::Node::Node(T data, T neighbor, MyDistMap<T>* map, int distance)
{
    m_data = data;
    m_map = map; 
    m_neighbors[neighbor] = distance;
}

// Template Declarations
#define DECLARE(type) template class MyDistMap<type>;
DECLARE(int);