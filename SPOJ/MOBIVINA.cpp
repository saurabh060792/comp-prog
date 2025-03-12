#include <cstdio>
#include <cstdio>
#include <queue>
#include <cstring>
#include <vector>
#include <iostream>

#define MAX 600
#define INF 2147483646
#define UNINITIALIZED -1

using namespace std; 

int capacities[MAX][MAX], flowPassed[MAX][MAX], parentsList[MAX], currentPathCapacity[MAX];
vector<int> graph[MAX];

int bfs(int startNode, int endNode);
int edmondsKarp(int startNode, int endNode);

int main()
{
	int source, sink, i,j,nodesCount,n,c,maxFlow;
	scanf("%d",&n);
	nodesCount = n+2;
	source = 1;
	sink = nodesCount;
	for(i=1; i<=n;i++) {
		scanf("%d",&c);
		capacities[source][i+1] = c;
		capacities[i+1][source] = 0;
		graph[source].push_back(i+1);
	}
	for(i=1;i<=n;i++) {
		scanf("%d",&c);
		capacities[i+1][sink] = c;
		capacities[sink][i+1] = 0;
		graph[i+1].push_back(sink);
	}
	for(i=1;i<=n;i++) {
		for(j=1;j<=n;j++) {
			scanf("%d",&c);
			capacities[i+1][j+1] = c;
			graph[i+1].push_back(j+1);
		}
	}
	maxFlow = edmondsKarp(source, sink);
	printf("%d\n",maxFlow); 
	return 0;
}


int bfs(int startNode, int endNode)
{
	memset(parentsList, UNINITIALIZED, sizeof(parentsList));
	memset(currentPathCapacity, 0, sizeof(currentPathCapacity));

	queue<int> q;
	q.push(startNode);

	parentsList[startNode]=-2;
	currentPathCapacity[startNode]=INF;

	while(!q.empty()) {
		int currentNode = q.front(); q.pop();
		for(int i=0; i<graph[currentNode].size(); i++) {
			int to = graph[currentNode][i];
			if(parentsList[to] == UNINITIALIZED) {
				if(capacities[currentNode][to] - flowPassed[currentNode][to] > 0) {
					parentsList[to] = currentNode;
					currentPathCapacity[to] = min(currentPathCapacity[currentNode], 
					capacities[currentNode][to] - flowPassed[currentNode][to]);
					if(to == endNode) return currentPathCapacity[endNode];
					q.push(to);
				}
			}
		}
	}

	return 0;
}

int edmondsKarp(int startNode, int endNode)
{
	int maxFlow=0;
	while(true) {
		int flow=bfs(startNode, endNode);
		if(flow==0) break;
		maxFlow +=flow;
		int currentNode=endNode;
		while(currentNode != startNode) {
			int previousNode = parentsList[currentNode];
			flowPassed[previousNode][currentNode] += flow;
			flowPassed[currentNode][previousNode] -= flow;
			currentNode=previousNode;
		}
	}
	return maxFlow;
}