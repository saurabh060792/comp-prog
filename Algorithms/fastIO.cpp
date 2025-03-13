#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstdlib>
#include <cstring>


using namespace std;

int read_int();

int main()
{
	return 0;
}

int read_int()
{
	register int x = 0, c = getchar_unlocked();
	int sign = 1;
	while(c!='-' && (c<48 || c>57) ) c = getchar_unlocked();
	if(c=='-') sign = -1, c = getchar_unlocked();
	while(c>=48 && c<=57) x = (x<<1) + (x<<3) + c - 48, c = getchar_unlocked();
	return sign*x;
}