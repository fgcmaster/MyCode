#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <iostream>
#include <unordered_map>

using namespace std;

typedef vector<int> IntVec;
typedef vector<IntVec> VecVec;
typedef unordered_map<int, int> IntMap;

class Solution
{
	public:
		vector<vector<int>> threeSum(const vector<int>& nums)
		{
			IntMap numMap;
			for(int i = 0; i < nums.size(); ++i)
			{
				numMap[nums[i]] = i;
			}
			VecVec result;
			IntVec eachLine;
			for(int i = 0; i < nums.size(); ++i)
			{
				int oppositeNum = -1*nums[i];
				eachLine.clear();
				for(int j = 0; j < nums.size(); ++j)
				{
					int leftNum = oppositeNum - nums[j];
					if(numMap.find(leftNum) != numMap.end() && numMap[leftNum] > j && j != i && numMap[leftNum] != i)
					{
						int minNum = min(min(nums[i], nums[j]), leftNum);
						int maxNum = max(max(nums[i], nums[j]), leftNum);
						int medNum = nums[i] + leftNum + nums[j] - minNum - maxNum;
						eachLine.clear();
						result.push_back({minNum, medNum, maxNum});
					}
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

void checkResult(const IntVec& leftNums)
{
	Solution sol;
	VecVec result = sol.threeSum(leftNums);
	printArray(leftNums);
	for(auto vec: result)
	{
		printArray(vec);
	}
	printf("\n~~~~~~~\n");
}

int main()
{
	checkResult({-1,0,1,2,-1,-4});

	return 0;
}

