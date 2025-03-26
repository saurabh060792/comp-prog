#include <cstdio>
#include <algorithm>

#define MAXK 12
#define MAXN 22
#define MAXSET (1<<12)
#define INF (1<<30)

using namespace std;

typedef long long int lli;

int dp[MAXSET][MAXN];

int main()
{
	int cost[MAXK][MAXN]={},s,n,k,i,j,minimum=INF,m;
	scanf("%d%d",&n,&k);
	for(i=1;i<=k;i++)
		for(j=1;j<=n;j++) {
			scanf("%d",&cost[i][j]);
			if(j!=1) cost[i][j] += cost[i][j-1];			
		}

	for(s=0;s<(1<<k);s++)
		for(i=1;i<=n;i++)
			dp[s][i] = INF;

	for(i=0;i<(1<<k);i++) dp[i][0] = 0;

	for(s=1;s<(1<<k);s++) {
		for(j=0;j<k;j++) {
			if(( s & (1<<j) )!=0) {
				dp[s][1] = min(dp[s][1], cost[j+1][1]);
			}
		}
	}	


	for(s=1;s<(1<<k);s++) {
		for(i=1;i<=n;i++) {
			for(j=0;j<k;j++) {
				if( ( s & (1<<j) )!=0) {
					for(m=i;m>=0;m--) {
						dp[s][i] = min(dp[s][i], dp[s^(1<<j)][m] + cost[j+1][i] - cost[j+1][m]);
					}
				}
			}
		}
	}

	for(i=1;i<(1<<k);i++)
		minimum = min(minimum, dp[i][n]);

	printf("%d\n",minimum);


	return 0;
}