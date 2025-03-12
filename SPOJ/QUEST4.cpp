#include <cstdio>
#include <algorithm>
#include <queue>
#include <vector>
#include <cstring>

#define MAX 605
#define NIL 0
#define INF (1<<28)

using namespace std;

vector<int> G[MAX];
int n, m, match[MAX], dist[MAX];

int hopcroftKarp();
bool bfs();
bool dfs(int u);

int main()
{
	int t, i, x, y;
	scanf("%d", &t);
	while(t--) {
		scanf("%d", &n);
		for(i=0; i<MAX; i++) G[i].clear();
		memset(match, 0, sizeof(match));
		memset(dist, 0, sizeof(dist));

		for(i=0; i<n; i++) {
			scanf("%d%d", &x, &y);
			G[x+1].push_back(y+120+1);
		}
		n = 120;
		printf("%d\n", hopcroftKarp());
	}
	return 0;
}

bool bfs()
{
	int i, u, v, len;
	queue<int> Q;
	
	//From graph G1 make the distance of vertex equal    
	//0 if it is unmatched and infinity if it is matched
	//and insert unmatched vertices(free vertices) in queue Q
	for(i=1; i<=n; i++) {
		if(match[i]==NIL) {
			dist[i] = 0;
			Q.push(i);
		}
		else dist[i] = INF;
	}

	dist[NIL] = INF;
	while(!Q.empty()) {
		u = Q.front();
		Q.pop();
		if(u!=NIL) {
			len = G[u].size();
			for(i=0; i<len; i++) {
				v = G[u][i];
				//when all the vertices in V (corresponding to U)
				// which are unmatched (i.e. we have found one or
				//more M augumenting paths) are found 
				//then the top loop breaks because at that point queue  
				//contains only NIL

				//Note that dist[ match[v] ] will be equal to INF in
				//two cases when match[v] is NIL(in this case we have
				//found a M augumenting path) or the vertex which is
				//matched with v has not yet reached by bfs.
				if(dist[match[v]]==INF) {
					dist[match[v]] = dist[u] + 1;
					Q.push(match[v]);
				}
			}
		}
	}
	return (dist[NIL]!=INF);
}

bool dfs(int u)
{
	//Now this dfs is just used to backtrack the 
	//M augumenting path we have found in the above
	//bfs
	int i, v, len;
	if(u!=NIL) {
		len = G[u].size();
		for(i=0; i<len; i++) {
			v = G[u][i];
			if(dist[match[v]]==dist[u]+1) {
				if(dfs(match[v])) {
					match[v] = u;
					match[u] = v;
					return true;
				}
			}
		}
		dist[u] = INF;
		return false;
	}
	return true;
}

int hopcroftKarp()
{
	int matching = 0, i;
	// match[] is assumed NIL for all vertex in G
	while(bfs())
		for(i=1; i<=n; i++)
			if(match[i]==NIL && dfs(i))
				matching++;
	return matching;
}