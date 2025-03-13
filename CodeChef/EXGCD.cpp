#include <cstdio>
#include <algorithm>

#define MOD 1000000007
#define MAX 200005
#define MAXK 5

using namespace std;

typedef long long int lli;

lli prime[MAX], phi[MAX], A[MAXK], B[MAXK];

void sieve();
lli mulInverse(lli a, lli b);

int main()
{
	int t,k;
	lli minB,p,q,i,j,cur;
	sieve();
	scanf("%d",&t);
	while(t--) {
		scanf("%d",&k);
		minB = MAX;
		q = 1;
		for(i=0;i<k;i++) {
			scanf("%lld%lld",&A[i],&B[i]);
			A[i]--;
			minB = min(minB, B[i]);
			q = (q* (B[i] - A[i]))%MOD;
		}
		p = 0;
		for(i=1;i<=minB;i++) {
			cur = phi[i];
			for(j=0;j<k;j++) cur = (cur * (B[j] / i - A[j] / i))%MOD;
			p = (p + cur) % MOD;
		}
		printf("%lld\n",(p*(mulInverse(MOD-q, MOD)))%MOD);
	}
	return 0;
}


void sieve()
{
	int i,j;
	for(i=1;i<MAX;i++) phi[i] = i;
	for(i=2;i<MAX;i++)
		if(!prime[i])
			for (j=i;j<MAX;j+=i) {
				prime[j] = 1;
				phi[j] = phi[j] / i * (i - 1);
			}
}

lli mulInverse(lli a, lli b)
{
	lli b0 = b, t, q, x0 = 0, x1 = 1;
	if(b==1) return 1;
	while(a>1) {
		q = a / b;
		t = b, b = a % b, a = t;
		t = x0, x0 = x1 - q * x0, x1 = t;
	}
	if(x1<0) x1 += b0;
	return x1;
}