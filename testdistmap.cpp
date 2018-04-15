#include "treeandmap.h"
#include "unittests.h"
#include <iostream>

void DistMapTests::Run()
{		  
    m_results["threeNodeTest:\t"] = threeNodeTest();
    m_results["twoUnlinkedGroupsTest:"] = twoUnlinkedGroupsTest();
    m_results["twoPathsTest:\t"] = twoPathsTest();
    m_results["intersectionTest:"] = intersectionTest();
    m_results["sequentialRemoval:"] = sequentialRemoval();

    std::cout << "Running DistMap tests...\n";
    for (auto& it : m_results)
    {
      std::cout << it.first << "\t" << (it.second ? "PASSED" : "\033[1;31mFAILED\033[0m") << std::endl;
    }	  
    std::cout << "\n";
}

bool DistMapTests::threeNodeTest() 
{
	MyDistMap<int> map;
	map.connect(1, 2, 10);
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

	if (map.shortestDistance(1, 2) == 10) 
	{
		// ok; continue testing
	}
	else
	{
		return false;
	}	

	map.connect(2, 3, 10);
	if (map.shortestDistance(1, 3) == 20) 
	{
		// ok; continue testing
	}
	else
	{
		// std::cout << map.shortestDistance(1, 3) << "\n";
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

bool DistMapTests::twoUnlinkedGroupsTest()
{
	MyDistMap<int> map;
	map.connect(1, 2, 5);
	map.connect(3, 4, 5);
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
bool DistMapTests::twoPathsTest()
{
	MyDistMap<int> map;
	map.connect(0, 1, 10);
	map.connect(1, 2, 10);

	if (map.shortestDistance(0, 2) == 20)
	{
		// ok; continue testing
	}
	else
	{
		return false;
	}

	map.connect(0, 11, 5);
	map.connect(11, 12, 5);
	map.connect(12, 2, 5);

	if (map.shortestDistance(0, 2) == 15)
	{
		// ok; continue testing
	}
	else
	{
		return false;
	}

	map.remove(12);
	if (map.shortestDistance(0, 2) == 20)
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
bool DistMapTests::intersectionTest()
{
	MyDistMap<int> map;
	map.connect(0, 11, 5);
	map.connect(11, 2, 5);
	map.connect(2, 3, 5);
	map.connect(3, 4, 5);
	map.connect(0, 1, 10);
	map.connect(1, 2, 10);
	map.connect(2, 13, 10);
	map.connect(13, 4, 10);

	if (map.shortestDistance(0, 4) == 20)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool DistMapTests::sequentialRemoval()
{
	MyDistMap<int> map;
	map.connect(0, 1, 1);
	map.connect(1, 100, 10);

	map.connect(0, 21, 2);
	map.connect(21, 100, 10);

	map.connect(0, 31, 3);
	map.connect(31, 100, 10);

	if (map.shortestDistance(0, 100) == 11)
	{
		// ok; continue testing
	}
	else
	{
		return false;
	}

	map.remove(1);
	if (map.shortestDistance(0, 100) == 12)
	{
		// ok; continue testing
	}
	else
	{
		return false;
	}

	map.remove(21);
	if (map.shortestDistance(0, 100) == 13)
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