#include "MyString.h"

int main(void)
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

	s1.Insert(2, '6');
	std::cout << s1.c_str() << std::endl;
	std::cout << s1.size() << std::endl;
	std::cout << s1.capacity() << std::endl;

	s1.Insert(4, " I Love YOU ");//he6l I Love YOU lo world
	std::cout << s1.c_str() << std::endl;
	std::cout << s1.size() << std::endl;
	std::cout << s1.capacity() << std::endl;

	s1.Erase(2, 3);//heI Love YOU lo world
	std::cout << s1.c_str() << std::endl;
	std::cout << s1.size() << std::endl;
	std::cout << s1.capacity() << std::endl;


	return 0;
}