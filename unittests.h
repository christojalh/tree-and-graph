#include "tree.h"
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
	  std::map<std::string, bool> m_results;
};

#endif