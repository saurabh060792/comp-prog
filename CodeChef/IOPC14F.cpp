#include <cstdio>
#include <algorithm>
#include <cstring>

#define MAX 100005

using namespace std;

typedef long long int lli;

lli val[MAX], prime[MAX];

lli findPisanoPeriod(lli mod);
lli powMod(lli base, lli index, lli mod);
void powerCounter(lli num, lli add);
void sieve();
lli findFib(lli index, lli mod);
void matrixMultiply(lli a[][2], lli b[][2], lli mod);
lli mul(lli a, lli b, lli c);


int main() 
{
	lli i,temp,t,n,r,mod,period,ans;
	sieve();
	scanf("%lld",&t);
	while(t--) {
		scanf("%lld %lld %lld",&n,&r,&mod);
		period = findPisanoPeriod(mod);
		memset(val, 0, sizeof(val));
		for(i=2;i<=n;i++) powerCounter(i, 1);
		for(i=2;i<=r;i++) powerCounter(i, -1);
		for(i=2;i<=n-r;i++) powerCounter(i, -1);

		temp = 1;
		for(i=2;i<=n;i++) temp = mul(temp, powMod(i, val[i], period), period);

		ans = findFib(temp, mod);
		printf("%lld\n", ans);
	}
	return 0;
}

//(a*b)%c
lli mul(lli a, lli b, lli c)
{
	lli d = 0;
	a %= c;
	b %= c;
	while (b > 0) {
		if (b & 1) {
			d += a;
			if (d >= c) d -= c;
		}
		b >>= 1;
		a <<= 1;
		if (a >= c) a -= c;
	}
	return d;
}

lli findPisanoPeriod(lli mod)
{
	lli period = 1,i;
	for(i=2;i * i<=mod;i++)
		if(mod % i == 0) {
		if(i==2) period *= 3; 
		else if(i==5) period *= 20;
		else period *= (i - 1) * (i + 1);
		mod /= i;
		while(mod % i == 0) {
			period *= i;
			mod /= i;
		}
	}
	if (mod > 1) {
		i = mod;
		if(i==2) period *= 3;
		else if(i==5) period *= 20;
		else period *= (i - 1) * (i + 1);
	}
	return period;
}

lli powMod(lli base, lli index, lli mod)
{
	if(index<=0) return 1;
	else if(index==1) return base%mod;
	lli temp;
	if(index%2) { //odd
		return mul(base, powMod(base, index-1, mod), mod);
	}
	else { //even
		temp = powMod(base, index/2, mod);
		return mul(temp, temp, mod);
	}
}

void powerCounter(lli num, lli add)
{
	lli curr;
	while(num > 1) {
		curr = prime[num];
		while(num % curr == 0) {
			val[curr] += add;
			num /= curr;
		}
	}
}

void sieve()
{
	lli i,j;
	for(i=1;i<MAX;i++) prime[i] = i;
	for(i=2;i * i<MAX;i++)
		if(prime[i] == i)
			for(j=2*i;j<MAX;j+=i)
				prime[j] = i;
}

void matrixMultiply(lli a[][2], lli b[][2], lli mod)
{
	lli spare[2][2]={0},i,j,k;
	for(i=0;i<2;i++)
		for(j=0;j<2;j++){
			spare[i][j] = 0;
			for(k=0;k<2;k++)
				spare[i][j] = (spare[i][j] + a[i][k] * b[k][j]) % mod;
		}
	memcpy(a, spare, sizeof(spare));
}

lli findFib(lli index, lli mod)
{
	if(index == 0) return 0;
	if(index == 1) return 1;
	index--;
	lli res[2][2], temp[2][2];
	res[0][0] = res[1][1] = temp[0][0] = temp[0][1] = temp[1][0] = 1;
	res[0][1] = res[1][0] = temp[1][1] = 0;
	while(index) {
		if(index & 1) matrixMultiply(res, temp, mod);
		matrixMultiply(temp, temp, mod);
		index >>= 1;
	}
	return res[0][0];
}