#include <iostream>
#include <cstdio>
#include <algorithm>

#define MAX 16

using namespace std;

typedef long long int lli;

lli factorial(lli n);
int main()
{
	lli sum1,sum2,k,i,n,h1[MAX],h2[MAX];
	while(1) {
		sum1 = sum2 = 0;
		scanf("%lld",&n);
		for(i=0;i<n;i++) {
			scanf("%lld",&h1[i]);
			h2[i] = h1[i];
		}
		if(n==0) break;
		sort(h1,h1+n,greater<lli>());
		sort(h2,h2+n);
		k = n/2;
		if(n%2) {
			for(i=0;i<=k;i++) sum1 += h1[i];
			for(i=0;i<k;i++) sum2 += h2[i];
			printf("%lld %lld\n",(sum1-sum2+n)*2, factorial(k+1)*factorial(k));
		}
		else {
			for(i=0;i<=k;i++) sum1 += h1[i];
			for(i=0;i<k;i++) sum2 += h2[i];
			printf("%lld %lld\n",(sum1-sum2+n)*2, factorial(k)*factorial(k)*2);	
		}
	}
	return 0;
}


lli factorial(lli n)
{
	lli i,fact=1;
	for(i=1;i<=n;i++) fact *= i;
	return fact;
}