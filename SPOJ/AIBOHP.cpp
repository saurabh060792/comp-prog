#include <cstdio>
#include <cstring>
#include <algorithm>

#define MAX 6116

using namespace std;

int dp[2][MAX];
char s[MAX];

int main()
{
	int t,n,i,j,k;
	scanf("%d",&t);
	while(t--) {
		scanf("%s",s);
		n = strlen(s);
		memset(dp, 0, sizeof(dp));
		for(i=1;i<=n;i++) {
			for(j=1,k=n;j<=n;j++,k--) {
				if(s[i-1] == s[k-1]) dp[i%2][j] = dp[((i%2)+1)%2][j-1] + 1;
				else dp[i%2][j] = max(dp[i%2][j-1], dp[((i%2)+1)%2][j]);
			}
		}
		printf("%d\n",n-dp[n%2][n]);
	}
	return 0;
}