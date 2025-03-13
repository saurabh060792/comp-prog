#include <cstdio>
#include <algorithm>
#include <cstring>

#define MAX 1003

using namespace std;

typedef long long int lli;

lli dp[MAX][MAX], ball[MAX][MAX], sum[MAX][MAX];

int main()
{
	int i,j,n;
	while(1) {
		scanf("%d",&n);
		if(n==0) break;
		memset(ball, 0, sizeof(ball));
		memset(dp, 0, sizeof(dp));
		memset(sum, 0, sizeof(sum));

		for(i=1;i<=n;i++) {
			for(j=1;j<=i;j++) scanf("%lld",&ball[i][j]);
		}

		for(i=1;i<=n;i++) {
			for(j=1;j<=n-i+1;j++) {
				sum[i][j] = sum[i][j-1] + ball[i+j-1][i];
			}
		}

		dp[n][0] = 0;
		dp[n][1] = max(sum[n][1], dp[n][0]);
		dp[n][2] = dp[n][1];
		for(i=n-1;i>=1;i--) {
			for(j=1;j<=n-i+1;j++) {
				dp[i][j] = max(dp[i+1][j]+sum[i][j], dp[i][j-1]);
			}
			dp[i][j] = dp[i][j-1];
		}

		printf("%lld\n",dp[1][n]);
	}
	return 0;
}
