#include <memory>
#include <vector>
#include <map>
#include <set>
#ifndef TREEANDMAP
#define TREEANDMAP

template<typename T>
class MyMap
{
public:
	// if you imagine each of these nodes is a unique number, you'll call on the number

    void connect(T objA, T objB);
    // std::queue

    // returns -1 if one of the nodes doesn't exist, or no connection is found 
    int shortestDistance(T objA, T objB);

private:
    struct Node
    {
    	Node(T data, T neighbor, MyMap<T>* map);
    	T m_data;
        std::set<T> m_neighbors;
        MyMap<T>* m_map;
    };

    // void search(int current, );
    std::map<int,std::shared_ptr<Node>> m_nodes;
    bool isNeighbor(T objA, T objB);

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