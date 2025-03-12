#include <cstdio>

#define MOD 1000000007
#define MAX 100005

using namespace std;

char s[MAX];
int dp[MAX], last[26];

int main()
{
	int i,t;
	scanf("%d", &t);
	dp[0] = 1;
	while(t--) {
		for(i=0;i<26;i++) last[i] = 0;
		scanf("%s",s+1);

		for(i=1;s[i];i++) {
			dp[i] = (2*dp[i-1])%MOD;
			if(last[s[i]-'A']) dp[i] -= dp[last[s[i]-'A'] - 1];
			if(dp[i] < 0) dp[i] += MOD;
			else if(dp[i] >= MOD) dp[i] -= MOD;
			last[s[i]-'A'] = i;
		}
		printf("%d\n", dp[--i]);
	}
	return 0;
}