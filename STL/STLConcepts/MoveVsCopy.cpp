#include "MoveVsCopy.h"

//This function will be called whenever we are passing an object normally
void playWithObject(Entity& ref)
{
	std::cout << "Working with a reference of a object." << std::endl;
	Entity locEn = ref;
	std::cout << "New object after creation:" << std::endl;
	locEn.Print();
	std::cout << "Passed object after using in creation of another object:" << std::endl;
	ref.Print();
}

//This function will be called when we when we are using Temp object (RValue) or using std::move
void playWithObject(Entity&& Rref)
{
	std::cout << "Passed temp object (RValue Ref), will work accordingly." << std::endl;
	Entity locEn = std::move(Rref); //This syntax of std::move is need despite Rref being of type &&, this is because
									//it can still be used in normal syntax of Entity loc = Rref; without intending to move contents
									//to express move contents we should express it by std::move.
									
	std::cout << "New object after creation:" << std::endl;
	locEn.Print();
	std::cout << "Passed object after using in creation of another object:" << std::endl;
	Rref.Print();
}

void ideaOfMoveAndMoveCopy()
{
	//C++11 has introduce the idea of MOVE and RValue reference. They both are meant to serve one purpose: How to handle temporary objects.
	//These kind of temporary objects are made when we have no other way but to first construct an object and then dispatch it to others to
	//construct similar object. These kind of objects which acts like an temporary information holder can become a burden for a program if they
	//allocate (which has to be deallocated later) special resource like memory file handles etc.

	//New C++ code syntax allows to idenify such temporary automatically or can also be explicitly identified by the programmer.
	//Impilicit temporary objects:
	// String str(String("fsf"));
	// String str = String("sfdf");

	//Explicit Temporary object:
	//String str1 = std::move(str2);

	//C++ further allow to define a program flow based on whether we are working with temporary objects or non-temp objects:
	//For this C++ provides R-Value Refernce
	//A function signature for Temporary/RValue object argument call:
	// func(String&& dtr);

	//This way we can split the program flow for handling of temporary objects or usual L-Value objects.

	//Note that std::move does not move anything actually, it just tells the program flow that we might be working with temporary object.

	//Note if a functions looks like this:
	// func1(String&& obj) {
	//   ....
	//   func2(std::move(obj));
	//   ....
	// }
	//In above function we should still use std::move to get the right func2 R-Value version even though obj is of type String&&. This is because
	//'obj' can still be used in a function call where we do not intend to move things out of the object 'obj' and as we do not have called 
	//something std::unmove. 


	//With the introduction of RValue and Move our usual 'Rule of Three' has become 'Rule of Five (if any of destructor, copy constructor, move-constructor,
	//copy-assignment operator, move-assignment operator are required, then if the move semantics are desirable then we have to declare all of the five members)'

	//String str1("xyz");
	//String str2 = std::move(str1); //stealing the contents, rendering str1 without contents and useless, and programer should remain aware of it in
	//								//rest of the program control. std::move and RValue reference area is meant for bigger purpose than this.
	//str2.Print();
	//str1.Print();

	//In below case, imagine Entity class is heavy class where it goes through an extensive build up process of the object, allocating lot of
	//memory on the heap.
	Entity en = Entity("Hello:New contents");
	//in below case we intend to create new copy of the data inside the function and resue object en probably here later in the code
	std::cout << "\n\n";
	playWithObject(en);
	//Here we do not intend to use passed object later any where in the function as it is evident from we have passed 
	//temp value without any kept record here. We want new object inside called function should take away content of the passed object.
	//We ensure call of the right constructor by using std::move inside the called function.
	//Here we call overloaded function for RValue calls to separate the handling of such object. This kind of speration of flow of temp values
	//is allowed by the idea of RValue refernce.
	std::cout << "\n\n";
	playWithObject(Entity("Hello:Reused contents"));

}