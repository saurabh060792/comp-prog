#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

#define INF 10000000
#define UNEXPLORED 0
#define EXPLORING 1
#define EXPLORED 2

using namespace std;

typedef struct vertex
{
	int status,parent;									//parent in dfs tree
}vertex;

void dfs(vector<vector<int> > graph);
void dfsVisit(vector<vector<int> > graph, vertex *V, int u);

stack<int> ts;

int main()
{
	int n,i,u,v,e;
	cin>>n>>e;											//vertices
	vector<vector<int> > graph(n);
	for(i=0;i<e;i++) {
		cin>>u>>v;                               		//edges of undirected graph
		graph[u].push_back(v);
	}

	dfs(graph);
	while(!ts.empty()) {
		cout<<ts.top()<<" ";
		ts.pop();
	}
	cout<<endl;
	return 0;
}

void dfs(vector<vector<int> > graph)
{
	int i,n = graph.size(),u;
	vertex V[n];
	for(i=0;i<n;i++) V[i].status = UNEXPLORED;

	for(i=0;i<n;i++)
		if(V[i].status == UNEXPLORED) {
			V[i].parent = -1;
			dfsVisit(graph, V, i);
		}
	return;
}

void dfsVisit(vector<vector<int> > graph, vertex *V, int u)
{
	vector<int>::iterator it;
	V[u].status = EXPLORING;
	for(it = graph[u].begin(); it != graph[u].end(); it++) {
		if(V[*it].status == UNEXPLORED) {
			V[*it].parent = u;
			dfsVisit(graph, V, *it);
		}
	}
	V[u].status = EXPLORED;
	ts.push(u);
	return;
}