#include <cstdio>
#include <algorithm>

#define MAX 10000007
#define MOD 1000000007
using namespace std;

typedef long long int lli; 

int A[MAX];

lli powMod(lli a, lli b, lli m);
void init(lli i, lli n);
void precompute(lli m, lli n);

int main()
{
	lli n, m, l, r, i, j, k, ans;
	int t;
	A[1] = 1;
	scanf("%d",&t);
	while(t--) {
		scanf("%lld%lld%lld%lld",&n,&m,&l,&r);
		precompute(m, n);
		ans = 0;
		for(i=r;i>=l;i=k) {
			j = m/i;
			k = m/(j+1);
			if(k < l-1) k=l-1;
			ans = (ans + (((i-k)* A[j]) % MOD)) % MOD;
		}
		printf("%lld\n",ans);
	}
	return 0;
}

lli powMod(lli a, lli b, lli m)
{
	lli i=a,k=1;
	while(b) {
		if(b&1) k = (k*i) % m;
		i = (i*i) % m;
		b >>= 1;
	}
	return k;
}


void init(lli i, lli n)
{
	lli present = 0,j,k,l;
	for(j=i,k=0,l=0;j>1;j=l) {
		k = i/j; 
		l = i/(k+1);
		present = (present +  (((j-l) * A[k]) % MOD)) % MOD;
	}
	A[i] = (powMod(i, n, MOD) - present + MOD) % MOD;
}

void precompute(lli m, lli n)
{
	lli i;
	for(i=2;i*i<=m;i++) init(i, n);
	for(;i>0;i--)init(m/i, n);
}