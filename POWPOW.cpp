#include <cstdio>
#include <iostream>
#include <algorithm>

#define MAX 100005
#define MOD1 1000000007
#define MOD2 500000003

using namespace std;

typedef long long int lli;

lli CRT(lli *n, lli *a, lli size);
lli mulInverse(lli a, lli b);
void f();
lli powMod(lli a, lli b, lli m);

lli C[MAX];

int main()
{
	lli t,a,b,n,primes[] = {2, MOD2}, coef[2];
	scanf("%lld",&t);
	f();
	while(t--) {
		scanf("%lld%lld%lld",&a,&b,&n);
		coef[0] = (b>0?(n==0?1:0) : 1);
		coef[1] = powMod(C[n], b, MOD2);
		printf("%lld\n",powMod(a,CRT(primes, coef, 2),MOD1));
	}
	return 0;
}

lli powMod(lli a, lli b, lli m)
{
	lli temp;
	if(b==0) return 1;
	if(b==1) return a%m;
	if(b%2) return (a*powMod(a,b-1,m))%m;
	else {
		temp = powMod(a,b/2,m);
		return (temp * temp)%m;
	}
}

void f()
{
	int i;
	C[0] = 1;
	for(i=1;i<MAX;i++) C[i] = ((((C[i-1]*2)*(2*i-1))%MOD2) * mulInverse(i, MOD2))%MOD2;
}
 
// returns x where (a * x) % b == 1
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

lli CRT(lli *n, lli *a, lli size)
{
	lli p, i, prod = 1, sum = 0;
	for(i=0;i<size;i++) prod *= n[i];
	for(i=0;i<size;i++) {
		p = prod / n[i];
		sum += a[i] * mulInverse(p, n[i]) * p;
	}
	return sum % prod;
}
 