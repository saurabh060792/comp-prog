#include <iostream>
#include <cstdio>
#include <algorithm>

#define MAX 1000006
#define MAXGAME 51
using namespace std;

typedef long long int lli;

lli dp[MAX];

int main()
{
	lli k,l,m,i;
	scanf("%lld%lld%lld",&k,&l,&m);
	dp[0] = 0;
	dp[1] = dp[k] = dp[l] = 1;
	for(i=2;i<k;i++) dp[i] = dp[i-1]?0:1;
	for(i=k+1;i<l;i++) dp[i] = dp[i-1]&&dp[i-k]?0:1;
	for(i=l+1;i<MAX;i++) dp[i] = dp[i-1]&&dp[i-k]&&dp[i-l]?0:1;
	for(i=0;i<m;i++) {
		scanf("%lld",&k);
		if(dp[k]) printf("A");
		else printf("B");
	}
	printf("\n");
	return 0;
}