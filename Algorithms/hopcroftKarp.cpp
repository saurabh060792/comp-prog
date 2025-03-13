#include <cstdio>
#include <algorithm>
#include <queue>
#include <vector>

#define MAX 100001
#define NIL 0
#define INF (1<<28)

using namespace std;

vector<int> G[MAX];
int n, m, match[MAX], dist[MAX];
// n: number of nodes on left side, nodes are numbered 1 to n
// m: number of nodes on right side, nodes are numbered n+1 to n+m
// G = NIL[0] ∪ G1[G[1---n]] ∪ G2[G[n+1---n+m]]
// Complexity : O(E sqrt(V))

int hopcroftKarp();
bool bfs();
bool dfs(int u);


int main()
{
	int a, b, t;
	scanf("%d%d%d",&n,&m,&t);
	while(t--) {
			scanf("%d%d",&a,&b);
			G[a].push_back(b+n);
	}
	printf("%d\n",hopcroftKarp());

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

/*
A vertex that is not the endpoint of an edge in some partial matching M
is called a free vertex. The basic concept that the algorithm relies on
is that of an augmenting path, a path that starts at a free vertex, ends
at a free vertex, and alternates between unmatched and matched edges
within the path. If M is a matching, and P is an augmenting path relative
to M, then the symmetric difference of the two sets of edges, M and P,
would form a matching with size |M| + 1.
Thus, by finding augmenting paths, an algorithm may increase the size of
the matching.

Algorithm
The algorithm is run in phases. Each phase consists of the following steps.

1.  A breadth-first search partitions the vertices of the graph into layers.
	The free vertices in U are used as the starting vertices of this search,
	and form the first layer of the partition. At the first level of the
	search, only unmatched edges may be traversed (since the free vertices
	in U are by definition not adjacent to any matched edges); at subsequent
	levels of the search, the traversed edges are required to alternate between
	matched and unmatched. That is, when searching for successors from a vertex
	in U, only unmatched edges may be traversed, while from a vertex in V only
	matched edges may be traversed. The search terminates at the first layer k
	where one or more free vertices in V are reached.

2.  All free vertices in V at layer k are collected into a set F. That is, a
	vertex v is put into F if and only if it ends a shortest augmenting path.

3.  The algorithm finds a maximal set of vertex disjoint augmenting paths of
	length k. This set may be computed by depth first search from F to the
	free vertices in U, using the breadth first layering to guide the search:
	the depth first search is only allowed to follow edges that lead to an
	unused vertex in the previous layer, and paths in the depth first search
	tree must alternate between matched and unmatched edges. Once an augmenting
	path is found that involves one of the vertices in F, the depth first search
	is continued from the next starting vertex.
4.  Every one of the paths found in this way is used to enlarge M.
*/