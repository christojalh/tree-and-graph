#include <memory>
#include <vector>
#include <map>
#include <set>
#ifndef TREEANDMAP
#define TREEANDMAP

template<typename T>
class MyDistMap
{
public:
    void connect(T objA, T objB, int distance);
    void remove(T obj);
    int shortestDistance(T objA, T objB); // returns -1 if one of the nodes doesn't exist, or -2 if no connection is found 

private:
    struct Node
    {
    	Node(T data, T neighbor, MyDistMap<T>* map, int distance);
    	T m_data;
        std::map<T, int> m_neighbors;
        MyDistMap<T>* m_map;
    };

    std::map<int,std::shared_ptr<Node>> m_nodes;
    void addPrevious(T obj, int distance, std::map<T, int>& previous);
    bool isPrevious(T obj, std::map<T, int>& previous);
    bool isNeighbor(T objA, T objB);
    bool isExistingNode(T obj);
    void findPath(T current, T dest, int& shortest, int& path, std::map<T, int>& previous);
};

template<typename T>
class MyMap
{
public:
    void connect(T objA, T objB);
    void remove(T obj);
    int shortestDistance(T objA, T objB); // returns -1 if one of the nodes doesn't exist, or -2 if no connection is found 

private:
    struct Node
    {
    	Node(T data, T neighbor, MyMap<T>* map);
    	T m_data;
        std::set<T> m_neighbors;
        MyMap<T>* m_map;
    };

    std::map<int,std::shared_ptr<Node>> m_nodes;
    void addPrevious(T obj, std::map<T, int>& previous);
    void delPrevious(T obj, std::map<T, int>& previous);
    bool isPrevious(T obj, std::map<T, int>& previous);
    bool isNeighbor(T objA, T objB);
    bool isExistingNode(T obj);
    void findPath(T current, T dest, int& shortest, std::vector<T>& path, std::map<T, int>& previous);


};

template<typename T>
class MySearchTree 
{
private:
	class Node
	{
	public:
		Node(T value);
		~Node();

		T getVal();

	private:
		T m_data;
		std::unique_ptr<Node> m_left;
		std::unique_ptr<Node> m_right;

		void setVal(T value);
		bool hasL();
		bool hasR();
		std::unique_ptr<Node>& getL();
		std::unique_ptr<Node>& getR();		
		friend MySearchTree;
	};

public: 
	MySearchTree(T value);
	~MySearchTree();
	bool insert(T value);
	bool remove(T value);
	bool contains(T value);

	MySearchTree::Node* getRoot();

private:
	std::unique_ptr<Node> root;
	std::unique_ptr<Node>* largest(std::unique_ptr<Node>* current); 
	std::unique_ptr<Node>* smallest(std::unique_ptr<Node>* current); 
	std::unique_ptr<Node>* find(T value); 
	bool hasChildren(std::unique_ptr<Node>* current);
	void swap(std::unique_ptr<Node>& a, std::unique_ptr<Node>& b); 	
};

#endif