#include <iostream>
#include <map>
#include <string>

class Entity
{
	std::string _mStr;
public:
	Entity(std::string name)
	{
		_mStr = name;;
	}
	std::string& getName() { return _mStr; }
};

bool mycompare(int lhs, int rhs)
{
	return lhs > rhs;
}

void ideaOfMultiMap()
{
	std::multimap<int, Entity*, bool(*)(int,int)> mapVal(mycompare);

	mapVal.insert(std::pair<int, Entity*>(3, new Entity("jhon")));
	mapVal.insert(std::pair<int, Entity*>(1, new Entity("mohan")));
	mapVal.insert(std::pair<int, Entity*>(5, new Entity("ram")));
	mapVal.insert(std::pair<int, Entity*>(5, new Entity("shyam")));
	mapVal.insert(std::pair<int, Entity*>(1, new Entity("242kn")));
	mapVal.insert(std::pair<int, Entity*>(1, new Entity("jsdjbl")));

	//[]operator not defined for multimap as this is not garunties to return single value
	//mapVal[0] = new Entity("pappu");
	//mapVal[5] = new Entity("xxy");

	for (std::map<int, Entity*>::iterator it = mapVal.begin(); it != mapVal.end(); ++it)
	{
		std::cout << it->first << ":" << it->second->getName() << std::endl;
	}

	std::multimap<int, Entity*, bool(*)(int, int)>::iterator it = mapVal.find(1); //will return key to the first and one occurance of the key
	std::cout << "Found element:" << it->first << ":" << it->second->getName() << std::endl;

	mapVal.erase(10); //will not find, won't do anything
	mapVal.erase(5);  //will erase all the entries matching the key values in the multimap
	std::cout << "After erasing elements for key 5:(Total elements " << mapVal.size() << "):" << std::endl;
	for (std::map<int, Entity*>::iterator it = mapVal.begin(); it != mapVal.end(); ++it)
	{
		std::cout << it->first << ":" << it->second->getName() << std::endl;
	}

	std::cout << "Total elements having key 1:" << mapVal.count(1) << std::endl;

	typedef std::multimap<int, Entity*, bool(*)(int, int)> myMap;
	std::pair<myMap::iterator, myMap::iterator> itR = mapVal.equal_range(1); //The function returns a pair, whose member pair::first is the lower bound of the range 
																			 //(the same as lower_bound), and pair::second is the upper bound (the same as upper_bound).
	std::cout << "All elements with key 1:" << std::endl;
	for (myMap::iterator it = itR.first; it != itR.second; ++it)
	{
		std::cout << it->first << ":" << it->second->getName() << std::endl;
	}

	if (!mapVal.empty()) std::cout << "Map is not empty." << std::endl;
	mapVal.clear();
	std::cout << "Current size of the map:" << mapVal.size() << std::endl;
	if (mapVal.empty()) std::cout << "Map is empty." << std::endl;

}