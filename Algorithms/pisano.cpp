#include <cstdio>
#include <utility>
#include <algorithm>
#include <cstring>

using namespace std;

typedef long long int lli;

lli power(lli base, lli index);
void matrixMultiply(lli a[][2], lli b[][2], lli mod);
pair<lli, lli> findFib(lli index, lli mod);
lli findPeriod(lli p);
lli findPisanoPeriod(lli num);
lli gcd(lli a, lli b);


int main()
{
	lli t,m;
	scanf("%lld",&t);
	while(t--) {
		scanf("%lld",&m);
		printf("%lld\n",findPisanoPeriod(m));
	}
	return 0;
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

// http://www.jstor.org/stable/2309169?seq=1