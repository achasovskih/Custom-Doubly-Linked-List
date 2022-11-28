#include "ListRand.h"
#include <fstream>
#include <iostream>
#include <string>

using namespace SaberInteractive_Test;

int main()
{
	srand(time(NULL));

	ListRand list;

	std::cout << "Creating list" << std::endl;

	for (size_t i = 0; i < 100000; i++)
	{
		list.push_back("data_" + std::to_string(i));
	}

	std::ofstream fout;
	std::ifstream fin;

	list.Serialize(fout);

	list.clear();

	list.Deserialize(fin);

	return 0;
}
