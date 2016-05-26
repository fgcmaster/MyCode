#include <stdlib.h>
#include <stdio.h>
#include <cctype>
#include <vector>
#include <iostream>

using namespace std;

typedef vector<int> IntVec;

class Solution
{
	enum State
	{
		Prepare,
		Symbol,
		Coef,
		OnlyDot,
		WithDot,
		AfterDot,
		Exp,
		ExpSymbol,
		AfterExp,
		End
	};

	public:
		bool isNumber(string s)
		{
			State curState = Prepare;
			for(auto ch: s)
			{
				if(curState == Prepare)
				{
					if(ch == '+' || ch == '-')
					{
						curState = Symbol;
					}
					else if(isdigit(ch))
					{
						curState = Coef;
					}
					else if(ch == '.')
					{
						curState = OnlyDot;
					}
					else if(ch != ' ')
					{
						return false;
					}
				}
				else if(curState == Symbol)
				{
					if(isdigit(ch))
					{
						curState = Coef;
					}
					else if(ch == '.')
					{
						curState = OnlyDot;
					}
					else
					{
						return false;
					}
				}
				else if(curState == Coef)
				{
					if(ch == 'e' || ch == 'E')
					{
						curState = Exp;
					}
					else if(ch == '.')
					{
						curState = WithDot;
					}
					else if(ch == ' ')
					{
						curState = End;
					}
					else if(!isdigit(ch))
					{
						return false;
					}
				}
				else if(curState == OnlyDot)
				{
					if(isdigit(ch))
					{
						curState = AfterDot;
					}
					else
					{
						return false;
					}
				}
				else if(curState == WithDot)
				{
					if(isdigit(ch))
					{
						curState = AfterDot;
					}
					else if(ch == ' ')
					{
						curState = End;
					}
					else if(ch == 'e' || ch == 'E')
					{
						curState = Exp;
					}
					else
					{
						return false;
					}
				}
				else if(curState == AfterDot)
				{
					if(ch == ' ')
					{
						curState = End;
					}
					else if(ch == 'e' || ch == 'E')
					{
						curState = Exp;
					}
					else if(!isdigit(ch))
					{
						return false;
					}
				}
				else if(curState == Exp)
				{
					if(isdigit(ch))
					{
						curState = AfterExp;
					}
					else if(ch == '+' || ch == '-')
					{
						curState = ExpSymbol;
					}
					else
					{
						return false;
					}
				}
				else if(curState == ExpSymbol)
				{
					if(isdigit(ch))
					{
						curState = AfterExp;
					}
					else
					{
						return false;
					}
				}
				else if(curState == AfterExp)
				{
					if(ch == ' ')
					{
						curState = End;
					}
					else if(!isdigit(ch))
					{
						return false;
					}
				}
				else if(curState == End)
				{
					if(ch != ' ')
					{
						return false;
					}
				}
			}
			if(curState == Coef || curState == AfterDot || curState == AfterExp 
					|| curState == End || curState == WithDot)
			{
				return true;
			}
			else
			{
				return false;
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

void checkResult(const string& s, bool target)
{
	Solution sol;
	bool result = sol.isNumber(s);
	if(result == target)
	{
		printf("\ttrue.\n");
	}
	else
	{
		printf("\tfalse, %d != %d, %s\n", result, target, s.c_str());
	}
}

int main()
{
	checkResult(" 0.1 ", true);
	checkResult("1 ", true);
	checkResult("2e10", true);
	checkResult(" 1a", false);
	checkResult(" 1.", true);
	checkResult(" 1.5", true);
	checkResult(" 1.5e10", true);
	checkResult(" +1.5e10", true);
	checkResult(" 1.5 a", false);
	checkResult(" 20e001 ", true);
	checkResult(".1", true);
	checkResult("3.", true);
	checkResult("3. ", true);
	checkResult(".", false);
	checkResult("+.8", true);
	checkResult("46.e3", true);
	checkResult("46.5e3", true);
	checkResult("005047e+6", true);
	checkResult("4e+", false);
	checkResult("4e- ", false);

	return 0;
}

