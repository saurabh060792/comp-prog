#include <cstdio>
#include <map>
#include <algorithm>
#include <utility>

#define MAX 80048
#define MAXARRAY 50004

using namespace std;

typedef long long int lli;

lli read(lli x);
void update(int idx ,int val);

lli f[MAX], A[MAXARRAY], D[MAXARRAY], result[MAXARRAY];
pair<lli, lli> p[MAXARRAY];

int main(void){
	lli i,n;

	scanf("%lld",&n);
	for(i=1;i<=n;i++) {
		scanf("%lld",&A[i]);
		p[i].first = A[i];
		p[i].second = i;
		update(i, 1);
	}
	sort(p+1, p+n+1);
	D[1] = p[1].first;
	for(i=2;i<=n;i++) D[i] = D[i-1] + p[i].first;

	// for(i=1;i<=n;i++) printf("%lld  ",D[i]);
	// printf("\n");
	// for(i=1;i<=n;i++) printf("%lld %lld\n",p[i].first, p[i].second);
	// printf("\n");

	for(i=1;i<=n;i++) {
		result[p[i].second] = D[i-1] + (n-i+1)*p[i].first + read(p[i].second - 1) - n + i;
		update(p[i].second, -1);
	}
	for(i=1;i<=n;i++) printf("%lld\n",result[i]);
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
	for(; x < MAX; x += (x & -x)) --f[x];
}

void update(int idx ,int val)
{
	while(idx <= MAX){
		f[idx] += val;
		idx += (idx & -idx);
	}
}