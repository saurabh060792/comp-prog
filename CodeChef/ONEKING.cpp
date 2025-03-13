#include <cstdio>
#include <algorithm>

#define MAX 100005

using namespace std;

pair<int, int> interval[MAX];
int dp[MAX];

bool comp(pair<int, int> a, pair<int, int> b);

int main()
{
	int t,n,i,rb;
	scanf("%d",&t);
	while(t--) {
		scanf("%d",&n);
		for(i=0;i<n;i++) scanf("%d%d",&interval[i].first, &interval[i].second);
		sort(interval, interval+n, comp);
		rb = interval[0].second;
		dp[0] = 1;
		for(i=1;i<n;i++) {
			if(rb>=interval[i].first) dp[i] = dp[i-1];
			else {
				dp[i] = dp[i-1] + 1;
				rb = interval[i].second;
			}
		}
		printf("%d\n",dp[n-1]);
	}
	return 0;
}

bool comp(pair<int, int> a, pair<int, int> b)
{
	return a.second<b.second;
}