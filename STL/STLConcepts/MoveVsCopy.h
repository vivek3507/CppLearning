#pragma once
#include <string>
#include <iostream>


//Rule of 3
//Rule of 5

class String
{
	char* m_Data;
	int m_size;
public:
	String()=default;
	String(const char* str)
	{
		std::cout << "String:const char* Constructor called." << std::endl;
		m_size = strlen(str);
		m_Data = new char[m_size];

		memcpy(m_Data, str, m_size);
	}

	String(const String& str) //copy constructor: Deep Copy
	{
		std::cout << "String:Copy Constructor called." << std::endl;
		m_size = str.m_size;
		m_Data = new char[m_size];

		memcpy(m_Data, str.m_Data, m_size);
	}

	String(String&& str) noexcept	//RValue copy/move constructor: Shallow copy as it is best here
	{
		std::cout << "String:RValue Copy Constructor called." << std::endl;
		m_size = str.m_size;
		m_Data = str.m_Data; //moved

		//made other object hollow
		str.m_size = 0;
		str.m_Data = nullptr;
	}

	String& operator=(const String& lhs)
	{
		if (this != &lhs) {
			std::cout << "String:Assignment operator called." << std::endl;
			if (m_Data) {
				delete m_Data;
			}
			m_size = lhs.m_size;
			m_Data = new char[m_size];

			memcpy(m_Data, lhs.m_Data, m_size);
		}
		return *this;
	}

	String& operator=(String&& lhs)
	{
		if (this != &lhs) {
			std::cout << "String:Move Assignment operator called." << std::endl;
			if (m_Data) {
				delete m_Data;
			}
			m_size = lhs.m_size;
			m_Data = lhs.m_Data;

			lhs.m_Data = 0;
			lhs.m_size = 0;
		}
		return *this;
	}

	~String()
	{
		std::cout << "String:Destructor called." << std::endl;
		m_size = 0;
		delete[] m_Data;
		m_Data = nullptr;
	}

	void Print()
	{
		//std::cout << "Stored String:";
		for (int i = 0; i < m_size; ++i) {
			std::cout << m_Data[i];
		}

		//std::cout << ".";
		std::cout << std::endl;
	}
};

class Entity {
	String m_String;
public:
	Entity(String& str)  //usual constructor
		: m_String(str)
	{
		std::cout << "Entity:Constructor called." << std::endl;
	}

	Entity(String&& str) noexcept  //RValue constructor => Move Constructor for other value type
		: m_String(std::move(str))	//this std::move is need as we have to make it clear to that moving of content is intended
	{
		std::cout << "Entity:RValue reference Base Constructor called." << std::endl;
	}

	Entity(Entity& obj)		//copy-constructor
		: m_String(obj.m_String)
	{
		std::cout << "Entity:Copy Constructor called." << std::endl;
	}

	Entity(Entity&& obj) noexcept //RValue move-constructor
		: m_String(std::move(obj.m_String)) //this std::move is need as we have to make it clear to that moving of content is indended
	{
		std::cout << "Entity:RValue reference Copy Constructor called." << std::endl;
	}

	Entity& operator=(Entity& en) //Copy-Assignment operator
	{
		if (this != &en) {
			m_String = en.m_String;
		}
	}

	Entity& operator=(Entity&& en) //Move-Assignment operator
	{
		if (this != &en) {
			m_String = std::move(en.m_String);
		}
	}

	void Print()
	{
		m_String.Print();
	}
};