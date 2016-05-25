#include <stdlib.h>
#include <stdio.h>
#include <cmath>
#include <vector>
#include <unordered_map>
#include <iostream>

using namespace std;

typedef vector<int> IntVec;
typedef unordered_map<int, bool> IntMap;

void printArray(const IntVec& nums);

class Solution
{
	public:
		int longestConsecutive(vector<int>& nums) 
		{
			IntMap usedMap;
			for(auto num: nums)
			{
				usedMap[num] = false;
			}
			int consecutiveLen = 0;
			for(auto num: nums)
			{
				if(!usedMap[num])
				{
					int currConsecutiveLen = 1;
					for(int i = num+1; ; ++i)
					{
						if(usedMap.find(i) == usedMap.end())
						{
							break;
						}
						else
						{
							currConsecutiveLen++;
						}
					}
					consecutiveLen = max(consecutiveLen, currConsecutiveLen);
				}
			}
			return consecutiveLen;
			/*
			IntVec resultVec;
			longestConsecutive_i(nums, 0, nums.size()-1, resultVec);
			printArray(resultVec);
			return resultVec.size();
			*/
		}
	private:
		void longestConsecutive_i(IntVec& nums, int start, int end, IntVec& resultVec)
		{
			if(start == end)
			{
				resultVec.clear();
				resultVec.push_back(nums[start]);
			}
			int vecSize = end - start;
			swap(nums[start], nums[start+vecSize/2]);
			int pivot = nums[start];
			int j = start;
			for(int i = start; i <= end; ++i)
			{
				if(nums[i] < pivot)
				{
					nums[j++] = nums[i];
					nums[i] = nums[j];
				}
			}
			nums[j] = pivot;
			IntVec leftVec;
			if(start == j)
			{
				leftVec.push_back(nums[start]);
			}
			else
			{
				longestConsecutive_i(nums, start, j-1, leftVec);
			}

			IntVec rightVec;
			if(j == end)
			{
				rightVec.push_back(nums[end]);
			}
			else
			{
				longestConsecutive_i(nums, j+1, end, rightVec);
			}
			int leftSize = leftVec.size();
			int rightSize = rightVec.size();
			if(leftVec[leftSize-1]+1 == pivot && rightVec[0] == pivot+1)
			{
				leftVec.push_back(pivot);
				leftVec.insert(leftVec.end(), rightVec.begin(), rightVec.end());
				resultVec.assign(leftVec.begin(), leftVec.end());
			}
			else if(leftVec[leftSize-1]+1 == pivot && rightVec[0] != pivot+1)
			{
				leftVec.push_back(pivot);
				leftSize+1 > rightSize ? resultVec.assign(leftVec.begin(), leftVec.end())
					: resultVec.assign(rightVec.begin(), rightVec.end());
			}
			else if(leftVec[leftSize-1]+1 != pivot && rightVec[0] == pivot+1)
			{
				rightVec.push_back(pivot);
				leftSize > rightSize+1 ? resultVec.assign(leftVec.begin(), leftVec.end())
					: resultVec.assign(rightVec.begin(), rightVec.end());
			}
			else
			{
				leftSize > rightSize ? resultVec.assign(leftVec.begin(), leftVec.end())
					: resultVec.assign(rightVec.begin(), rightVec.end());
			}
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

void checkResult(const IntVec& leftNums, int target)
{
	Solution sol;
	int result = sol.longestConsecutive(const_cast<IntVec&>(leftNums));
	if(fabs(result - target) < 0.001)
	{
		printf("\ttrue.\n");
	}
	else
	{
		printf("\tfalse, %d != %d\n", result, target);
		printArray(leftNums);
	}
}

int main()
{
	checkResult({100,4,200,1,3,2}, 4);
	checkResult({5,6,100,4,200,1,3,2,7,8}, 8);

	return 0;
}

