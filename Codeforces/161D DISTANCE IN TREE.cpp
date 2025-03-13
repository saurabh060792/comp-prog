#include <cstdio>
#include <algorithm>
#include <vector>

#define MAXNODE 50004
#define MAXK 502

using namespace std;

typedef long long int lli;

lli dp[MAXNODE][MAXK], sum;
int n, k;
vector<int> tree[MAXNODE];

void dfs(int u, int p);

int main()
{
	int u, v;
	scanf("%d %d", &n, &k);
	sum=0;
	for(int i=0;i<n-1;i++){
		scanf("%d %d", &u, &v);
		tree[u].push_back(v);
		tree[v].push_back(u);
	}
	for(int i=0;i<=n;i++) dp[i][0]=1;
	dfs(1, 0);
	printf("%lld\n", sum/2);
	return 0;
}

void dfs(int u, int p)
{
	for(int i=0;i<tree[u].size();i++){
		if(tree[u][i]!=p){
			dfs(tree[u][i], u);
			for(int j=1;j<=k;j++){
				dp[u][j]+=dp[tree[u][i]][j-1];
			}
		}
	}
	sum+=2*dp[u][k];
	for(int i=0;i<tree[u].size();i++){
		int v=tree[u][i];
		if(v==p) continue;
		for(int j=1;j<=k-1;j++){
			sum+=dp[v][j-1]*(dp[u][k-j]-dp[v][k-j-1]);
		}
	}
}