#include <cstdio>
#include <algorithm>
#include <cstring>

#define MAXN 5005
#define MAXE 60006
#define INF 0x7fffffff

using namespace std;

typedef long long int lli;

lli src, snk, nNode, nEdge;
lli Q[MAXN], fin[MAXN], pro[MAXN], dist[MAXN], flow[MAXE], cap[MAXE], next[MAXE], to[MAXE];

void init(lli source, lli sink, lli nodes);
void add(lli u, lli v, lli c);
bool bfs();
lli dfs(lli u, lli fl);
lli dinitz();


int main()
{
	lli n, e, u, v, c, i;
	scanf("%lld",&n);
	init(1, 2*n+2, 2*n+2);
	printf("%lld\n", dinitz());
	return 0;
}

void init(lli source, lli sink, lli nodes)
{
	src = source, snk = sink, nNode = nodes, nEdge = 0;
	memset(fin, -1, sizeof(fin));
}

void add(lli u, lli v, lli c)
{
	to[nEdge] = v, cap[nEdge] = c, flow[nEdge] = 0, next[nEdge] = fin[u], fin[u] = nEdge++;
	to[nEdge] = u, cap[nEdge] = c, flow[nEdge] = 0, next[nEdge] = fin[v], fin[v] = nEdge++;
}

bool bfs()
{
	lli st, en, i, u, v;
	memset(dist, -1, sizeof(dist));
	dist[src] = st = en = 0;
	Q[en++] = src;
	while(st < en) {
		u = Q[st++];
		for(i=fin[u]; i>=0; i=next[i]) {
			v = to[i];
			if(flow[i] < cap[i] && dist[v]==-1) {
				dist[v] = dist[u]+1;
				Q[en++] = v;
			}
		}
	}
	return dist[snk]!=-1;
}

lli dfs(lli u, lli fl)
{
	if(u==snk) return fl;
	for(lli &e=pro[u], v, df; e>=0; e=next[e]) {
		v = to[e];
		if(flow[e] < cap[e] && dist[v]==dist[u]+1) {
			df = dfs(v, min(cap[e]-flow[e], fl));
			if(df>0) {
				flow[e] += df;
				flow[e^1] -= df;
				return df;
			}
		}
	}
	return 0;
}

lli dinitz()
{
	lli ret = 0, df;
	while(bfs()) {
		for(lli i=1; i<=nNode; i++) pro[i] = fin[i];
		while(true) {
			df = dfs(src, INF);
			if(df) ret += df;
			else break;
		}
	}
	return ret;
}