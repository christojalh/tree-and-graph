#include "treeandgraph.h"
#include "unittests.h"
#include <iostream>

void DistGraphTests::Run()
{		  
    m_results["threeNodeTest:\t"] = threeNodeTest();
    m_results["twoUnlinkedGroupsTest:"] = twoUnlinkedGroupsTest();
    m_results["twoPathsTest:\t"] = twoPathsTest();
    m_results["intersectionTest:"] = intersectionTest();
    m_results["sequentialRemoval:"] = sequentialRemoval();

    std::cout << "Running DistGraph tests...\n";
    for (auto& it : m_results)
    {
      std::cout << it.first << "\t" << (it.second ? "PASSED" : "\033[1;31mFAILED\033[0m") << std::endl;
    }	  
    std::cout << "\n";
}

bool DistGraphTests::threeNodeTest() 
{
	MyDistGraph<int> graph;
	graph.connect(1, 2, 10);
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

	if (graph.shortestDistance(1, 2) == 10) 
	{
		// ok; continue testing
	}
	else
	{
		return false;
	}	

	graph.connect(2, 3, 10);
	if (graph.shortestDistance(1, 3) == 20) 
	{
		// ok; continue testing
	}
	else
	{
		// std::cout << graph.shortestDistance(1, 3) << "\n";
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

bool DistGraphTests::twoUnlinkedGroupsTest()
{
	MyDistGraph<int> graph;
	graph.connect(1, 2, 5);
	graph.connect(3, 4, 5);
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
bool DistGraphTests::twoPathsTest()
{
	MyDistGraph<int> graph;
	graph.connect(0, 1, 10);
	graph.connect(1, 2, 10);

	if (graph.shortestDistance(0, 2) == 20)
	{
		// ok; continue testing
	}
	else
	{
		return false;
	}

	graph.connect(0, 11, 5);
	graph.connect(11, 12, 5);
	graph.connect(12, 2, 5);

	if (graph.shortestDistance(0, 2) == 15)
	{
		// ok; continue testing
	}
	else
	{
		return false;
	}

	graph.remove(12);
	if (graph.shortestDistance(0, 2) == 20)
	{
		// ok; continue testing
	}
	else
	{
		return false;
	}

	return true;
}

// two diamonds stacked on top of each other
bool DistGraphTests::intersectionTest()
{
	MyDistGraph<int> graph;
	graph.connect(0, 11, 5);
	graph.connect(11, 2, 5);
	graph.connect(2, 3, 5);
	graph.connect(3, 4, 5);
	graph.connect(0, 1, 10);
	graph.connect(1, 2, 10);
	graph.connect(2, 13, 10);
	graph.connect(13, 4, 10);

	if (graph.shortestDistance(0, 4) == 20)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool DistGraphTests::sequentialRemoval()
{
	MyDistGraph<int> graph;
	graph.connect(0, 1, 1);
	graph.connect(1, 100, 10);

	graph.connect(0, 21, 2);
	graph.connect(21, 100, 10);

	graph.connect(0, 31, 3);
	graph.connect(31, 100, 10);

	if (graph.shortestDistance(0, 100) == 11)
	{
		// ok; continue testing
	}
	else
	{
		return false;
	}

	graph.remove(1);
	if (graph.shortestDistance(0, 100) == 12)
	{
		// ok; continue testing
	}
	else
	{
		return false;
	}

	graph.remove(21);
	if (graph.shortestDistance(0, 100) == 13)
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