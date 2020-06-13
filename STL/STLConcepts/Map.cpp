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

void ideaOfMap()
{
	std::map<int, Entity*> mapVal;

	mapVal.insert(std::pair<int, Entity*>(3,new Entity("jhon")));
	mapVal.insert(std::pair<int, Entity*>(1, new Entity("mohan")));
	mapVal.insert(std::pair<int, Entity*>(5, new Entity("ram")));

	mapVal[0] = new Entity("pappu");
	mapVal[5] = new Entity("xxy"); //it will overide the element at [5]

	for (std::map<int, Entity*>::iterator it = mapVal.begin(); it != mapVal.end(); ++it)
	{
		std::cout << it->first << ":" << it->second->getName() << std::endl;
	}

	std::map<int, Entity*>::iterator it = mapVal.find(5);
	if (it != mapVal.end()) {
		std::cout << "Found " << it->first << " " << it->second->getName() << std::endl;
	}
	else {
		std::cout << "Did not find 5." << std::endl;
	}

	struct MyCompare
	{
		bool operator()(const int& lhs, const int& rhs) const
		{
			return lhs < rhs;
		}
	};
	std::map<int, Entity*, MyCompare> mapVar;

	mapVar.insert(std::pair<int, Entity*>(4, new Entity("782")));
	mapVar.insert(std::pair<int, Entity*>(89, new Entity("74e")));
	mapVar.insert(std::pair<int, Entity*>(84, new Entity("75")));
	mapVar.insert(std::pair<int, Entity*>(90, new Entity("7562")));

	for (std::map<int, Entity*>::iterator it = mapVar.begin(); it != mapVar.end(); ++it)
	{
		std::cout << it->first << ":" << it->second->getName() << std::endl;
	}

	//Entity * const & p = mapVar.at(89); //const-pointer to a non-const memory
	Entity *p = mapVar.at(89); // if element exist with this key then return the reference of the mapped value, otherwise throws exception
								//so use it when you are sure or after using find(). Though note that it does not return std::pair or iterator
								//to it, so eases on the use of pair access syntax.
	std::cout << p->getName() << std::endl;

	std::cout << "lower bound for 85:" << (mapVar.lower_bound(85) != mapVar.end() ? mapVar.lower_bound(85)->first : -19092) << std::endl;
	std::cout << "upper bound for 0:" << (mapVar.upper_bound(0) != mapVar.end() ? mapVar.upper_bound(0)->first : -19092) << std::endl;
	std::cout << "lower bound for 0:" << (mapVar.lower_bound(0) != mapVar.end() ? mapVar.lower_bound(0)->first : -19092) << std::endl;

	std::cout << "no of entries of 4:" << mapVar.count(4) << std::endl; //it can only be one in a map
	std::cout << "Size of mapVar :" << mapVar.size() << std::endl;
	std::cout << "Max possible size:" << mapVar.max_size() << std::endl;
	mapVar.erase(89);
	std::cout << "Size of mapVar :" << mapVar.size() << std::endl;
	mapVar.clear();
	std::cout << "Size of mapVar :" << mapVar.size() << std::endl;

	if (mapVar.empty()) std::cout << "Map is empty now." << std::endl;

}