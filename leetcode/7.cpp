#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <cmath>
#include <climits>
#include <iostream>

using namespace std;

typedef vector<int> IntVec;

class Solution
{
	public:
		int reverse(int num) 
		{
			bool isNeg = (num < 0);
			int number = abs(num);
			int resultNum = 0;
			while(true)
			{
				if(resultNum > INT_MAX/10 || resultNum*10 > INT_MAX - number%10)
				{
					return 0;
				}
				resultNum = resultNum*10 + number%10;
				if(number < 10)
				{
					break;
				}
				number = number/10;
			}
			return isNeg ? -1*resultNum: resultNum;
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

void checkResult(int leftNums, int target)
{
	Solution sol;
	int result = sol.reverse(leftNums);
	if(fabs(result - target) < 0.001)
	{
		printf("\ttrue.\n");
	}
	else
	{
		printf("\tfalse, %d != %d\n", result, target);
		//printArray(leftNums);
	}
}

int main()
{
	/* 	checkResult(123, 321);
	checkResult(-123, -321);
	checkResult(-120, -21);
	checkResult(-1, -1);
	checkResult(2, 2);
	checkResult(20, 2);
	checkResult(0, 0);
 */

	printf("%d, %d, %u\n", INT_MAX, INT_MIN, UINT_MAX);
	checkResult(1534236469, 0);

	return 0;
}

