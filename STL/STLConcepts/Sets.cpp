#include <iostream>
#include <set>
#include <functional>

#define LOGCOMMA(x) std::cout << x << ",";

bool function(const int& lsh, const int& rhs) { return lsh < rhs; };

void ideaOfSets()
{
	std::set<int> setV; //Keeps sorted based on the value. Insertion take log(n) time. Insertion order is lost. Sorting is not needed.
					//Implemented as Red and Black Tree

	if (setV.empty()) std::cout << "In the begining set is empty." << std::endl;
	std::cout << "Max set size possible:" << setV.max_size() << std::endl;
	std::pair<std::set<int>::iterator, bool> pr;
	setV.insert(20);
	setV.insert(30);
	setV.insert(40);
	setV.insert(-40);
	setV.insert(1000);

	std::cout << "Current size of the set:" << setV.size() << std::endl;
	for (auto val : setV) { //prints in sorted order
		LOGCOMMA(val)
	}
	std::cout << std::endl;

	auto p = setV.insert(10);

	if (p.second == true) {
		std::cout << "inserted element " << *(p.first) << " was not already present." << std::endl;
	}
	pr = setV.insert(20);
	if (pr.second == false) {
		std::cout << "inserted element " << *(pr.first) << " was already present." << std::endl;
	}

	auto it = setV.find(30); //log(n) time
	if (it != setV.end()) {
		std::cout << "Element " << *it << " found in the set." << std::endl;
	}

	std::set<int>::iterator itf = setV.find(40);
	//*itf = 60;     Not possible with sets, understandably as all the elements are kept sorted in a set, how will you ensure sorted order
					//with such modifications.
	setV.erase(itf); //erase by iterator

	for (auto val : setV) { //prints in sorted order
		LOGCOMMA(val)
	}
	std::cout << std::endl;

	setV.erase(10); //erase by value, erase of a iterator range is also possible by erase(it1, it2)

	std::cout << "Current count of the -10 value:" << setV.count(-10) << std::endl; //It will always be 1 if found as set can not have duplicates.

	setV.emplace(-30); //in place construction of the opbject and insertion as usual

	for (auto val : setV) { //prints in sorted order. Here auto return the value directly rather then iterator, by recognizing the data type
							//of the container
		LOGCOMMA(val)
	}
	std::cout << std::endl;

	auto itLB1 = setV.lower_bound(25);
	auto itUB1 = setV.upper_bound(25);
	auto itLB2 = setV.lower_bound(35);
	auto itUB2 = setV.upper_bound(35);
	if (itLB1 != setV.end()) std::cout << "LB for 25:" << *itLB1 << std::endl;
	if (itUB1 != setV.end()) std::cout << "UB for 25:" << *itUB1 << std::endl;
	if (itLB2 != setV.end()) std::cout << "LB for 35:" << *itLB2 << std::endl;
	if (itUB2 != setV.end()) std::cout << "UB for 35:" << *itUB2 << std::endl;



	std::cout << "Clearing the array." << std::endl;
	setV.clear();
	struct myComp {
		bool _incr;
		myComp(bool val) {
			_incr = val;
		}
		bool operator() (const int& lhs, const int& rhs) const
		{
			if (_incr) {
				return lhs < rhs;
			}
			return lhs > rhs;
		}
	};
	myComp strategy(false);
	std::set<int, myComp> setComp1(strategy); //New comparator operator will make this set to store elements in decending order.
								   //Here myComp struct provide uniary/function-call operator() which will be used for instead of std::less<T> operator
	setComp1.insert(1);
	setComp1.insert(9);
	setComp1.insert(5);
	setComp1.insert(1000);
	setComp1.insert(100);

	for (auto i : setComp1) {
		LOGCOMMA(i);
	}
	std::cout << std::endl;

	std::set<int, bool(*)(const int&, const int&)> setComp2(function); //Above can also be implmented in this way
	setComp2.insert(1);
	setComp2.insert(9);
	setComp2.insert(5);
	setComp2.insert(1000);
	setComp2.insert(100);

	for (auto i : setComp2) {
		LOGCOMMA(i);
	}
	std::cout << std::endl;

	//auto lambda = [] (int& lhs, int& rhs)->bool { return lhs < rhs; };
	//std::set<int, lambda> setComp4; //This usage is not allowed

	//std::set<int> setComp3 = setComp1; //Not possible, which means we have to pass objects exactly with the same signature.
	//std::set<int> setComp3(setComp1); //Same as above, and not possible
	//std::set<int>& setComp3 = setComp1;//Same as above, not possible
	std::set<int> setComp3(setComp1.begin(), setComp1.end()); //This is possible as we are compying elements we are not intereseted in the
															  //compatibility of the container objects. We have shown our interese clearly on elements.
	for (auto i : setComp3) {
		LOGCOMMA(i);
	}
	std::cout << std::endl;
}