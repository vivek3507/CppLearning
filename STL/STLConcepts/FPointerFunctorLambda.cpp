#include <iostream>
#include <functional>
#include <vector>

//https://www.cprogramming.com/tutorial/functors-function-objects-in-c++.html

static void forEach(std::vector<int>& vec, void (*InjectedCode1)(int), bool(*InjectedCode2)(int) ) {
	for (auto i : vec) {
		if (InjectedCode2(i)) {
			InjectedCode1(i);
		}
	}
}

static void print(int i)
{
	std::cout << i << ",";
}

static bool chossen(int i)
{
	if (i < 0) {
		return true;
	}
	else {
		return false;
	}
}

void ideaOfFunctionPointer()
{
	std::vector<int> val{ 1,2,4,-10, 30, -1 };
	void(*func1)(int) = print;
	bool(*func2)(int) = chossen;
	forEach(val, func1, func2);

}

class Find
{
	int _key;
public:
//	Find() {
//		_key = 30;
//	}

	Find(int i) {
		_key = i;
	}
	//overload the function call operator. This is what will make an oridnary object as callable object or Functor
	bool operator()(int val) {
		return _key == val;
	}
};

static void ForEach(std::vector<int> val, Find fd)
{
	for (auto i : val) {
		if (fd(i)) {
			std::cout << i << ",";
		}
	}
}

//An object which can be called like a function
//It allows functon be prepared before it is called. We prepare objects, quality of going through prepraparation comes from there.
void ideaOfFunctor()
{
	std::vector<int> val{ 1,2,4,-10, 30, -1 };
	Find five(5);
	ForEach(val, five);
	Find ten(-10);
	ForEach(val, ten);

}

template <typename compare>
static void ForEach(std::vector<int> val, compare f = compare(4))
{
	for (auto i : val) {
		if (f(i)) {
			std::cout << i << ",";
		}
	}
}

//It allows us to pass both function pointer or Functor
void ideaOfTemplatedFunctor()
{
	std::vector<int> val{ 1,2,4,-10, 30, -1 };
	Find one(1);
	//passing functor
	ForEach<Find>(val, one);
	std::cout << std::endl;
	//passing functor with default value
	ForEach<Find>(val); //this is how comparator object behaves in std::set/std::map
	std::cout << std::endl;
	//passing function pointer
	ForEach<bool(*)(int)>(val, chossen);
	std::cout << std::endl;

}

static void forEach(std::vector<int>& vec, void(*InjectedCode1)(int), std::function<bool(int)> lFunc) {
	for (auto i : vec) {
		if (lFunc(i)) {
			InjectedCode1(i);
		}
	}
}

void ideaOfLambdaFunction()
{
	int key1 = 5;
	int key2 = 10;
	//Lambda functions are anonymous function objects which has works around the idea of Use-And-Throw.
	//Use-And-Throw means that this function does not exist like usual functions with their definition/declaration managment.
	//As with usual functions there is a parameter list and return type. Here also we can specify the parameter list and most of the
	//time return type is deduced or we can mention that also.
	//Here main thing is to remember that this function is not being used here, it is just being defined here. It will be passed around
	//and will be called as per the signature and there the parameter will be passed in that context. So the parameter list is entirly
	//made for that context.
	//Now what if we want to trasfer something from this context to the context where this lambda function will be used.
	//Instead of messing up with the lambda function signature it provides a capture list '[]', which can be filled with current context
	//variable either by value (=) or by reference, selectively or all of them (which are used inside the lambda function body).
	//This internally might be being passed as pointers hard value, not sure, but it facilitates it.
	//C++ lamda functions facilitate very convinient way of injecting logic, though same effect can be achived using other existing ways,
	//like functors and classes with virtual functions etc.
	 
 	auto lambda1 = [=](int a) { return a >= key1 && a <= key2; }; //all by value
	auto lambda2 = [&](int a) { return a >= key1 && a <= key2; }; //all by reference
	auto lambda3 = [key1, &key2](int a) { return a >= key1 && a <= key2; }; //all by value
	auto lambda4 = [key1, &key2](int a) mutable { key1 = 45;  return a >= key1 && a <= key2; }; //we can not modify lvalue key1 (as passed by value) without mutable.
	auto lambda5 = [key1, &key2](int a) { key2 = 45;  return a >= key1 && a <= key2; }; //by refernece value can be modified without mutable keyword

	std::vector<int> val{ 1,2,4,-10, 30, -1 };

	//One another important thing is that these lambda functions acts like an object as they preserve the information passed on (by value)
	//by capture block at the time when they were created. It means they differ in thier construction and exist as separate objects.
	//If we pass it by reference it will still be separate objects, the difference is that they are linked to latest values.

	//Lambda Functions are objects!!!

	std::cout << "lambda1" << std::endl;
	forEach(val, print, lambda1);
	std::cout << std::endl;
	key1 = 1; key2 = 3;
	std::cout << "lambda2" << std::endl;
	forEach(val, print, lambda2);
	std::cout << std::endl;
	key1 = 0; key2 = 3;
	std::cout << "lambda3" << std::endl;
	forEach(val, print, lambda3);
	std::cout << std::endl;
	key1 = -10; key2 = 3;
	std::cout << "lambda4" << std::endl;
	forEach(val, print, lambda4);
	std::cout << std::endl;
	key1 = -30; key2 = 2000;
	std::cout << "lambda5" << std::endl;
	forEach(val, print, lambda5);
	std::cout << std::endl;

}


