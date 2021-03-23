
#include <iostream>
#include <string>
using namespace std;

int mult(unsigned int m, unsigned int n)
{
	if (n == 0)
	{
		return 0;
	}
		else
		{
			return m + mult(m, n - 1);
		}

}

int countDigit(int num, int digit)
{

	if (num == 0)
	{
		return 0;
	}

	int extract = 0;
	extract = num % 10;

			if (extract == digit)
			{
				return 1 + countDigit(num / 10, digit);
			}
				else
				{
					return 0 + countDigit(num / 10, digit);
				}

}

string pairMinus(string n)
{
	if (n.size() == 1)
	{
		return n;
	}
		else if (n[0] == n[1]) 
		{
			return n.substr(0, 1) + "--" + pairMinus(n.substr(1, n.size() - 1));
		}

			else 
			{
				return n.substr(0, 1) + pairMinus(n.substr(1, n.size() - 1));
			}
}



string findParen(string str)
{
	if (str.substr(0, 1) != "(") 
	{
		return findParen(str.substr(1, str.size() - 1)); 
	}
		
		else if (str.substr(str.size() - 1, 1) != ")") 
		{
			return findParen(str.substr(0, str.size() - 1)); 
		}

			return str; 
}


bool combinationSum(const int a[], int size, int target)
{
	if (target == 0)
	{
		return true;
	}
		if (target != 0 && size == 0)
		{
			return false;
		}
		size--;

			return (combinationSum(a, size, target) || combinationSum(a, size, target - a[size]));
}


bool pathPresent(string maze[], int nRows, int nCols, int sr, int sc, int er, int ec)
{
	if (sr == er && sc == ec && maze[sr][sc] == '.') 
	{
		return true;
	}


			if (maze[sr][sc] == '@' || maze[sr][sc] == 'X' || maze[sr][sc] == 'V') 
			{
				return false;
			}
				if (maze[sr][sc] == '.') 
				{
					maze[sr][sc] = 'V';

					if (pathPresent(maze, nRows, nCols, sr - 1, sc, er, ec)) 
					{
						return true;
					}
						if (pathPresent(maze, nRows, nCols, sr + 1, sc, er, ec)) 
						{
							return true;
						}
						if (pathPresent(maze, nRows, nCols, sr, sc - 1, er, ec))
						{
							return true;
						}
							if (pathPresent(maze, nRows, nCols, sr, sc + 1, er, ec)) 
							{
								return true;
							}

								return false;
				}
	return false;

}

