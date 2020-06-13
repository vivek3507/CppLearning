#include <iostream>
#include <vector>
#include <algorithm>

void ideaOfSTLVectors()
{
	//std::vector<int> vecV(10,9);
	std::vector<int> vecV;

	std::cout << "Max size array possible:" << vecV.max_size() << std::endl;
	std::cout << "Current element size of the array:" << vecV.capacity() << std::endl;
	std::cout << "Current heap capacity of the array:" << vecV.capacity() << std::endl;

	vecV.push_back(5); //O(1) insertion
	vecV.push_back(1);
	vecV.push_back(6);
	vecV.push_back(10);
	vecV.push_back(7);
	vecV.push_back(2);
	vecV.push_back(10);
	std::cout << vecV.size() << std::endl;
	
	//removing elements
	vecV.pop_back(); //take out the element form the back only => O(1)
	vecV.erase(vecV.begin() + 4); //erase en element at the specified location, and shift elements afterward => O(n)
	//vecV.erase(vecV[2]); //not possible, operator [] returns reference of the underlying 'data', but not the iterator
						   //threrefor not possible.
	//Adding elements
	std::cout << vecV.size() << std::endl;
	vecV.insert(vecV.begin()+2, 100); //insert the elements by shifting them (O(n))
	//there is no member called add() in vectors
	
	//changing value/accessing
	std::cout << vecV[2] << std::endl; //it does not check for the bound, but it is also a reference of the value
	vecV[2] = 1000;
	std::cout << vecV[2] << std::endl; //it does not check for the bound, but it is also a reference of the value
	vecV.at(2) = -1000;
	std::cout << vecV.at(2) << std::endl;
	std::cout << vecV.size() << std::endl;
	std::cout << vecV.front() << std::endl; //named accessors for for front and back matching with modifiers push_back/pop_back
	std::cout << vecV.back() << std::endl;
	
	//if want to find an element in the array we have to do sorting, which will take n*log(n) time
	std::sort(vecV.begin(), vecV.end()); //n*log(n)
	
	//below binary seach will take log(n) time
	if (std::binary_search(vecV.begin(), vecV.end(), 5)) {
		std::cout << "Found 5." << std::endl;
	}

	std::vector<int>::iterator it = vecV.begin() + 3;
	*it = 6;

	//SIZES
	std::cout << "Current heap capacity of the array:" << vecV.capacity() << std::endl;
	vecV.reserve(vecV.capacity() * 2); //change the heap size of the array
	std::cout << "Current heap capacity of the array:" << vecV.capacity() << std::endl;

	vecV.resize(vecV.size() - 2); // reduce the number of elements from the back of the array
	std::cout << vecV.size() << std::endl;

	vecV.shrink_to_fit(); //it will invalidate all the iterators if it reallocates memory achieve this

	std::cout << "After shrink_to_fit heap capacity of the array:" << vecV.capacity() << std::endl;

	//Special Modification
	vecV.emplace(vecV.begin() + 3, -99); //Similar to insert, but in place creation of the object, in this case simple int, 
										 //but it could be a class obj, in that case we will pass constuctor parameters 
										 //as variable arg list. It is also O(n) as insertion
	std::cout << "Current heap capacity of the array:" << vecV.capacity() << std::endl;
	vecV.emplace_back(-999);			//Same as above but at the back of the array => O(1)
	std::cout << "Current heap capacity of the array:" << vecV.capacity() << std::endl;

	if (!vecV.empty()) {
		std::cout << "Array is not empty." << std::endl;
		std::cout << vecV.size() << std::endl;
		vecV.clear(); //clear the array, by removing all the elements and calling their destructors
		std::cout << vecV.size() << std::endl;
	}
}