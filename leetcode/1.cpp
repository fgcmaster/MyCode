#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <iostream>
#include <unordered_map>

using namespace std;

typedef vector<int> IntVec;
typedef unordered_map<int, int> IntMap;

class Solution
{
	public:
		vector<int> twoSum(const vector<int>& nums, int target)
		{
			IntMap numMap;
			for(int i = 0; i < nums.size(); ++i)
			{
				numMap[nums[i]]= i;
			}
			IntVec result;
			int minusNum = 0;
			for(int i = 0; i < nums.size(); ++i)
			{
				minusNum = target - nums[i];
				if(numMap.find(minusNum) !=numMap.end() && numMap[minusNum] > i)
				{
					int indices = numMap[minusNum];
					result.push_back(i);
					result.push_back(indices);
				}
			}
			return result;
		}
};

void printArray(const IntVec& nums)
{
	for(IntVec::const_iterator iter = nums.begin();
			iter != nums.end(); ++iter)
	{
		printf("%d\t", *iter);
	}
	printf("\n");
}

void checkResult(const IntVec& leftNums, int value, const IntVec& target)
{
	Solution sol;
	IntVec result = sol.twoSum(leftNums, value);
	if(result[0] == target[0] && result[1] == target[1])
	{
		printf("\ttrue.\n");
	}
	else
	{
		printf("\tfalse, %d %d != %d %d\n", result[0], result[1], target[0], target[1]);
	}
}

int main()
{
	checkResult({2,7,11,15}, 9, {0,1});
	checkResult({2,7,11,15, 7}, 14, {1,4});
	checkResult({3,2,4}, 6, {1,2});

	return 0;
}

