#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <cstring>
#include <queue>

#define MAX 1003

using namespace std;

vector<int> graph[MAX];
bool visited[MAX];

void dfs(int u);
void bfs(int u);

int main()
{
	int test,i,t,n,u,v,q,m,j;
	scanf("%d",&t);
	for(test=1;test<=t;test++) {
		for(i=0;i<MAX;i++) graph[i].clear();
		scanf("%d",&n);
		for(i=0;i<n;i++) {
			scanf("%d%d",&u,&m);
			for(j=0;j<m;j++) {
				scanf("%d",&v);
				graph[u].push_back(v);
			}

		}
		printf("graph %d\n",test);
		while(1) {
			scanf("%d%d",&u,&q);
			if(u==0 && q==0) break;
			if(q==0) {
				memset(visited, false, sizeof(visited));
				dfs(u);
				printf("\n");
			}
			else {
				memset(visited, false, sizeof(visited));
				bfs(u);
				printf("\n");
			}
		}
	}
	return 0;
}

void dfs(int u)
{
	int i;
	printf("%d ",u);
	visited[u] = true;
	for(i=0;i<graph[u].size();i++) {
		if(!visited[graph[u][i]]) {
			dfs(graph[u][i]);
		}
	}
}

void bfs(int u)
{
	int i,v;
	queue<int> Q;
	Q.push(u);
	visited[u] = true;
	while(!Q.empty()) {
		v = Q.front();
		Q.pop();
		printf("%d ",v);
		for(i=0;i<graph[v].size();i++) {
			if(!visited[graph[v][i]]) {
				Q.push(graph[v][i]);
				visited[graph[v][i]] = true;
			}
		}
	}
}
