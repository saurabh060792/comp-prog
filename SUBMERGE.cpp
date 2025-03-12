#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>

#define MAX 100005

using namespace std;

vector<int> graph[MAX];
int cIdx[MAX], sNo[MAX], timer;
bool artPoint[MAX], visited[MAX];

void dfs(int n);
int dfsVisit(int u, int p);

int main()
{
	int n,m,v,u,i,count,j;
	while(1) {
		count = 0;
		scanf("%d%d",&n,&m);
		if(n==0 && m==0) break;
		for(i=0;i<=n;i++) graph[i].clear();
		for(i=0;i<m;i++) {
			scanf("%d%d",&u,&v);
			graph[u].push_back(v);
			graph[v].push_back(u);
		}
		dfs(n);
		for(i=1;i<=n;i++) if(artPoint[i]) count++;
		printf("%d\n",count);
	}
	return 0;
}

void dfs(int n)
{
	int i;
	for(i=0;i<=n;i++) artPoint[i] = visited[i] = false;
	timer = 0;
	for(i=1;i<=n;i++) {
		if(!visited[i]) {
			dfsVisit(i, -1);
		}
	}
}

int dfsVisit(int u, int p)
{
	int i,v,vCIdx,children=0;
	timer++;
	cIdx[u] = sNo[u] = timer;
	visited[u] = true;
	for(i=0;i<graph[u].size();i++) {
		v = graph[u][i];
		if(v==p) continue;
		if(!visited[v]) {
			children++;
			vCIdx = dfsVisit(v, u);
			cIdx[u] = min(cIdx[u], vCIdx);
			if(p == -1 && children>1) artPoint[u] = true;
			if(p != -1 && vCIdx >= sNo[u]) artPoint[u] = true;
		}
		else cIdx[u] = min(cIdx[u], sNo[v]);
	}
	return cIdx[u];
}