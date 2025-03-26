#include <cstdio>
#include <algorithm>
#include <vector>

#define MAXNODE 100005
#define MAXK 202

using namespace std;

typedef long long lli;

lli dp[MAXNODE][MAXK];
bool memo[MAXNODE][MAXK];
int timer,parent[MAXNODE], dfsOrder[MAXNODE], childrenCount[MAXNODE], weight[MAXNODE], invDfs[MAXNODE];
vector<int> tree[MAXNODE];

int dfs(int u, int p);
lli f(int i, int j);

int main()
{
	timer = 1;
	int n,k,u,v,i,j;
	scanf("%d%d",&n,&k);
	for(i=1;i<=n;i++) scanf("%d",&weight[i]);
	for(i=1;i<n;i++) {
		scanf("%d%d",&u,&v);
		tree[u].push_back(v);
		tree[v].push_back(u);
	}
	dfs(1, 0);
	for(i=1;i<=n;i++) invDfs[dfsOrder[i]] = i;
	printf("%lld\n",f(n, k));
	return 0;
}


/*
f(i,j) represents the maximum value of 
tree with at most j deletetions till node i
but with restriction that every deleted node
has childern in the range 0..i that is for example
if i has children then we cannot delete children 
of i as they will not be in range 0..i.

So the case when i is deleted is considered when we 
reach the last child of i and then in loop every
ancestor is checked for deletion.

When i is not deleted
f(i,j) = max(f(i,j-1), f(i-1,j) + weight[dfsOrder[i]])

When i is deleted then one of the ancestor is responsible for i's deletetion
but the ancestor last child must be i
f(i,j) = for all a in Ancestor[i] (max(f(i,j), f(a-1, j-1)))
*/

lli f(int i, int j)
{
	int p;
	if(memo[i][j]) return dp[i][j];
	if(i==0) return 0;
	if(j==0) {
		dp[i][j] = f(i-1, j) + weight[dfsOrder[i]];
		memo[i][j] = true;
		return dp[i][j];
	}
	dp[i][j] = max(f(i, j-1), f(i-1, j) + weight[dfsOrder[i]]);

	p = dfsOrder[i];
	while(p!=0 && invDfs[p]+childrenCount[p]-1== i) {
		dp[i][j] = max(dp[i][j], f(invDfs[p]-1, j-1));
		p = parent[p];
	}
	memo[i][j] = true;
	return dp[i][j];
}

int dfs(int u, int p)
{
	int i;
	childrenCount[u] = 1;
	parent[u] = p;
	dfsOrder[timer++] = u;
	for(i=0;i<tree[u].size();i++) {
		if(tree[u][i] != p) {
			childrenCount[u] += dfs(tree[u][i], u);
		}
	}
	return childrenCount[u];
}