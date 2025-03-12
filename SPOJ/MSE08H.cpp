#include <cstdio>
#include <algorithm>

#define MAX 1003

using namespace std;

int phi[MAX], v[MAX];

int main()
{
	int n,i,j;
	long long int ans;
	while(scanf("%d", &n) == 1) {
		ans = 1;
		for(i=0;i<n;i++) scanf("%d",&v[i]);
		sort(v, v+n);
		for(i=0;i<n;i++) phi[i] = v[i];
		for(i=1;i<n;i++){
			if(phi[i] == v[i])
				for(j=i;j<n;j++)
					if(!(v[j] % v[i])){
						phi[j] /= v[i];
						phi[j] *= v[i] - 1;
					}
			ans = (ans * phi[i]) % 1000000007;
		}
		printf("%lld\n", ans);
	}
	return 0;
}

//Smith's Matrix gcd closed