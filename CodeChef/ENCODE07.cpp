#include <cstdio>
#include <algorithm>

using namespace std;

#define MAXN 100010

typedef long long int lli;
 
int phi[MAXN], mu[MAXN];

void sieve();
 
int main()
{
	int t,i,j,count;
	lli ans,n;
	sieve();
	scanf("%d",&t);
	while(t--) {
		scanf("%lld",&n);
		ans = n*n;
		for(i=2;i<=n;i++)
			if(mu[i] != 0) {
				count = 0;
				for(j=i;j<=n;j+=i)
						if(mu[j] != 0)	count++;
				ans += (mu[i] * count * count);
			}
		printf("%lld\n",ans);
	}
	return 0;
}

void sieve()
{
	int i,j;
	for(i=2;i<MAXN;i++)
		if (!phi[i]) { 
			j = i;
			while(j <= MAXN) {
				if(!phi[j]) phi[j] = i;
				j += i;			
			}
		} 	
 	for(i=1;i<MAXN;i++)
		if(i==1) mu[i] = 1;
		else if(phi[i / phi[i]] == phi[i]) mu[i] = 0;
		else mu[i] = -1 * mu[i / phi[i]];
}