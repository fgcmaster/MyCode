#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <iostream>

using namespace std;

class Solution
{
	public:
		int search(const vector<int>& nums, int target)
		{
			return search_i(nums, 0, nums.size()-1, target);
		}
	private:
		int search_i(const vector<int>& nums, int start, int end, int target)
		{
			if(start <= end)
			{
				int midPos = (start+end)/2;
				int midValue = nums[midPos];
				if(target == midValue)
				{
					return midPos;
				}
				if(nums[start]< midValue)
				{
					if(target >= nums[start] && target < midValue)
					{
						return binarySearch(nums, start, midPos-1, target);
					}
					else
					{
						return search_i(nums, midPos+1, end, target);
					}
				}
				else if(midValue < nums[end])
				{
					if(target > midValue && target <= nums[end])
					{
						return binarySearch(nums, midPos+1, end, target);
					}
					else
					{
						return search_i(nums, start, midPos-1, target);
					}
				}
				else if(nums[start] == midValue || nums[end] == midValue)
				{
					int leftResult = search_i(nums, start, midPos-1, target);
					if(leftResult != -1)
					{
						return leftResult;
					}
					else
					{
						return search_i(nums, midPos+1, end, target);
					}
				}
			}
			return -1;
		}
	public:

		int binarySearch(const vector<int>& nums, int start, int end, int target)
		{
			int midPos, resultPos = -1;
			while(start <= end)
			{
				midPos = (start + end)/2;
				if(target < nums[midPos])
				{
					end = midPos-1;
				}
				else if(target > nums[midPos])
				{
					start = midPos + 1;
				}
				else
				{
					resultPos = midPos;
					break;
				}
			}
			return resultPos;
		}
};

int main()
{
	Solution sol;
	//vector<int> nums = {4,5,6,7,0,1,2};
	//vector<int> nums = {4,5,6,7, 0};
	vector<int> nums = {3, 3,9,19,23, 45, 46,49, 0, 0, 0,0,0};
	//vector<int> nums = {};
	//vector<int> nums = {7,7,7,7,7,7,7,7,7,7,4,5,6,7,7,7,7};

	for(int i = 0; i < nums.size(); ++i)
	{
		printf("%d\t", nums[i]);
	}
	printf("\n");
	int findValue;
	cin >> findValue;
	//printf("%d\n", sol.binarySearch(nums, 0, nums.size()-1, findValue));
	printf("%d\n", sol.search(nums, findValue));

	return 0;
}

