#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <iostream>

using namespace std;

typedef vector<int> IntVec;

class Solution
{
	public:
		int KKK(vector<int>& nums) 
		{
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
	int result = sol.KKK(leftNums);
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
	checkResult({}, );

	return 0;
}

