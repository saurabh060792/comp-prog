#include <cstdio>
#include <algorithm>
#include <cstring>
#include <functional>

#define MAX 100005

using namespace std;

struct myCompare
{
	bool operator() (pair<int, int> a, pair<int, int> b) {
		return a.second==b.second?a.first<b.first:a.second<b.second;
	}
};

pair<int, int> interval[MAX];
int dp[MAX];

int main()
{
	int t,i,n,j;
	scanf("%d",&t);
	while(t--) {
		scanf("%d",&n);
		for(i=1;i<=n;i++) scanf("%d%d",&interval[i].first, &interval[i].second);
		memset(dp, 0, sizeof(dp));
		dp[0] = 0;
		dp[1] = 1;
		sort(interval+1, interval+n+1, myCompare());
		for(i=2;i<=n;i++) {
			j = upper_bound(interval+1, interval+i+1, make_pair(interval[i].first, interval[i].first), myCompare()) - interval;
			dp[i] = max(dp[i-1], dp[j-1]+1);
		}
		printf("%d\n",dp[n]);
	}
	return 0;
}