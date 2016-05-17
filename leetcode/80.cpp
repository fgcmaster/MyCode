/*
 * =====================================================================================
 *
 *       Filename:  80.cpp
 *
 *    Description:  leetnode 80
 *
 *        Version:  1.0
 *        Created:  05/16/2016 03:55:56 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <iostream>

using namespace std;

class Solution
{
	public:
		int removeDuplicates(vector<int>& nums) 
		{
			if(nums.empty())
			{
				return 0;
			}
			int cnt = 1;
			vector<int>::iterator pivot = nums.begin();
			for(vector<int>::iterator iter = nums.begin()+1;
					iter != nums.end();++iter )
			{
				if(*iter != *pivot)
				{
					*++pivot = *iter;
					cnt = 1;
				}
				else if(cnt < 2)
				{
					*++pivot = *iter;
					cnt++;
				}
			}
			nums.erase(pivot+1, nums.end());
			return nums.size();
		}
};

int main()
{
	Solution sol;
	//vector<int> nums = {-3,-3,-3, 0, 1,2,4,5,6,90};
	//vector<int> nums = {-3,0, 0,0,0,0, 1,2,4,5,6,90,90};
	//vector<int> nums = {-3,0, 0,0,0,0, 1,2,4,5,6,90,90,90};
	vector<int> nums = {-3,-3,0, 0,0,0,0, 1,2,4,4,5,6,6,6,90,90,90};

	for(vector<int>::const_iterator iter = nums.begin();
			iter != nums.end(); ++iter)
	{
		printf("%d\t",*iter);
	}
	printf("\n");

	printf("%d\n",sol.removeDuplicates(nums));

	for(vector<int>::const_iterator iter = nums.begin();
			iter != nums.end(); ++iter)
	{
		printf("%d\t",*iter);
	}
	printf("\n");
	return 0;
}

