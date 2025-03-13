#include <cstdio>
#include <algorithm>
#include <queue>
#include <cstring>

#define MAX 10004
#define INF 1000000000

using namespace std;

struct compareGreater {
	bool operator() (pair<int, int> v, pair<int, int> u)
	{
		return v.second > u.second;
	}
};

vector<pair<int, int> > graph[MAX];
bool visited[MAX];
int dist[MAX];

void dijkstra(int s);

int main()
{
	int n,m,i,t,u,v,w,s,d;
	scanf("%d",&t);
	while(t--) {
		scanf("%d%d",&n,&m);
		for(i=0;i<MAX;i++) graph[i].clear();
		memset(dist, 0, sizeof(dist));
		memset(visited, false, sizeof(visited));
		for(i=0;i<m;i++) {
			scanf("%d%d%d",&u,&v,&w);
			graph[u].push_back(make_pair(v,w));
		}
		scanf("%d%d",&s,&d);
		dijkstra(s);
		if(dist[d]==INF) printf("NO\n");
		else printf("%d\n",dist[d]);
	}
	return 0;
}

void dijkstra(int s)
{
	int i,v,u,w;
	priority_queue<pair<int, int>, vector<pair<int, int> >, compareGreater> Q;
	Q.push(make_pair(s, 0));
	for(i=0;i<MAX;i++) dist[i] = INF;
	dist[s] = 0;

	while(!Q.empty()) {
		u = Q.top().first;
		Q.pop();
		if(visited[u]) continue;
		for(i=0;i<graph[u].size();i++) {
			v = graph[u][i].first;
			w = graph[u][i].second;
			if(!visited[v] && dist[v] > w + dist[u]) {
				dist[v] = w + dist[u];
				Q.push(make_pair(v, dist[v]));
			}
		}
		visited[u] = true;
	}
}