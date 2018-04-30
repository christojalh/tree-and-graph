#include "treeandgraph.h"
#include "unittests.h"
#include <iostream>

void BasicGraphTests::Run()
{		  
    m_results["threeNodeTest:\t"] = threeNodeTest();
    m_results["twoUnlinkedGroupsTest:"] = twoUnlinkedGroupsTest();
    m_results["twoPathsTest:\t"] = twoPathsTest();
    m_results["intersectionTest:"] = intersectionTest();
    m_results["sequentialRemoval:"] = sequentialRemoval();

    std::cout << "Running BasicGraph tests...\n";
    for (auto& it : m_results)
    {
      std::cout << it.first << "\t" << (it.second ? "PASSED" : "\033[1;31mFAILED\033[0m") << std::endl;
    }	  
    std::cout << "\n";
}

bool BasicGraphTests::threeNodeTest() 
{
	MyGraph<int> graph;
	graph.connect(1, 2);
	if (graph.shortestDistance(1, 1) == 0) 
	{
		// ok; continue testing
	}
	else
	{
		return false;
	}

	if (graph.shortestDistance(1, 3) == -1) 
	{
		// ok; continue testing
	}
	else
	{
		return false;
	}

	if (graph.shortestDistance(1, 2) == 1) 
	{
		// ok; continue testing
	}
	else
	{
		return false;
	}	

	graph.connect(2, 3);
	if (graph.shortestDistance(1, 3) == 2) 
	{
		// ok; continue testing
	}
	else
	{
		return false;
	}

	graph.connect(1, 3);
	if (graph.shortestDistance(1, 3) == 1) 
	{
		// ok; continue testing
	}
	else
	{
		return false;
	}	

	graph.remove(3);
	if (graph.shortestDistance(1, 3) == -1) // since this node doesn't exist, it returns -1
	{
		// ok; continue testing
	}
	else
	{
		return false;
	}		

	return true;
}

bool BasicGraphTests::twoUnlinkedGroupsTest()
{
	MyGraph<int> graph;
	graph.connect(1, 2);
	graph.connect(3, 4);
	if (graph.shortestDistance(1, 3) == -2) 
	{
		return true;
	}
	else
	{
		return false;
	}	
}

// looks like a rectangle
bool BasicGraphTests::twoPathsTest()
{
	MyGraph<int> graph;
	graph.connect(0, 1);
	graph.connect(1, 2);
	graph.connect(0, 11);
	graph.connect(11, 12);
	graph.connect(12, 2);

	if (graph.shortestDistance(0, 2) == 2)
	{
		// ok; continue testing
	}
	else
	{
		return false;
	}

	graph.remove(1);
	if (graph.shortestDistance(0, 2) == 3)
	{
		// ok; continue testing
	}
	else
	{
		return false;
	}

	return true;
}

// this one looks like a square with an X in the middle with the destination sticking out of the corner
bool BasicGraphTests::intersectionTest()
{
	MyGraph<int> graph;
	graph.connect(0, 1);
	graph.connect(1, 12);
	graph.connect(12, 11);
	graph.connect(11, 0);
	graph.connect(0, 12);
	graph.connect(11, 1);
	graph.connect(12, 2);

	if (graph.shortestDistance(0, 2) == 2)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool BasicGraphTests::sequentialRemoval()
{
	MyGraph<int> graph;
	graph.connect(0, 11);
	graph.connect(11, 100);

	graph.connect(0, 21);
	graph.connect(21, 22);
	graph.connect(22, 100);

	graph.connect(0, 31);
	graph.connect(31, 32);
	graph.connect(32, 33);
	graph.connect(33, 100);

	if (graph.shortestDistance(0, 100) == 2)
	{
		// ok; continue testing
	}
	else
	{
		return false;
	}

	graph.remove(11);
	if (graph.shortestDistance(0, 100) == 3)
	{
		// ok; continue testing
	}
	else
	{
		return false;
	}

	graph.remove(21);
	if (graph.shortestDistance(0, 100) == 4)
	{
		// ok; continue testing
	}
	else
	{
		return false;
	}

	graph.remove(31);
	if (graph.shortestDistance(0, 100) == -2)
	{
		// ok; continue testing
	}
	else
	{
		return false;
	}

	return true;
}