/*
 * =====================================================================================
 *
 *       Filename:  26.cpp
 *
 *    Description:  leetnode
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
			vector<int>::iterator start = nums.begin();
			for(vector<int>::iterator iter = nums.begin();
					iter != nums.end(); )
			{
				if(iter == nums.begin())
				{
					iter++;
					continue;
				}

				if(*iter != *start)
				{
					if(start+1 != iter)
					{
						printf("%d\n", *iter);
						iter = start = nums.erase(start+1, iter);
					}
					else
					{
						iter++;
					}
				}
				else
				{
					iter++;
				}

				if(iter == nums.end() && start+1 != iter)
				{
					nums.erase(start+1, iter);
					break;
				}
			}
			return nums.size();
			/*  
			int lastValue = nums[0];
			for(vector<int>::iterator iter = nums.begin();
					iter != nums.end(); )
			{
				if(iter == nums.begin())
				{
					iter++;
					continue;
				}
				if(*iter == lastValue)
				{
					iter = nums.erase(iter);
				}
				else
				{
					lastValue = *iter++;
				}
			}
			return nums.size();
			*/
		}
};

int main()
{
	Solution sol;
	vector<int> nums = {-3,0, 1,1,2,4,5,6,6,6,6,90,90};
	printf("%d\n",sol.removeDuplicates(nums));

	for(vector<int>::const_iterator iter = nums.begin();
			iter != nums.end(); ++iter)
	{
		printf("%d\t",*iter);
	}
	printf("\n");
	return 0;
}

