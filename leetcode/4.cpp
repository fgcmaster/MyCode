#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

typedef vector<int> IntVec;

class Solution
{
	public:
		double findMedianSortedArrays(const vector<int>& nums1, const vector<int>& nums2)
		{
			if(nums1.empty())
			{
				return nums2[nums2.size()/2];
			}
			if(nums2.empty())
			{
				return nums1[nums1.size()/2];
			}
			int totalNum = nums1.size() + nums2.size();
			if(totalNum%2 == 1)
			{
				return findMedianNum(nums1, 0, nums2, 0, totalNum/2);
			}
		}

		int findMedianNum(const IntVec& lNums, int lStart, const IntVec& rNums, int rStart, int kNum)
		{
			if(kNum == 0)
			{
				return min(lNums[lStart], rNums[rStart]);
			}
			else if(kNum == 1)
			{
				return max(lNums[lStart], rNums[rStart]);
			}

			int medPos = kNum/2;
			int lSize = lNums.size() - lStart;
			int rSize = rNums.size() - rStart;
			if(lSize < medPos)
			{
				return max(rNums[rStart+kNum-lSize],lNums[lNums.size()-1]);
			}
			else if(rSize < medPos)
			{
				return max(lNums[lStart+kNum-rSize],rNums[rNums.size()-1]);
			}

			if(lNums[lStart+medPos] < rNums[rStart+medPos])
			{
				return findMedianNum(lNums, lStart+medPos, rNums, rStart, kNum-medPos);
			}
			else if(rNums[rStart+medPos] < lNums[lStart+medPos])
			{
				return findMedianNum(lNums, lStart, rNums, rStart+medPos, kNum-medPos);
			}
			else
			{
				return lNums[medPos];
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

void checkResult(const IntVec& leftNums, const IntVec& rightNums, int target)
{
	Solution sol;
	double result = sol.findMedianSortedArrays(leftNums, rightNums);
	if(fabs(result - target) < 0.001)
	{
		printf("\ttrue.\n");
	}
	else
	{
		printf("\tfalse, %f != %d\n", result, target);
		printArray(leftNums);
		printArray(rightNums);
	}
}

int main()
{
	/* 	checkResult({}, {2,3,5,7,9}, 5);

	checkResult({2,3,5,7,9},{} , 5);
	checkResult({10,23,55}, {2,3,5,7,9},7);
	checkResult({2,3,5,10,19}, {17}, 10);
	checkResult({17}, {2,3,5,10,19},10);
 */
	checkResult({17,18}, {2,3,5,10,19},10);
	checkResult({2,3,5,10,19}, {11,21,23,55}, 11);
	checkResult({10,19}, {11}, 11);
	checkResult({11}, {10,19}, 11);
	checkResult({2,3,5,10,19}, {11,13,20,21,23,55}, 13);
	/*  
	checkResult({11,12}, {10,19}, 12);
	*/

	return 0;
}

