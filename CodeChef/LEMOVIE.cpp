#include <cstdio>
#include <cstring>

#define MAX 202
#define MOD 1000000007

typedef long long int lli;

int p[MAX],hash[MAX];
lli dp[MAX];

int main()
{
	int i,j,n,k,t,size;
	lli temp;
	scanf("%d",&t);
	while(t--) {
		memset(hash, 0, sizeof(hash));
		memset(dp, 0, sizeof(dp));
		dp[0] = 1;
		size = 0;
		scanf("%d%d",&n,&k);
		for(i=0;i<n;i++) {
			scanf("%d",&p[i]);
			hash[p[i]]++;
		}
		for(i=200;i>=0;i--) {
			if(hash[i]) {
				temp = 1;
				for(j=size+1;j<size+hash[i];j++) temp = (temp*j)%MOD;
				for(j=k;j>=0;j--) {
					dp[j+1] = (dp[j+1] + (((temp*dp[j])%MOD)*hash[i])%MOD)%MOD;
					dp[j] = (((dp[j]*temp)%MOD)*size)%MOD;
				}
				size += hash[i];
			}
		}
		temp = 0;
		for(i=0;i<=k;i++) temp = (temp + dp[i])%MOD;
		printf("%lld\n",temp);
	}
	return 0;
}