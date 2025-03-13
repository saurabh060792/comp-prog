#include <iostream>
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
	int d,status,parent;								//parent in bfs tree
}vertex;

void bfs(vector<vector<int> > graph);

int main()
{
	int n,i,u,v,e;
	cin>>n>>e;											//vertices
	vector<vector<int> > graph(n);
	vector<int>::iterator it;
	for(i=0;i<e;i++) {
		cin>>u>>v;                               		//edges of undirected graph
		graph[u].push_back(v);
		graph[v].push_back(u);
	}

	// Printing the input
	// cout<<"here"<<endl;
	// for(i=0;i<n;i++) {
	// 	for(it = graph[i].begin(); it != graph[i].end(); it++)
	// 		cout<<*it<<"  ";
	// 	cout<<endl;
	// }

	bfs(graph);
	return 0;
}

void bfs(vector<vector<int> > graph)
{
	int i,n = graph.size(),u;
	vector<int>::iterator it;
	vertex V[n];
	queue<int> Q;
	for(i=0;i<n;i++) {
		V[i].d = INF;
		V[i].status = UNEXPLORED;
	}

	for(i=0;i<n;i++) {
		if(V[i].status == UNEXPLORED) {  				//taking care of the disconnected components	
			V[i].status = EXPLORING;
			V[i].d = 0;
			V[i].parent = -1;
			Q.push(i);
			while(!Q.empty()) {
				u = Q.front();
				Q.pop();
				for(it = graph[u].begin(); it != graph[u].end(); it++) {
					if(V[*it].status == UNEXPLORED) {
						V[*it].status = EXPLORING;
						V[*it].d = V[u].d + 1;
						V[*it].parent = u;
						Q.push(*it);
					}
				}
				V[u].status = EXPLORED;
			}
		}
	}

	// for(i=0;i<n;i++)
	// 	cout<<i<<". Distance: "<<V[i].d<<" Parent: "<<V[i].parent<<endl;
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