#include <stdlib.h>
#include <stdio.h>
#include <cmath>
#include <climits>
#include <vector>
#include <iostream>

using namespace std;

typedef vector<int> IntVec;

class Solution
{
	public:
		int myAtoi(string str)
		{
			bool isStart = true;
			int num = 0;
			int flag = 1;
			for(auto ch: str)
			{
				if(ch>= '0' && ch <= '9')
				{
					isStart = false;
					if((num > INT_MAX/10 || num*10 > INT_MAX - (ch-'0')))
					{
						return INT_MAX;
					}
					else if( num < INT_MIN/10 || num*10 < INT_MIN + ch-'0')
					{
						return INT_MIN;
					}
					if(flag == -1)
					{
						if(num > 0)
						{
							num = num*flag;
						}
						num = num*10 - (ch-'0');
					}
					else
					{
						num = num*10 + (ch-'0');
					}
				}
				else if(isStart)
				{
					if(ch == '+' )
					{
						isStart = false;
					}
					else if(ch == '-')
					{
						isStart = false;
						flag = -1;
					}
					else if(ch != ' ')
					{
						break;
					}
				}
				else
				{
					break;
				}
			}
			return num;
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

void checkResult(const string& str, int target)
{
	Solution sol;
	int result = sol.myAtoi(str);
	if(fabs(result - target) < 0.001)
	{
		printf("\ttrue.\n");
	}
	else
	{
		printf("\tfalse, %d != %d\n", result, target);
	}
}

int main()
{
	checkResult("23", 23);
	checkResult("0.5", 0);
	checkResult("0", 0);
	checkResult(" +34 a", 34);
	checkResult(" +-34 a", 0);
	checkResult(" -34", -34);
	checkResult(" 2147483648", 2147483647);
	checkResult(" 3147483648", 2147483647);
	checkResult("b11228552307", 0);
	printf("%d, %d\n", INT_MAX, atoi("3147483648"));

	return 0;
}

