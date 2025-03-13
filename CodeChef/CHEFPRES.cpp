#include <cstdio>
#include <iostream>
#include <algorithm>
#include <set>
#include <vector>

#define MAX 10004
#define MAXP 102
#define LOGMAX 15
#define INF 1000000000

using namespace std;

typedef struct tree
{
	int depth, parent;
	int product[MAXP];
}tree;

int n,K,b,a,p,P[LOGMAX][MAX];
vector<int> graph[MAX];
tree t[MAX];

void dfs(int u, int pa);
int findK(int d);

int main()
{
	int i,j,k,q,u,v,low,mid,high;
	scanf("%d%d%d",&n,&K,&b);
	for(i=0;i<n-1;i++) {
		scanf("%d%d",&u,&v);
		graph[u].push_back(v);
		graph[v].push_back(u);
	}
	for(i=1;i<=n;i++) {
		scanf("%d",&p);
		for(j=1;j<=K;j++) t[i].product[j] = INF;
		t[i].product[p] = i;
	}
	t[b].depth = 0;
	t[b].parent = -1;
	dfs(b,-1);

	for(i=1;i<=n;i++) P[0][i] = t[i].parent;
	for(k=1;k<LOGMAX;k++) {
		for(i=1;i<=n;i++) {
			if((1<<k) <= t[i].depth) P[k][i] = P[k-1][P[k-1][i]];
		}
	}

	scanf("%d",&q);
	while(q--) {
		scanf("%d%d",&a,&p);
		if(t[b].product[p] == INF) {
			printf("-1\n");
			continue;
		}
		low = a;
		high = b;
		while(t[low].depth - t[high].depth > 1) {
			mid = P[findK(t[low].depth-t[high].depth) - 1][low];
			if(t[mid].product[p] != INF) high = mid;
			else low = mid;
		}
		if(t[low].product[p] != INF) printf("%d\n",t[low].product[p]);
		else printf("%d\n",t[high].product[p]);
	}

	return 0;
}

int findK(int d)
{
	int k=0,tk=1;
	while(tk<d) {
		k++;
		tk *= 2;
	}
	return k;
}

void dfs(int u, int pa)
{
	int i,v,j;
	for(i=0;i<graph[u].size();i++) {
		v = graph[u][i];
		if(v != pa) {
			t[v].depth = t[u].depth + 1;
			t[v].parent = u;
			dfs(v, u);
			for(j=1;j<=K;j++) {
				t[u].product[j] = min(t[u].product[j], t[v].product[j]);
			}
		}
	}
}