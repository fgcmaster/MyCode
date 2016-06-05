#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>

using namespace std;

typedef vector<int> IntVec;
typedef vector<IntVec> VecVec;
typedef unordered_map<int, int> IntMap;
typedef unordered_set<int> IntSet;

class Solution
{
	public:
		vector<vector<int>> threeSum(vector<int>& nums)
		{
			sort(nums.begin(), nums.end());
			IntMap numMap;
			int greaterEqualZeroPos = -1;
			for(size_t i = 0; i < nums.size(); ++i)
			{
				if(nums[i] >= 0 && greaterEqualZeroPos == -1)
				{
					greaterEqualZeroPos = i;
				}
				numMap[nums[i]] = i;
			}
			VecVec result;
			for(size_t i = 0; i < nums.size(); ++i)
			{
				if(i != 0 && nums[i] == nums[i-1])
				{
					continue;
				}
				int startPos, endPos;
				int curNum = nums[i];
				if(curNum > 0)
				{
					startPos = 0;
					endPos = greaterEqualZeroPos-1;
				}
				else
				{
					startPos = greaterEqualZeroPos;
					endPos = nums.size()-1;
				}
				int oppositeNum = -1*curNum;
				IntSet numSet;
				for(int j = startPos; j < endPos; ++j)
				{
					int leftNum = oppositeNum - nums[j];
					if( (nums[j] >= 0 && leftNum < 0)
							||(nums[j] < 0 && leftNum >= 0))
					{
						continue;
					}
					if(numMap.find(leftNum) != numMap.end() && numMap[leftNum] > j 
							&& numSet.count(leftNum) == 0)
					{
						numSet.insert(leftNum);
						int minNum = nums[i];
						int maxNum = nums[j];
						int medNum = leftNum;
						if(minNum > medNum)
						{
							swap(minNum, medNum);
						}
						if(minNum > maxNum)
						{
							swap(minNum, maxNum);
						}
						if(medNum > maxNum)
						{
							swap(medNum, maxNum);
						}
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
	VecVec result = sol.threeSum(const_cast<IntVec&>(leftNums));
	printArray(leftNums);
	for(auto vec: result)
	{
		printArray(vec);
	}
	printf("\n~~~~~~~\n");
}

int main()
{
	/*  	checkResult({-1,0,1,2,-1,-4});
	checkResult({-1,0,1,2, 2,-1,-4});
	checkResult({-1,0,2});
	checkResult({-2,-1,2, 3});
	checkResult({-2,-1,-1,-1,2, 3});
	checkResult({0,-2,-1,2, 0,3,-1,-1,3,-1});
*/
	checkResult({0,0,0});
}

