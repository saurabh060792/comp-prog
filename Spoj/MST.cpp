#include <cstdio>
#include <algorithm>
#include <queue>
#include <cstring>

#define MAX 10004
#define INF 1000000000

using namespace std;

typedef long long int lli;

struct compareGreater {
	bool operator() (pair<lli, lli> v, pair<lli, lli> u)
	{
		return v.second > u.second;
	}
};

vector<pair<lli, lli> > graph[MAX];
bool visited[MAX];
lli dist[MAX],n;

lli prims(lli s);

int main()
{
	lli m,i,u,v,w;
	scanf("%lld%lld",&n,&m);
	for(i=1;i<=n;i++) graph[i].clear();
	for(i=0;i<m;i++) {
		scanf("%lld%lld%lld",&u,&v,&w);
		graph[u].push_back(make_pair(v,w));
		graph[v].push_back(make_pair(u,w));
	}
	printf("%lld\n",prims(1));
	return 0;
}

lli prims(lli s)
{
	lli i,v,u,w,c=0;
	priority_queue<pair<lli, lli>, vector<pair<lli, lli> >, compareGreater> Q;
	Q.push(make_pair(s, 0));
	for(i=1;i<=n;i++) dist[i] = INF;
	dist[s] = 0;

	while(!Q.empty()) {
		u = Q.top().first;
		Q.pop();
		if(visited[u]) continue;
		for(i=0;i<graph[u].size();i++) {
			v = graph[u][i].first;
			w = graph[u][i].second;
			if(!visited[v] && w < dist[v]) {
				dist[v] = w;
				Q.push(make_pair(v, dist[v]));
			}
		}
		visited[u] = true;
		c += dist[i];
	}
	return c;
}