#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

typedef long long int lli;

lli a[63];

lli func(lli x);

int main()
{
	int i,j;
	lli x, y;
	a[0] = 1;
	for(i=1;i<63;i++) {
		a[i] = 1LL << i;
		for(j=0;j<i;j++)
			a[i] += a[j];
	}
	scanf("%lld%lld",&x,&y);
	printf("%lld\n",func(y) - func(x - 1));
}

// f(0) = 1
// f(n) = (1 << n) + (f(0) + f(1) + f(2) + ... + f(n - 1))
lli func(lli x)
{
	lli res = 0, aux = 0;
	while (x) {
		if (x % 2) res += a[aux];
		x >>= 1;
		++aux;
	}
	return res;
}