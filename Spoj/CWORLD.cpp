#include <cstdio>
#include <algorithm>
#include <cstring>

#define MAX 102
#define INF 1000000000

using namespace std;

int dp[MAX][MAX], color[MAX][MAX], cost[MAX][MAX];

int main()
{
	int t,T,n,k,q,i,temp,j,p,maximum;
	scanf("%d",&T);
	for(t=1;t<=T;t++) {
		memset(color, 0, sizeof(color));
		memset(dp, 0, sizeof(dp));
		scanf("%d%d",&n,&k);
		for(i=0;i<n;i++) {
			scanf("%d",&q);
			while(q--) {
				scanf("%d",&temp);
				color[i][temp] = 1;
			}
		}
		for(i=1;i<=k;i++) for(j=1;j<=k;j++) scanf("%d",&cost[i][j]);
		for(i=1;i<=k;i++) if(!color[0][i]) dp[0][i] = -INF; 
		for(i=1;i<n;i++)
			for(j=1;j<=k;j++) {
				dp[i][j] = dp[i-1][j];
				if(!color[i][j]) continue;
				else for(p=0;p<=k;p++) dp[i][j] = max(dp[i][j], dp[i-1][p] + cost[p][j]);
			}
		maximum = -INF;
		for(i=0;i<=k;i++) maximum = max(dp[n-1][i], maximum);
		printf("Game %d: %d\n",t,maximum);
	}
	return 0;
}