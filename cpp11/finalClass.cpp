/************************************************************************
	> File Name: finalClass.cpp
	> Author: fgcmaster
	> Mail: fgcmaster@163.com 
	> Created Time: Fri 27 Mar 2015 10:26:32 AM CST
 ************************************************************************/
#include <iostream>
#include <memory>

class NoDerivedClass final
{
	public:
		void test()
		{
			std::cout << " derived of this class is not permitted." << std::endl;
		}
};

/*
class WrongDerivedClass: public NoDerivedClass
{
	public:
		void test()
		{
		}
};
*/


int main()
{
	std::cout << " test of No derived class of final." << std::endl;
	std::unique_ptr<NoDerivedClass> uniPtr(new NoDerivedClass());
	uniPtr->test();
}
