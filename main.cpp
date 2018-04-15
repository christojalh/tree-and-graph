#include "treeandmap.h"
#include "unittests.h"
#include <iostream> 
#include <memory>

int main() 
{
	TreeTests treetest;
	treetest.Run();

	BasicMapTests maptest;
	maptest.Run();

	DistMapTests distmaptest;
	distmaptest.Run();

	return 0; 
}