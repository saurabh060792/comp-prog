#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>
#include <algorithm>

#define INF 10000000
#define UNEXPLORED 0
#define EXPLORING 1
#define EXPLORED 2

using namespace std;

typedef struct vertex
{
	int d,status;
}vertex;

int bfs(vector<vector<int> > graph, int s);

int ans;

int main()
{
	int n,i,u,v,e;
	scanf("%d",&n);
	e = n - 1;											//vertices
	vector<vector<int> > graph(n);
	vector<int>::iterator it;
	for(i=0;i<e;i++) {
		scanf("%d%d",&u,&v);                       		//edges of undirected graph
		v--;u--;
		graph[u].push_back(v);
		graph[v].push_back(u);
	}
	bfs(graph, bfs(graph, 0));
	printf("%d\n",ans);
	return 0;
}

int bfs(vector<vector<int> > graph, int s)
{
	int i,n = graph.size(),u,max,maxIndex;
	vector<int>::iterator it;
	vertex V[n];
	queue<int> Q;
	for(i=0;i<n;i++) {
		V[i].d = INF;
		V[i].status = UNEXPLORED;
	}

	V[s].status = EXPLORING;
	V[s].d = 0;
	Q.push(s);
	while(!Q.empty()) {
		u = Q.front();
		Q.pop();
		for(it = graph[u].begin(); it != graph[u].end(); it++) {
			if(V[*it].status == UNEXPLORED) {
				V[*it].status = EXPLORING;
				V[*it].d = V[u].d + 1;
				Q.push(*it);
			}
		}
		V[u].status = EXPLORED;
	}
	max = V[0].d;
	maxIndex = 0;
	for(i=1;i<n;i++)
		if(V[i].d > max) {
			max = V[i].d;
			maxIndex = i;
		}
	ans = max;
	return maxIndex;
}