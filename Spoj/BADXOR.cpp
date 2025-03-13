#include <iostream>
#include <cstdio>
#include <algorithm> 
#include <string.h> 

#define MOD 100000007

using namespace std;

typedef long long LL;

int dp[1025][1025];
//dp[i][j] -> ways to get xor value of j, using 
// first i elements of the array A

int A[1025], B[1025];
bool inB[1025];


int main()
{
	int a,ans,t,n,m,i,j,k;
	scanf("%d",&t);
	for(k=1;k<=t;k++) {
		scanf("%d%d",&n,&m);
		for(i=0;i<n;i++) scanf("%d",&A[i]);
		memset(inB,0,sizeof(inB));
		for(j=0;j<m;j++) {
			scanf("%d",&B[j]);
			inB[B[j]] = true;
		}
		memset(dp,0,sizeof(dp));
		
		dp[0][0] = 1;
		for(i=1;i<=n;i++) {
			a = A[i-1];
			for(j=0;j<1024;j++) {
				dp[i][j] = dp[i-1][j] + dp[i-1][j^a];
				if(dp[i][j]>=MOD)
					dp[i][j] -= MOD;
			}
		}
		
		ans = 0;
		for(j=0;j<1024;j++) {
			if(!inB[j]) {
				ans += dp[n][j];
				if(ans>=MOD) ans -= MOD;
			}
		}
		printf("Case %d: %d\n",k,ans);
	}
	return 0;
}