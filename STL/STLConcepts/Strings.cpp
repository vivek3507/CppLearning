#include <iostream>
#include <string>

void cStyleString()
{
	//A String is a sequence of characters and therefore an array of chars. As char is basic data type like int, array of char
	//should not be any different than array of any basic data type. Which is true.
	//The whole confusion around strings arises from our usual perception of strings, for example:
	//	We know that "Vivek" is a character string and this is how we want to write it in our code. While an array of ints
	//	is "123456" is not same as {1 2 3 4 5 6}, so we need special way of representing srings like "Vivek" unlike normal
	//	base data array {'V' 'i' 'v' 'e' 'k'}. 
	//Further we want the convinience handling strings without knowing its actual size, for example:
	//	std::cout << "Vivek" << std::endl;
	//should know when the char array ends. This is easy to support with char arrays as a non-important character called NULL exist having value 0.
	//Which is not visible either and can really mark the end of an char array which is not possible with integer array as 0 means 0 and it has its significant.
	//Then why not use NULL char for our advantage.
	//And by now char array (=>string) representation has become entirely different from other data type array and therefore source of confusion.

	//Look at followings, They all are same as they are array of some data type, but with one major difference: While name and numbers are pointing
	//to filled stack location from readonly data segment values, nameC points to the readonly data segment directly and therefore const char* type.
	//We can modify the values say at nameC[3] = 'a';. We can do name[3] = 'a';. This brings one more differenciator how strings can be represented differently
	//than normal compile time arrays.

	//char name[6] = { 'V', 'i', 'v', 'e', 'k', '\0' };
	//Same as below;
	char nameS[6] = "Vivek"; //Stack filled char array or string
	//char nameS[] = "Vivek";
	int numbersS[6] = { 1, 2, 3, 4, 5, 6 }; //Stack filled int array or string of ints
	const char* nameL = "Vivek";	//Directly pointing to String literal in readonly part of data segment (const segment): "Vivek" is string literal

	std::cout << nameS << std::endl;
	std::cout << nameL << std::endl;

	//allowed
	nameS[3] = 'a';

	//not allowed
	//nameL[3] = 'a';  //C++ does not have defined behavior for this

	std::cout << nameS << std::endl;
	std::cout << nameL << std::endl;

	//Simplifying Strings usage lead to complicating it in C/C++.

	//Above all strings are either created on stack (by reading from data segment) or directly pointing to data segment chars.
}

void stringsOfCPP()
{
	//They are not the strings on stack. The object is on stack but it allocates memory onn heap to store chars.

	std::string name = "Kumar";

	std::cout << name << std::endl;

	//string class allows below
	name += " jksd";
	//but not this, as wee are trying to add to string literals
	//name = "jksj" + "nkjn";

	//Below is allowed
	//using std::string_literals;
	//name = "jksj"s + "nkjn"s;


	std::cout << name << std::endl;

}

static uint32_t _allocations = 0;

void* operator new(size_t sz)
{
	_allocations++;

	return malloc(sz);
}

void smallStringOptimization() //small string optimization done by STL
{
	_allocations = 0;
	std::cout << "\n\n\n";
	std::cout << "smallStringOptimization" << std::endl;
	std::cout << _allocations << " Allocated." << std::endl;

	std::string str("sbfksdljw345634"); //if more than 15 then visual studio attahced compiler use heap storage othereise not. Visible in Relase mode.

	std::cout << str << std::endl;
	std::cout << _allocations << " Allocated." << std::endl;

}

static void printName(const std::string& part)
{
	std::cout << part << std::endl;
}


//static void printName(std::string_view str) //supported in Cpp17, similar to below
static void printName(const char* part, int offset, int count)
{
	for (int i = offset; i < offset + count; ++i)
		std::cout << part[i];

	std::cout << std::endl;
}




void makeStringsFaster()
{
	std::cout << "\n\n\nMake string faster..." << std::endl;
	_allocations = 0;

	std::string name = "Vivek Kumar";

	std::string firstName = name.substr(0, 5); //move costructor called on temp return string object
	std::string lastName = name.substr(6, 5); //move constructor called on temp return string object

	printName(firstName);
	printName(lastName);

	std::cout << _allocations << " Allocations." << std::endl;

	std::cout << "\n\n\n";

	printName(name.c_str(), 0, 5);
	printName(name.c_str(), 6, 5);



	std::cout << _allocations << " Allocations." << std::endl;

}

void ideaOfString()
{
	cStyleString();

	stringsOfCPP();

	smallStringOptimization(); //Visible in Relase Mode

	makeStringsFaster();
}