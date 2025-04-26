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
	int status,parent;
}vertex;

void dfs(vector<vector<int> > graph);
void dfsVisit(vector<vector<int> > graph, vertex *V, int u);
void dfsStack(vector<vector<int> > graph);

int main()
{
	int n,i,u,v,e;
	cin>>n>>e;
	vector<vector<int> > graph(n);
	vector<int>::iterator it;
	for(i=0;i<e;i++) {
		cin>>u>>v;
		graph[u].push_back(v);
		graph[v].push_back(u);
	}
	dfs(graph);
	dfsStack(graph);
	return 0;
}

void dfsStack(vector<vector<int> > graph)
{
	int i,n = graph.size(),u;
	vertex V[n];
	vector<int>::iterator it;
	stack<int> S;
	for(i=0;i<n;i++) V[i].status = UNEXPLORED;
	for(i=0;i<n;i++) {
		if(V[i].status == UNEXPLORED) {
			V[i].parent = -1;
			V[i].status = EXPLORING;
			S.push(i);
			while(!S.empty()) {
				u = S.top();
				S.pop();
				for(it = graph[u].begin(); it != graph[u].end(); it++) {
					if(V[*it].status == UNEXPLORED) {
						V[*it].parent = u;
						V[*it].status = EXPLORING;
						S.push(*it);
					}
				}
				V[u].status = EXPLORED;
			}
		}
	}
	return;
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
	return;
}


// Inputs:
// First Line : number of vertices(n) and edges(e)
// then e line follows for e edges
//
// Sample Input
// 8 9
// 0 1
// 0 3
// 1 2
// 1 3
// 2 3
// 4 5
// 5 6
// 6 7
// 7 4
