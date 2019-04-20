#include "MyString.h"
#include <iostream>

void TestString1()
{

	Gerald::String s1("hello");
	std::cout << s1.c_str() << std::endl;
	std::cout << s1.size() << std::endl;
	std::cout << s1.capacity() << std::endl;

	s1 += ' ';
	s1 += "world";
	std::cout << s1.c_str() << std::endl;
	std::cout << s1.size() << std::endl;
	std::cout << s1.capacity() << std::endl;

	//s1.resize(3);
	//std::cout << s1.c_str() << std::endl;
	//std::cout << s1.size() << std::endl;
	//std::cout << s1.capacity() << std::endl;

	//s1.resize(7, 'a');
	//std::cout << s1.c_str() << std::endl;
	//std::cout << s1.size() << std::endl;
	//std::cout << s1.capacity() << std::endl;

	//s1.resize(13, 'e');
	//std::cout << s1.c_str() << std::endl;
	//std::cout << s1.size() << std::endl;
	//std::cout << s1.capacity() << std::endl;
	/*
	int pos = s1.find('e');

	int spos = s1.find("wor");

	std::cout << pos << std::endl;
	std::cout << spos << std::endl;*/

	//s1.Insert(2, '6');
	//std::cout << s1.c_str() << std::endl;
	//std::cout << s1.size() << std::endl;
	//std::cout << s1.capacity() << std::endl;

	//s1.Insert(4, " I Love YOU ");//he6l I Love YOU lo world
	//std::cout << s1.c_str() << std::endl;
	//std::cout << s1.size() << std::endl;
	//std::cout << s1.capacity() << std::endl;

	//s1.Erase(2, 3);//heI Love YOU lo world
	//std::cout << s1.c_str() << std::endl;
	//std::cout << s1.size() << std::endl;
	//std::cout << s1.capacity() << std::endl;

	Gerald::String s2 = s1.substr(1, 5);
	std::cout << s2.c_str() << std::endl;
	std::cout << s2.size() << std::endl;
	std::cout << s2.capacity() << std::endl;

	s2.Insert(0, "Gerald");//Geraldello
	std::cout << s2.c_str() << std::endl;
	std::cout << s2.size() << std::endl;
	std::cout << s2.capacity() << std::endl;

	s2.Erase(3, 7);
	std::cout << s2.c_str() << std::endl;
	std::cout << s2.size() << std::endl;
	std::cout << s2.capacity() << std::endl;


}




void TestIterator()
{
	Gerald::String s("Hello Gerald!");

	std::cout << s << std::endl;

	s.Insert(s.size(), 'G');
	std::cout << s << std::endl;

	s.Erase(1, 3);
	std::cout << s << std::endl;
}

int main(void)
{
	TestIterator();
	return 0;
}