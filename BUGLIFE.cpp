#include <cstdio>
#include <algorithm>
#include <vector>

#define MAX 2003

using namespace std;

vector<int> graph[MAX];
int visited[MAX];

bool isBipartite(int n);
bool dfsVisit(int u, int p);

int main()
{
	int _t,t,n,m,i,u,v;
	scanf("%d",&t);
	for(_t=1;_t<=t;_t++) {
		scanf("%d%d",&n,&m);
		for(i=0;i<=n;i++) graph[i].clear();
		for(i=0;i<m;i++) {
			scanf("%d%d",&u,&v);
			graph[u].push_back(v);
			graph[v].push_back(u);
		}
		for(i=0;i<=n;i++) visited[i] = -1;
		printf("Scenario #%d:\n%s\n",_t,isBipartite(n)?"No suspicious bugs found!":"Suspicious bugs found!");
	}
	return 0;
}

bool isBipartite(int n)
{
	int i;
	for(i=1;i<=n;i++) {
		if(visited[i] == -1) {
			visited[i] = 1;
			if(!dfsVisit(i, -1)) return false;
		}
	}
	return true;
}

bool dfsVisit(int u, int p)
{
	int i,v;
	bool f = true;
	for(i=0;i<graph[u].size() && f;i++) {
		v = graph[u][i];
		if(v == p) continue;
		if(visited[v] == -1) {
			visited[v] = visited[u] + 1;
			f &= dfsVisit(v, u);
		}
		else f &= (abs(visited[u] - visited[v] + 1))%2?false:true;
	}
	return f;
}
