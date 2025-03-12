#include <cstdio>
#include <map>
#include <algorithm>

#define MAX 300048
#define MAXARRAY 200005

using namespace std;

typedef long long int lli;

lli read(lli x);
void update(lli x);

lli f[MAX], A[MAXARRAY];
map<lli, lli> m;

int main(void){
	lli ans, n, t, x, i;
	scanf("%lld", &t); 
	while(t--) {
		m.clear();
		ans = 0;
		scanf("%lld",&n);
		for(i=1;i<=n;i++){
			scanf("%lld",&A[i]);
			m[A[i]] = n - i + 1;
			f[i] = 0;
		}
		sort(A+1, A+n+1);
		for(i=1;i<=n;i++) {
			update(x = m[A[i]]);
			ans += read(x - 1);
		}
		printf("%lld\n",ans);
	}
	return 0;
}

lli read(lli x)
{
	lli sum = 0;
	for(; x; x -= (x & -x)) sum += f[x];
	return sum;
}

void update(lli x)
{
	for(; x < MAX; x += (x & -x)) ++f[x];
}