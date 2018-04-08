#include <memory>
#ifndef TREE
#define TREE

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