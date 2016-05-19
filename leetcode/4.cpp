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

			return findMedianNum(nums1, 0, nums1.size()-1, nums2, 0, nums2.size()-1);
		}

		double findMedianNum(const IntVec& leftNums, int leftStart, int leftEnd, 
				const IntVec& rightNums, int rightStart, int rightEnd)
		{
			int leftSize = leftEnd - leftStart + 1;
			int rightSize = rightEnd - rightStart + 1;
			if(leftStart >= leftEnd)
			{
				int rightMedPos = rightStart + (rightSize+1)/2-1;
				int rightRst = rightNums[rightMedPos];
				if(leftStart == leftEnd)
				{
					if(rightRst >= leftNums[leftStart])
					{
						return rightRst;
					}
					else if(leftNums[leftStart] >= rightNums[rightMedPos+1])
					{
						return rightNums[rightMedPos+1];
					}
					else
					{
						return leftNums[leftStart];
					}
				}
				else
				{
					return rightRst;
				}
			}

			if(rightStart >= rightEnd)
			{
				int leftMedPos = leftStart + (leftSize+1)/2-1;
				int leftRst = leftNums[leftMedPos];
				if(rightStart == rightEnd)
				{
					if(leftRst >= rightNums[rightStart])
					{
						return leftRst;
					}
					else if(rightNums[rightStart] >= leftNums[leftMedPos+1])
					{
						return leftNums[leftMedPos+1];
					}
					else
					{
						return rightNums[rightStart];
					}
				}
				else
				{
					return leftRst;
				}
			}

			int medianPos = (leftSize+rightSize-1)/2;
			if(leftNums[leftEnd] < rightNums[rightStart])
			{
				printf(" that.%d, %d\n", leftNums[leftEnd], rightNums[rightStart]);
				if(leftSize >= rightSize)
				{
					return leftNums[leftStart+medianPos];
				}
				else
				{
					return rightNums[rightStart+medianPos-leftSize];
				}
			}
			else if(rightNums[rightEnd] < leftNums[leftStart])
			{
				printf(" here.%d, %d\n", rightNums[rightEnd], leftNums[leftStart]);
				if(leftSize <= rightSize)
				{
					return rightNums[rightStart+medianPos];
				}
				else
				{
					return leftNums[leftStart+medianPos-rightSize];
				}
			}

			int leftMedianPos = leftStart + (leftEnd-leftStart + 1)/2;
			int leftMedian = leftNums[leftMedianPos];
			int rightMedianPos = rightStart + (rightEnd-rightStart + 1)/2;
			int rightMedian = rightNums[rightMedianPos];
			if(leftMedian < rightMedian)
			{
				printf("left: %d, %d, %d, %d\n", leftMedianPos, leftEnd, rightStart, rightEnd-(leftMedianPos-leftStart));
				return  findMedianNum(leftNums, leftMedianPos, leftEnd, 
						rightNums, rightStart, rightEnd-(leftMedianPos-leftStart));
			}
			else
			{
				printf("left: %d, %d, %d, %d\n", leftStart, leftEnd-(rightMedianPos-rightStart), rightMedianPos, rightEnd);
				return  findMedianNum(leftNums, leftStart, leftEnd-(rightMedianPos-rightStart), 
						rightNums, rightMedianPos, rightEnd);
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
	checkResult({17,18}, {2,3,5,10,19},10);
	checkResult({2,3,5,10,19}, {11,21,23,55}, 11);
 */
	checkResult({10,19}, {11}, 11);
	checkResult({11}, {10,19}, 11);
	checkResult({11,12}, {10,19}, 12);
	/*  
	checkResult({2,3,5,10,19}, {11,13,20,21,23,55}, 13);
	*/

	return 0;
}

