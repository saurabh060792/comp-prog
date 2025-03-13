#include <iostream>
#include <cstdlib>
#include <utility>
#include <queue>
#include <vector>

#define MAX 1000
#define INF 10000000

using namespace std;

typedef struct vertex
{
	int index,key,parent;														//parent in shortest path tree
}vertex;

struct compareGreater {
	bool operator() (vertex v, vertex u)
	{
		return v.key > u.key;
	}
};

vertex* prims(vector<vector<int> > graph, int **weight, int s);

int main()
{
	int n,e,u,v,i,**weight,s;
	vertex *V;
	cin>>n>>e;
	weight = (int**)malloc(n*sizeof(int*));
	for(i=0;i<n;i++) weight[i] = (int*)malloc(n*sizeof(int));
	vector<vector<int> > graph(n);
	for(i=0;i<e;i++) {														//assuming the vertices are number from 0 to n-1
		cin>>u>>v;
		cin>>weight[u][v];
		weight[v][u] = weight[u][v];
		graph[u].push_back(v);
		graph[v].push_back(u);
	}
	s = 0;
	V = prims(graph, weight, s);
	for(i=0;i<n;i++) cout<<V[i].key<<endl;
	return 0;
}

vertex* prims(vector<vector<int> > graph, int **weight, int s)
{
	int i,n = graph.size();
	int visited[n];
	vector<int>::iterator it;
	vertex t,temp,*V = (vertex*)malloc(n*sizeof(vertex)),u;
	priority_queue<vertex, vector<vertex>, compareGreater> Q;
	t.key = 0;
	t.index = s;
	t.parent = -1;
	Q.push(t);
	for(i=1;i<n;i++) {
		temp.key = INF;
		temp.index = i;
		Q.push(temp);
	}
	for(i=0;i<n;i++) visited[i] = 0;
	while(!Q.empty()) {
		u = Q.top();
		Q.pop();
		if(!visited[u.index]) {
			V[u.index].index = u.index;
			V[u.index].key = u.key;
			visited[u.index] = 1;
			for(it = graph[u.index].begin(); it != graph[u.index].end(); it++) {
				if(!visited[*it]) {
					temp.index = *it;
					temp.key = weight[u.index][*it];
					temp.parent = u.index;
					Q.push(temp);
				}
			}
		}
	}

	return V;
}



// Sample Input
// first line contain number of vertices and edges and next n line contains
// edges and their weights.
// 5 8
// 0 1 5
// 0 2 5
// 0 4 1
// 1 4 2
// 1 3 1
// 2 4 2
// 2 3 2
// 4 3 4