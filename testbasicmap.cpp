#include "treeandmap.h"
#include "unittests.h"

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

	return true;
}

bool BasicMapTests::twoUnlinkedGroupsTest()
{
	MyMap<int> map;
	map.connect(1, 2);
	map.connect(3, 4);
	if (map.shortestDistance(1, 3) == -1) 
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
		return true;
	}
	else
	{
		return false;
	}
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