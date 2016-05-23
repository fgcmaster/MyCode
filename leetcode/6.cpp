#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <vector>
#include <iostream>

using namespace std;

typedef vector<int> IntVec;

class Solution
{
	public:
		string convert(string s, int numRows)
		{
			string resultStr;
			int strLen = s.size();
			resultStr.reserve(strLen);
			int eachSegNum = numRows+1;
			for(int i = 0; i < numRows;i++)
			{
				int columNum = 0;
				while(true)
				{
					int columPos = columNum*eachSegNum+i;
					if(columPos < strLen)
					{
						resultStr.push_back(s[columPos]);
					}
					else
					{
						break;
					}
					if(i == numRows-2)
					{
						int zigPos = (columNum+1)*eachSegNum-1;
						if(zigPos < strLen)
						{
							resultStr.push_back(s[zigPos]);
						}
						else
						{
							break;
						}
					}
					columNum++;
				}
			}
			return resultStr;
			/*  
			if(numRows == 1)
			{
				return s;
			}
			string resultStr;
			int strLen = s.size();
			resultStr.reserve(strLen);
			int eachSegNum = numRows*2-2;
			for(int i = 0; i < numRows;i++)
			{
				int columNum = 0;
				while(true)
				{
					int columPos = columNum*eachSegNum+i;
					if(columPos < strLen)
					{
						resultStr.push_back(s[columPos]);
					}
					else
					{
						break;
					}

					int zigNum = (columNum%2 == 0? numRows+i-1: eachSegNum-i);
					int zigPos = columNum*eachSegNum + zigNum;
					if(i != 0 && i != numRows-1 )
					{
						if(zigPos < strLen)
						{
							resultStr.push_back(s[zigPos]);
						}
						else
						{
							break;
						}
					}
					columNum++;
				}
			}
			return resultStr;
			*/

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

void checkResult(const string& leftNums, int numRows, const string& target)
{
	Solution sol;
	string result = sol.convert(leftNums, numRows);
	if(result == target)
	{
		printf("\ttrue.\n");
	}
	else
	{
		printf("\tfalse, %s != %s\n", result.c_str(), target.c_str());
	}
}

int main()
{
	checkResult("PAYPALISHIRING", 3,"PAHNAPLSIIGYIR");
	//checkResult("PAYPALISHIRING", 4,"PINAASIGYLHRPI");
	checkResult("PAY", 3,"PAY");
	checkResult("A", 1,"A");
	checkResult("ABCDE", 4,"ABCED");

	return 0;
}

