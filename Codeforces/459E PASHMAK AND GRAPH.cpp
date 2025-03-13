#include <iostream>
#include <vector>

#define MAX 300005

using namespace std;


vector<pair<int, int> > w[MAX];
int dp[MAX], tmp[MAX];

int main()
{
	int n, m, u, v, len, ans, i, j;
	cin>>n>>m;
	for(i=0;i<m;i++) {
		cin>>u>>v>>len;
		w[len].push_back(make_pair(u, v));
	}

	for(i=0;i<MAX;i++) {
		for(j=0;j<w[i].size();j++) {
			v = w[i][j].second;
			tmp[v] = 0;
		}
		for(j=0;j<w[i].size();j++) {
			u = w[i][j].first;
			v = w[i][j].second;
			tmp[v] = max(tmp[v], dp[u] + 1);
		}
		for(j=0;j<w[i].size();j++) {
			u = w[i][j].first;
			v = w[i][j].second;
			dp[v] = max(dp[v], tmp[v]);
		}
	}
	ans = 0;
	for(i=1;i<=n;i++)
		ans = max(ans, dp[i]);
	cout<<ans<<endl;
	return 0;
}