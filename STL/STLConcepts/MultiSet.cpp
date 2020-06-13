#include <iostream>
#include <set>
#include <algorithm>

void ideaOfMultiSet()
{
	std::multiset<int> valMSet;

	valMSet.insert(0);
	valMSet.insert(-10);
	valMSet.insert(40);
	valMSet.insert(3);
	valMSet.insert(2);
	valMSet.insert(90);
	valMSet.insert(-10);
	valMSet.insert(40);
	valMSet.insert(3);

	std::cout << "Size of the multiset:" << valMSet.size() << std::endl;

	typedef std::multiset<int>::iterator itr;
	for (itr it = valMSet.begin(); it != valMSet.end(); ++it) {
		std::cout << *it << std::endl;
	}

	int c = valMSet.erase(3);
	std::cout << "Removed " << c << " elements for value 3." << std::endl;

	if (valMSet.count(-10)) {
		std::cout << "-10 element exists." << std::endl;
	}

	std::set<int>::iterator it = valMSet.find(-10);
	if (it != valMSet.end()) {
		std::cout << *it << std::endl;
		++it;
		std::cout << *it << std::endl;
	}

	std::pair<std::set<int>::iterator, std::set<int>::iterator> range = valMSet.equal_range(40);
	std::for_each(range.first, range.second, [=](const int & n) {std::cout << n << std::endl; });

	if (!valMSet.empty()) std::cout << "Multiset is not empty." << std::endl;

}