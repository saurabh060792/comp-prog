#include <cstdio>
#include <iostream>
#include <algorithm>

#define MOD 1000000007

using namespace std;

typedef long long int lli;

lli dp[105][105];
lli stirling(int n,int k);

int main()
{
	lli i,j,fact[1000],T,m,n;
	for(i=0 ; i< 105 ; i++)
		for(j= 0 ; j< 105 ; j++)
			dp[i][j] = -1;
	fact[0] = 1;
	for(i=1;i<400;i++) fact[i] = (fact[i-1]*i)%MOD;

	scanf("%lld",&T);
	for(i=1;i<=T;i++) {
		scanf("%lld%lld",&m,&n);
		printf("Case #%lld: %lld\n",i, (stirling(n,m)*fact[m])%MOD);
	}
	return 0;
}

lli stirling(int n,int k)
{
	if(dp[n][k] != -1) return dp[n][k];
	if (k == 1 || k == n) {
		dp[n][k] = 1;
		return 1;
	}
	dp[n][k] = (stirling(n-1,k-1) + k*stirling(n-1,k))%MOD;
	return dp[n][k];
}