// how do i make this work with arrays? The problem is to make m_data an array
// I need to make m_data a pointer. However, if I want to store an int in there
// i'd have to make m_data a pointer to an int, but oftentimes the input will be
// a literal, which cannot have a pointer 
//		for now let's just make it work with literals

// can i use a const ref for both an array and a literal? 
#include <memory>
#ifndef TREEANDMAP
#define TREEANDMAP

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
		bool hasL();
		bool hasR();
		std::unique_ptr<Node>& getL();
		std::unique_ptr<Node>& getR();		

	private:
		T m_data;
		std::unique_ptr<Node> m_left;
		std::unique_ptr<Node> m_right;
	};

public: 
	MySearchTree(T value);
	~MySearchTree();
	void insert(T value);
	void remove(T value);
	bool contains(T value);
	std::unique_ptr<Node>* largest(std::unique_ptr<Node>* current); 
	std::unique_ptr<Node>* smallest(std::unique_ptr<Node>* current); 
	std::unique_ptr<Node>* find(T value); 
	bool hasChildren(std::unique_ptr<Node>* current);
	MySearchTree::Node* getRoot();
	void swap(std::unique_ptr<Node>& a, std::unique_ptr<Node>& b); 	

private:
	std::unique_ptr<Node> root;
};

#endif