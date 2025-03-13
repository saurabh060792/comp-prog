#include <iostream>
#include <cstdio>
#include <algorithm>

#define MAX 3003

using namespace std;

typedef long long int lli;

int main()
{
	lli t, n, a[MAX], s[MAX], i, k, m, s1, s2;
	scanf("%lld", &t);
	while(t--){
		scanf("%lld%lld", &n, &k);
		for(i=1;i<=n;i++) scanf("%lld", &a[i]);
		sort(a+1, a+n+1);
		s[0] = a[0] = 0;
		s[1] = a[1];
		for(i=2;i<=n;i++) s[i] = s[i-1]+a[i];
		m = (lli)1000000*(lli)1000000;
		for(i=0;i<=k;i++){
			s1 = s[i] + a[i]*(n-i);
			s2 = (s[n] - s[n-k+i]) - (k-i)*a[i];
			m = min(m, s1+s2);
		}
		printf("%lld\n", m);
	}
	return 0;
}