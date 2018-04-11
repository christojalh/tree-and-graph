#include "treeandmap.h"
#include <map>

#ifndef UNITTESTS
#define UNITTESTS

// void verifyChildChecking();
// void verifyInsertMultiple();

class TreeTests
{
	public:
	  void Run();

	private:
	  static bool insertMany();
	  static bool deleteMany();
	  static bool singleElementTest();
	  std::map<std::string, bool> m_results;
};

class BasicMapTests
{
public: 
	void Run();

private:
	bool threeNodeTest(); 
	bool twoUnlinkedGroupsTest();
	bool twoPathsTest();
	bool intersectionTest();
	std::map<std::string, bool> m_results;
};

#endif