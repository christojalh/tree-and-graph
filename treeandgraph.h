#include <memory>
#include <vector>
#include <map>
#include <set>
#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include <functional>

#ifndef TREEANDGRAPH
#define TREEANDGRAPH

template<typename T>
class MyDistGraph
{
public:
    void connect(T objA, T objB, int distance);
    void remove(T obj);
    int shortestDistance(T objA, T objB); // returns -1 if one of the nodes doesn't exist, or -2 if no connection is found 

private:
    struct Node
    {
    	Node(T data, T neighbor, MyDistGraph<T>* graph, int distance);
    	T m_data;
        std::map<T, int> m_neighbors;
        MyDistGraph<T>* m_graph;
    };

    std::map<int,std::shared_ptr<Node>> m_nodes;
    void addPrevious(T obj, int distance, std::map<T, int>& previous);
    bool isPrevious(T obj, std::map<T, int>& previous);
    bool isNeighbor(T objA, T objB);
    bool isExistingNode(T obj);
    void findPath(T current, T dest, int& shortest, int& path, std::map<T, int>& previous);
};

template<typename T>
class MySearchTree 
{
private:
	class Node
	{
	public:
		Node(T value)
        {
            m_data = value;
        }
		~Node()
        {

        }

		T& getVal()
        {
            return m_data;
        }

	private:
		T m_data;
		std::unique_ptr<Node> m_left;
		std::unique_ptr<Node> m_right;

		void setVal(T value)
        {
            m_data = value;
        }
		bool hasL()
        {
            return static_cast<bool>(m_left);
        }
		bool hasR()
        {
            return static_cast<bool>(m_right);
        }
		std::unique_ptr<Node>& getL()
        {
            return m_left;
        }
		std::unique_ptr<Node>& getR()
        {
            return m_right;
        }	
		friend MySearchTree;
	};

public: 
	// MySearchTree(T value, std::function<int(T,T)> comparator): root(new Node(value)), compare(comparator)
    MySearchTree(std::function<int(T,T)> comparator): root(nullptr), compare(comparator)
    {
        // our only step here is to initialize the root 
    }
	~MySearchTree()
    {

    }
	bool insert(T value)
    {
        if (!root.get()) // root uninitialized
        {
            root = std::make_unique<Node>(value);
        }

        Node* current = root.get();

        // we'll continue traversing the tree until a spot is found for the node
        while (true)
        {
            // if (value == current->getVal())
            if (compare(value, current->getVal()) == 0)
            {
                return false;
            }

            // else if (value > current->getVal())
            else if (compare(value, current->getVal()) == 1)
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
                    return true;
                }
            }

            else if (compare(value, current->getVal()) == -1)
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
                    return true;
                }
            }   
        }
    }

	bool remove(T value)
    {

        if (!contains(value))
        {
            return false;
        }

        std::unique_ptr<MySearchTree<T>::Node>* toRemove = find(value);

        // if the node doesn't have children, we can safely remove it 
        if ( !hasChildren(toRemove) )
        {
            toRemove->reset();
            return true;
        }
        // to keep the tree balanced, we'll choose a random subtree and replace the node to be removed with
        //   the optimal value from it
        else if ( ((*toRemove)->hasL()) && ((*toRemove)->hasR()) )
        {
            if (rand() % 2 == 0) // go left and swap with the largest value
            {
                // first check if this node has both children. if it doesn't, the smallest/largest code may not work 
                //    correctly. If you want the smallest of the right tree and move right before calling smallest()
                //    you're finding the smallest node of the right child, not the smallest of the node to be removed
                if ( !(*toRemove)->getL()->hasR() )
                {
                    // manually swap
                    auto toSwap = &(*toRemove)->getL();
                    swap( *toRemove, *toSwap);
                    toRemove = toSwap;
                }
                else // the code will work normally in this case
                {
                    auto toSwap = largest(&(*toRemove)->getL());
                    swap( *toRemove, *toSwap );
                    toRemove = toSwap;              
                }

                // if toRemove still has children, we can't remove it, so we continue swapping it out until it meets
                //   this criterion 
                while (hasChildren(toRemove))
                {
                    auto toSwap = largest(toRemove);
                    swap(*toRemove, *toSwap);
                    toRemove = toSwap;
                }
                // since current is now a node without children, we can safely remove it
                toRemove->reset();
                return true;
            }
            else // go right and swap with the smallest value
            {
                // first check if this node has both children. if it doesn't, the smallest/largest code may not work 
                //    correctly. If you want the smallest of the right tree and move right before calling smallest()
                //    you're finding the smallest node of the right child, not the smallest of the node to be removed
                if ( !(*toRemove)->getR()->hasL() )
                {
                    // manually swap
                    auto toSwap = &(*toRemove)->getR();
                    swap( *toRemove, *toSwap);
                    toRemove = toSwap;
                }
                else // the code will work normally in this case
                {
                    auto toSwap = smallest(&(*toRemove)->getR());
                    swap( *toRemove, *toSwap );
                    toRemove = toSwap;              
                }

                // if toRemove still has children, we can't remove it, so we continue swapping it out until it meets
                //   this criterion 
                while (hasChildren(toRemove))
                {
                    auto toSwap = smallest(toRemove);
                    swap(*toRemove, *toSwap);
                    toRemove = toSwap;
                }
                // since current is now a node without children, we can safely remove it
                toRemove->reset();
                return true;
            }
        }
        // if we don't have a left subtree, we'll go right
        else if (!(*toRemove)->hasL())
        {
            // first check if this node has both children. if it doesn't, the smallest/largest code may not work 
            //    correctly. If you want the smallest of the right tree and move right before calling smallest()
            //    you're finding the smallest node of the right child, not the smallest of the node to be removed
            if ( !(*toRemove)->getR()->hasL() )
            {
                // manually swap
                auto toSwap = &(*toRemove)->getR();
                swap( *toRemove, *toSwap);
                toRemove = toSwap;
            }
            else // the code will work normally in this case
            {
                auto toSwap = smallest(&(*toRemove)->getR());
                swap( *toRemove, *toSwap );
                toRemove = toSwap;              
            }

            // if toRemove still has children, we can't remove it, so we continue swapping it out until it meets
            //   this criterion 
            while (hasChildren(toRemove))
            {
                auto toSwap = smallest(toRemove);
                swap(*toRemove, *toSwap);
                toRemove = toSwap;
            }
            // since current is now a node without children, we can safely remove it
            toRemove->reset();  
            return true;
        }
        // otherwise go left
        else 
        {
            if ( !(*toRemove)->getL()->hasR() )
            {
                // manually swap
                auto toSwap = &(*toRemove)->getL();
                swap( *toRemove, *toSwap);
                toRemove = toSwap;
            }
            else // the code will work normally in this case
            {
                auto toSwap = largest(&(*toRemove)->getL());
                swap( *toRemove, *toSwap );
                toRemove = toSwap;              
            }

            // if toRemove still has children, we can't remove it, so we continue swapping it out until it meets
            //   this criterion 
            while (hasChildren(toRemove))
            {
                auto toSwap = largest(toRemove);
                swap(*toRemove, *toSwap);
                toRemove = toSwap;
            }
            // since current is now a node without children, we can safely remove it
            toRemove->reset();  
            return true;
        }
    }

	bool contains(T value)
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

	int cmp(T val1, T val2)
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

    T& returnVal(T value)
    {
        if (!contains(value))
        {
            throw std::invalid_argument( "Cannot return unique_ptr to a value the tree does not contain" );
        }

        std::unique_ptr<MySearchTree<T>::Node>* current = &root;
        while (true)
        {
            if (compare(current->get()->getVal(), value) == 0) 
            {
                return current->getVal();
            }
            else
            {
                if (compare(value, current->get()->getVal()) == 1) 
                {
                    current = &current->get()->getR();
                }
                else if (compare(value, current->get()->getVal()) == -1)
                {
                    current = &current->get()->getL();
                }       
            }
        }   
    }

	MySearchTree::Node* getRoot()
    {
        return root.get();
    }

private:
	std::unique_ptr<Node> root;
	std::unique_ptr<Node>* largest(std::unique_ptr<Node>* current)
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

	std::unique_ptr<Node>* smallest(std::unique_ptr<Node>* current)
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
            current = &(*current)->getR(); // we are now at the right child of the arg
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

    std::unique_ptr<Node>* find(T value)
    {
        if (!contains(value))
        {
            throw std::invalid_argument( "Cannot return unique_ptr to a value the tree does not contain" );
        }

        std::unique_ptr<MySearchTree<T>::Node>* current = &root;
        while (true)
        {
            if (compare(current->get()->getVal(), value) == 0) 
            {
                return current;
            }
            else
            {
                if (compare(value, current->get()->getVal()) == 1) 
                {
                    current = &current->get()->getR();
                }
                else if (compare(value, current->get()->getVal()) == -1)
                {
                    current = &current->get()->getL();
                }       
            }
        }   
    }


	bool hasChildren(std::unique_ptr<Node>* current)
    {
        if ((*current)->hasL())
        {
            return true;
        }
        else if ((*current)->hasR())
        {
            return true;
        }
        else
        {
            return false;
        }
    }

	void swap(std::unique_ptr<Node>& a, std::unique_ptr<Node>& b)
    {
        T temp = a->getVal();
        a->setVal(b->getVal());
        b->setVal(temp);
    } 

	std::function<int(T,T)> compare;	
};

template<typename T>
class MyGraph
{
public:
    void connect(T objA, T objB);
    void remove(T obj);
    int shortestDistance(T objA, T objB); // returns -1 if one of the nodes doesn't exist, or -2 if no connection is found 

private:
    struct Node
    {
        Node(T data);
        T m_data;
        std::vector<std::shared_ptr<Node>> m_neighbors;
    };

    struct PastNode
    {
        PastNode(T* data);
        T* m_data;
        int m_timesEncountered;
    };

    std::vector<std::shared_ptr<Node>> m_nodes;
    std::shared_ptr<Node>& get(T obj);
    void addPrevious(T obj, std::vector<PastNode>& previous);
    void delPrevious(T obj, std::vector<PastNode>& previous);
    bool isPrevious(T obj, std::vector<PastNode>& previous);
    auto getPreviousIt(T obj, std::vector<PastNode>& previous);
    bool isNeighbor(T objA, T objB);
    bool isExistingNode(T obj);
    void findPath(T current, T dest, int& shortest, int& path, std::vector<PastNode>& previous);

    // TODO make all T into T&, make previous into something else. make a struct PastNode which contains a reference to m_data
    // of another node and a counter for how many we've come across. then make previous a vector<PastNode>
};

#endif