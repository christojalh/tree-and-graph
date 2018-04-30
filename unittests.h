#ifndef UNITTESTS
#define UNITTESTS

#include "treeandgraph.h"
#include <map>
#include <iostream>
// #include <test_helpers.h>

// class TreeTests final : public UnitTests
// {
// protected:
//     void RunTests() final
//     {
//         ADD_TEST(TreeTests::insertMany);
//         ADD_TEST(TreeTests::deleteMany);
//         ADD_TEST(TreeTests::singleElementTest);
//     }

// private:
// 	static bool insertMany();
// 	static bool deleteMany();
// 	static bool singleElementTest();

//     static Test_Registrar<TreeTests> registrar;
// };

class TreeTests
{
	public:
	  void Run()
	  {
  	    m_results["insertMany:\t"] = insertMany();
	    m_results["deleteMany:\t"] = deleteMany();
	    m_results["singleElementTest:"] = singleElementTest();
	    
	    std::cout << "Running tree tests...\n";
	    for (auto& it : m_results)
	    {
	      std::cout << it.first << "\t" << (it.second ? "PASSED" : "\033[1;31mFAILED\033[0m") << std::endl;
	    }	  
	    std::cout << "\n";
	  }

	private:
	  static bool insertMany();
	  static bool deleteMany();
	  static bool singleElementTest();
	  std::map<std::string, bool> m_results;
};

class BasicGraphTests
{
public: 
	void Run();

private:
	bool threeNodeTest(); 
	bool twoUnlinkedGroupsTest();
	bool twoPathsTest();
	bool intersectionTest();
	bool sequentialRemoval();
	std::map<std::string, bool> m_results;
};

class DistGraphTests
{
public: 
	void Run();

private:
	bool threeNodeTest(); 
	bool twoUnlinkedGroupsTest();
	bool twoPathsTest();
	bool intersectionTest();
	bool sequentialRemoval();
	std::map<std::string, bool> m_results;
};

#endif