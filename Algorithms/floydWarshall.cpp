#include <cstdio>
#include <algorithm>

#define MAX 252

using namespace std;

int dp[MAX][MAX];

int main()
{
	int n,i,j,k,q;
	scanf("%d",&n);
	for(i=0;i<n;i++)
		for(j=0;j<n;j++)
			scanf("%d",&dp[i][j]);
	scanf("%d",&q);
	for(k=0;k<n;k++)
		for(i=0;i<n;i++)
			for(j=0;j<n;j++)
				dp[i][j] = min(dp[i][j], dp[i][k]+dp[k][j]);
	return 0;
}