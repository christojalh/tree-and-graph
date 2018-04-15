#include "treeandmap.h"
#include "unittests.h"
#include <iostream>

void BasicMapTests::Run()
{		  
    m_results["threeNodeTest:\t"] = threeNodeTest();
    m_results["twoUnlinkedGroupsTest:"] = twoUnlinkedGroupsTest();
    m_results["twoPathsTest:\t"] = twoPathsTest();
    m_results["intersectionTest:"] = intersectionTest();
    m_results["sequentialRemoval:"] = sequentialRemoval();

    std::cout << "Running BasicMap tests...\n";
    for (auto& it : m_results)
    {
      std::cout << it.first << "\t" << (it.second ? "PASSED" : "\033[1;31mFAILED\033[0m") << std::endl;
    }	  
    std::cout << "\n";
}

bool BasicMapTests::threeNodeTest() 
{
	MyMap<int> map;
	map.connect(1, 2);
	if (map.shortestDistance(1, 1) == 0) 
	{
		// ok; continue testing
	}
	else
	{
		return false;
	}

	if (map.shortestDistance(1, 3) == -1) 
	{
		// ok; continue testing
	}
	else
	{
		return false;
	}

	if (map.shortestDistance(1, 2) == 1) 
	{
		// ok; continue testing
	}
	else
	{
		return false;
	}	

	map.connect(2, 3);
	if (map.shortestDistance(1, 3) == 2) 
	{
		// ok; continue testing
	}
	else
	{
		return false;
	}

	map.connect(1, 3);
	if (map.shortestDistance(1, 3) == 1) 
	{
		// ok; continue testing
	}
	else
	{
		return false;
	}	

	map.remove(3);
	if (map.shortestDistance(1, 3) == -1) // since this node doesn't exist, it returns -1
	{
		// ok; continue testing
	}
	else
	{
		return false;
	}		

	return true;
}

bool BasicMapTests::twoUnlinkedGroupsTest()
{
	MyMap<int> map;
	map.connect(1, 2);
	map.connect(3, 4);
	if (map.shortestDistance(1, 3) == -2) 
	{
		return true;
	}
	else
	{
		return false;
	}	
}

// looks like a rectangle
bool BasicMapTests::twoPathsTest()
{
	MyMap<int> map;
	map.connect(0, 1);
	map.connect(1, 2);
	map.connect(0, 11);
	map.connect(11, 12);
	map.connect(12, 2);

	if (map.shortestDistance(0, 2) == 2)
	{
		// ok; continue testing
	}
	else
	{
		return false;
	}

	map.remove(1);
	if (map.shortestDistance(0, 2) == 3)
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
bool BasicMapTests::intersectionTest()
{
	MyMap<int> map;
	map.connect(0, 1);
	map.connect(1, 12);
	map.connect(12, 11);
	map.connect(11, 0);
	map.connect(0, 12);
	map.connect(11, 1);
	map.connect(12, 2);

	if (map.shortestDistance(0, 2) == 2)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool BasicMapTests::sequentialRemoval()
{
	MyMap<int> map;
	map.connect(0, 11);
	map.connect(11, 100);

	map.connect(0, 21);
	map.connect(21, 22);
	map.connect(22, 100);

	map.connect(0, 31);
	map.connect(31, 32);
	map.connect(32, 33);
	map.connect(33, 100);

	if (map.shortestDistance(0, 100) == 2)
	{
		// ok; continue testing
	}
	else
	{
		return false;
	}

	map.remove(11);
	if (map.shortestDistance(0, 100) == 3)
	{
		// ok; continue testing
	}
	else
	{
		return false;
	}

	map.remove(21);
	if (map.shortestDistance(0, 100) == 4)
	{
		// ok; continue testing
	}
	else
	{
		return false;
	}

	map.remove(31);
	if (map.shortestDistance(0, 100) == -2)
	{
		// ok; continue testing
	}
	else
	{
		return false;
	}

	return true;
}