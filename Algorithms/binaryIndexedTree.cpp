#include <iostream>
#include <cstdio>
#include <algorithm>

#define MAXARRAY 100000
#define MAXTREE 100000

using namespace std;

int queryBIT(int idx);
void updateBIT(int idx ,int val);

int bit[MAXTREE];

int main()
{

	return 0;
}

void buildBIT(int *A, int n)
{
	int i;
	for(i=0;i<n;i++) updateBIT(i+1, A[i]);
}

int queryBIT(int idx)
{
	int sum = 0;
	while(idx > 0) {
		sum += bit[idx];
		idx -= (idx & -idx);
	}
	return sum;
}

void updateBIT(int idx ,int val)
{
	while(idx <= MAXTREE){
		bit[idx] += val;
		idx += (idx & -idx);
	}
}