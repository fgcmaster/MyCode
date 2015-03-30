/*************************************************************************
	> File Name: threadtest.cpp
	> Author: fgcmaster
	> Mail: fgcmaster@163.com 
	> Created Time: Fri 27 Mar 2015 02:13:02 PM CST
 ************************************************************************/

#include <iostream>
#include <mutex>
#include <thread>

std::mutex thisMutex;

void printThread(int i)
{
	std::cout << i << std::endl;
}

void print_threadid(int id)
{
	std::lock_guard<std::mutex> guard(thisMutex);
	printThread(id);
}

const int THREAD_NUM = 3;

int main()
{
	std::thread testThread[THREAD_NUM];
	int i = 0;
	for(int i = 0; i < THREAD_NUM; i++)
	{
		testThread[i] = std::thread(print_threadid, i);
	}

	for(auto& th: testThread)
	{
		th.join();
	}
	return 0;
}

