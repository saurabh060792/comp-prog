#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>

#define MAX 102
#define MOD 1000000007

using namespace std;

typedef long long int lli;

lli a[MAX];
lli dp[MAX][MAX];

int main()
{
	lli i,j,l,k,n;

	scanf("%lld",&n);
	for(i=0;i<n;i++) scanf("%lld",&a[i]);
	for(i=0;i<n;i++) if(i <= n-2 && a[i] < 0 && a[i] == -a[i+1]) dp[i][i+1] = 1;

	for(l=3;l<=n;l++) {
		for(i=0;i<n;i++) {
			j = l + i - 1;
			if(j>=n) break;
			dp[i][j] = (dp[i][j-1] + dp[i+1][j] - dp[i+1][j-1])%MOD;
			for(k=i+1;k<=j-2;k++)
				if(a[i] < 0 && a[i] == -a[k]) dp[i][j] = (dp[i][j] + ((1+dp[i+1][k-1])*(dp[k+1][j]-dp[k+1][j-1]))%MOD)%MOD;
			if(a[i] < 0 && a[i] == -a[j]) dp[i][j] = (dp[i][j] + 1 + dp[i+1][j-1])%MOD;
		}
	}
	dp[0][n-1]++;
	printf("%lld\n", dp[0][n-1]<0?dp[0][n-1]+MOD:dp[0][n-1]);
	return 0;
}