#include <cstdio>
#include <algorithm>
#include <vector>
#include <queue>

#define MAX 20004
#define INF (((lli)1000000000) * ((lli)1000000000))

using namespace std;

typedef long long int lli;

vector<pair<lli, lli> > graph[MAX];
bool visited[MAX];
int n,m;
lli dist[MAX], len[MAX];

void init();
lli dijkstra();
lli prims();

int main()
{
	int t,i;
	lli pans, dans, w, u, v;
	scanf("%d",&t);
	while(t--) {
		scanf("%d%d",&n,&m);
		for(i=0;i<=n;i++) graph[i].clear();
		for(i=0;i<m;i++) {
			scanf("%lld%lld%lld",&u,&v,&w);
			graph[u].push_back(make_pair(w, v));
			graph[v].push_back(make_pair(w, u));
		}
		init();
		dans = dijkstra();
		init();
		pans = prims();
		if(dans == pans && dans != -1) printf("YES\n");
		else printf("NO\n");
	}
	return 0;
}

void init()
{
	int i;
	for(i=0;i<n;i++) {
		visited[i] = false;
		len[i] = INF;
		dist[i] = INF;
	}
	len[0] = dist[0] = 0;
}

lli dijkstra()
{
	int i;
	lli sum = 0,w, u, v;
	priority_queue<pair<lli, pair<lli, lli> >, vector<pair<lli, pair<lli, lli> > >, greater<pair<lli, pair<lli, lli> > > > Q;
	Q.push(make_pair(0,make_pair(0,0)));
	while(!Q.empty()) {
		u = Q.top().second.second;
		Q.pop();
		if(visited[u]) continue;
		for(i=0;i<graph[u].size();i++) {
			v = graph[u][i].second;
			w = graph[u][i].first;
			if(!visited[v] && (dist[u] + w < dist[v] || (dist[u] + w == dist[v] && w < len[v]))) {
				dist[v] = dist[u] + w;
				len[v] = w;
				Q.push(make_pair(dist[v], make_pair(len[v], v)));
			}
		}
		visited[u] = true;
	}
	for(i=1;i<n;i++)
		if(dist[i] != INF) sum += len[i];
		else return -1;
	return sum;
}

lli prims()
{
	int i;
	lli sum = 0,w, u, v;
	priority_queue<pair<lli, lli>, vector<pair<lli, lli> >, greater<pair<lli, lli> > > Q;
	Q.push(make_pair(0,0));
	while(!Q.empty()) {
		u = Q.top().second;
		Q.pop();
		if(visited[u]) continue;
		for(i=0;i<graph[u].size();i++) {
			v = graph[u][i].second;
			w = graph[u][i].first;
			if(!visited[v] && dist[v]>w) {
				dist[v] = w;
				Q.push(make_pair(dist[v], v));
			}
		}
		visited[u] = true;
	}
	for(i=1;i<n;i++)
		if(dist[i] != INF) sum += dist[i];
		else return -1;
	return sum;
}