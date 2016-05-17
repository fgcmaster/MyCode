#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

class Solution
{
	public:
		int removeElement(vector<int>& nums, int val) 
		{
			vector<int>::iterator pivot = nums.begin();
			for(vector<int>::iterator iter = nums.begin();
					iter != nums.end(); ++iter)
			{
				if(*iter != val)
				{
					*pivot++ = *iter;
				}
			}
			return distance(nums.begin(), pivot);
		}
};

int main()
{
	Solution sol;
	vector<int> nums = {4,0, 2,4,4,5,6,90,4,4,4};

	for(vector<int>::const_iterator iter = nums.begin();
			iter != nums.end(); ++iter)
	{
		printf("%d\t",*iter);
	}
	printf("\n");

	printf("%d\n",sol.removeElement(nums, 4));

	for(vector<int>::const_iterator iter = nums.begin();
			iter != nums.end(); ++iter)
	{
		printf("%d\t",*iter);
	}
	printf("\n");
	return 0;
}

