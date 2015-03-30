/*************************************************************************
	> File Name: test.cpp
	> Author: fgcmaster
	> Mail: fgcmaster@163.com 
	> Created Time: 2015年03月11日 星期三 11时09分43秒
 ************************************************************************/

#include <iostream>
#include <sstream>

int main()
{
	int aa = 55;
	std::ostringstream iss;
	iss << aa;

	std::cout << iss.str() << " aa " << std::endl;
}
