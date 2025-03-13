#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>

#define MAXNUM 1000006
#define MAX 100005
#define MAXFACTOR 30

using namespace std;

int prime[MAXNUM], coprime[MAXNUM], a[MAX], dp[MAX], factor[MAXNUM][MAXFACTOR], factorIndex[MAXNUM];

void sieve();
int calc(int *A, int n, int idx);

int main()
{
	int t,n,i,maximum,j;
	scanf("%d",&t);
	sieve();

	while(t--) {
		scanf("%d",&n);
		for(i=1;i<=n;i++) scanf("%d",&a[i]);
		memset(coprime, 0, sizeof(coprime));

		dp[0] = 0;
		for(i=1;i<=n;i++) dp[i] = min(dp[i-1]+1, i-calc(a,n,i));

		maximum = 0;
		for(i=1;i<=n;i++)maximum = max(maximum, dp[i]);

		if(maximum == 1) printf("-1\n");
		else printf("%d\n",maximum);

	}
	return 0;
}

void sieve()
{
	int i,j;
	factor[1][0] = 1;;
	for(i=2;i<=MAXNUM;i++) {
		if(!prime[i]) {
			for(j=i;j<MAXNUM;j+=i) {
				factor[j][factorIndex[j]] = i;
				factorIndex[j]++;
				prime[j] = 1;
			}
		}
	}
}

int calc(int *A, int n, int idx)
{
	int i,ans=0;
	for(i=0;i<factor[A[idx]][i]!=0;i++) {
		ans = max(ans, coprime[factor[A[idx]][i]]);
		coprime[factor[A[idx]][i]] = idx;
	}
	return ans;
}