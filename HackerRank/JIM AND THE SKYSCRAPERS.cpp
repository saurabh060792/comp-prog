#include <cstdio>
#include <algorithm>

#define MAX 500005

using namespace std;

typedef long long int lli;

lli up[MAX],left[MAX];

int main()
{
	lli n,i,ans,count[MAX];
	scanf("%lld",&n);
	for(i=1;i<=n;i++) scanf("%lld",&up[i]);
	for(i=1;i<=n;i++) {
		left[i] = i-1;
		while(left[i] > 0 && up[left[i]] < up[i]) {
			left[i] = left[left[i]];
		}
	}

	for(i=1;i<=n;i++) {
		if(left[i]>0 && up[left[i]] == up[i]) count[i] = count[left[i]]+1;
	}

	ans = 0;
	for(i=1;i<=n;i++) {
		if(left[i]>0 && up[left[i]] == up[i]) ans += count[i];
	}
	printf("%lld\n",2*ans);
	return 0;
}