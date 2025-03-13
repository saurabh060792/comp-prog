#include <cstdio>
#include <algorithm>
#include <vector>

#define MAX 100005
#define LOGMAX 17

using namespace std;

int n,subTreeSize[MAX], parent[MAX], lcaDp[MAX][LOGMAX], level[MAX];
vector<int> tree[MAX];

void computeLcaDp();
int lca(int u, int v);
int dfs(int u, int p);
int ancestor(int u, int k);

int main()
{
	int u,v,i,q,l,dist;
	scanf("%d",&n);
	for(i=0;i<n-1;i++) {
		scanf("%d%d",&u,&v);
		tree[u].push_back(v);
		tree[v].push_back(u);
	}
	dfs(1, 0);
	computeLcaDp();
	scanf("%d",&q);
	while(q--) {
		scanf("%d%d",&u,&v);
		if(u==v) {
			printf("%d\n",n);
			continue;
		}
		l = lca(u,v);
		dist = level[u] + level[v] - 2*level[l];
		if(level[u]<level[v]) u ^= v ^= u ^= v;						//u is lower vertex
		if(dist%2) {
			printf("0\n");
			continue;
		}

		if(l==v) printf("%d\n",subTreeSize[ancestor(u, dist/2)] - subTreeSize[ancestor(u, dist/2 - 1)]);
		else {
			if(level[l] - level[u] == level[l] - level[v]) printf("%d\n",n - subTreeSize[ancestor(u, dist/2 - 1)] - subTreeSize[ancestor(v, dist/2 - 1)]);
			else printf("%d\n",subTreeSize[ancestor(level[u]>level[v]?u:v, dist/2)] - (level[u]>level[v]?subTreeSize[ancestor(u, dist/2 - 1)]:subTreeSize[ancestor(v, dist/2 - 1)]));
		}
	}
	return 0;
}

int ancestor(int u, int k)
{
	int i;
	for(i=LOGMAX-1;i>=0;i--)
		if(k&(1<<i))
			u = lcaDp[u][i];
	return u;
}

void computeLcaDp()
{
	int i,j;
	for(i=1;i<=n;i++) lcaDp[i][0] = parent[i];
	for(i=0;i<LOGMAX;i++) lcaDp[0][i] = -1;
	for(j=1;j<LOGMAX;j++)
		for(i=1;i<=n;i++)
			lcaDp[i][j] = lcaDp[i][j-1] == -1?-1:lcaDp[lcaDp[i][j-1]][j-1];
}

int lca(int u, int v)
{
	int logu,i;
	if(level[u]<level[v]) u ^= v ^= u ^= v;
	for(logu = 0;(1<<logu)<=level[u];logu++);
	logu--;
	for(i=logu;i>=0;i--)
		if(level[u] - (1<<i) >= level[v]) 
			u = lcaDp[u][i];
	if(u == v) return u;
	for(i=logu;i>=0;i--)
		if(lcaDp[u][i] != -1 && lcaDp[u][i] != lcaDp[v][i]) {
			u = lcaDp[u][i];
			v = lcaDp[v][i];
		}
	return parent[u];
}

int dfs(int u, int p)
{
	int i, sz=1;
	parent[u] = p;
	level[u] = p==0?1:level[p]+1;
	for(i=0;i<tree[u].size();i++)
		if(p != tree[u][i]) sz += dfs(tree[u][i], u);
	subTreeSize[u] = sz;
	return sz;
}