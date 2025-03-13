#include <cstdio>
#include <cstring>
#include <algorithm>

#define MAX 204

using namespace std;

typedef long long int lli;

lli dp[MAX][MAX], catlan[MAX];

void solve();
void computeCatlan();

int main()
{
	int t,i,j,n,o;
	lli k;

	char p[MAX];
	computeCatlan();
	solve();

	scanf("%d",&t);
	for(int c=1;c<=t;c++){
		scanf("%d%lld",&n,&k);
		printf("Case #%d: ", c);
		if(k>dp[2*n][0]){
			printf("Doesn't Exist!\n");
			continue;
		}
		o = 0;
		for(i=1;i<=2*n;i++) {
			if(dp[2*n - i][o+1] >= k) {
				p[i] = '(';
				o++;
			}
			else {
				p[i] = ')';
				k -= dp[2*n - i][o+1];
				o--;
			}
		}
		for(i=1;i<=2*n;i++)
			printf("%c",p[i]);
		printf("\n");
	}
	return 0;
}

void solve()
{
	int i,j;
	for(i=1;i<MAX;i++) dp[i][0] = i%2?0:catlan[i/2];
	for(i=1;i<MAX;i++) dp[i][i] = 1;

	for(i=1;i<MAX-1;i++) {
		for(j=1;j<i;j++) {
			dp[i][j] = dp[i-1][j-1] + dp[i-1][j+1];
		}
	}
	return;
}

void computeCatlan()
{
	int i;
	catlan[0] = 1;
	for(i=1;i<MAX;i++) catlan[i] = (catlan[i-1] * 2 * (2*i - 1))/(i+1);
	return;
}