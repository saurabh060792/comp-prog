#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>

#define MAX 10004

using namespace std;

typedef long long int lli;

int grundy[MAX],mex[MAX];

void solve();

int main()
{
	int t,n;
	solve();
	scanf("%d",&t);
	while(t--) {
		scanf("%d",&n);
		printf("%s\n",grundy[n]>0?"Arjuna":"Bhima");
	}
	return 0;
}

void solve()
{
	int i,x,y,g;
	grundy[0] = grundy[1] = 0;
	grundy[2] = grundy[3] = 1;
	for(i=4;i<MAX;i++) {
		grundy[i] = 0;
		memset(mex, 0, sizeof(mex));
		x = 0;
		y = i-2;
		while(x<=y) {
			mex[grundy[x]^grundy[y]] = 1;
			x++;
			y--;
		}
		for(g=0;mex[g];g++);
		grundy[i] = g;
	}
}