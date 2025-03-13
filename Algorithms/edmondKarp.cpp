#include <cstdio>
#include <algorithm>
#include <queue>
#include <cstring>
#include <vector>
#include <iostream>

#define MAX 1000
#define INF 1000000000

using namespace std;

vector<int> graph[MAX];
int cap[MAX][MAX], netFlow[MAX][MAX];

int edmondKarp(int s, int t);
int convert(char a);

int main()
{
	int i,u,v,c,n,m;
	scanf("%d%d",&n,&m);
	for(i=0;i<m;i++) {
		cin>>u>>v>>c;
		graph[u].push_back(v);
		graph[v].push_back(u);
		cap[u][v] += c;
	}
	printf("%d\n",edmondKarp(0,n));
	return 0;
}

int edmondKarp(int s, int t)
{
	int flow=0, prev[MAX], i, u, v, bot;
	while(1) {
		memset(prev, -1, sizeof(prev));
		queue<int> Q;
		Q.push(s);
		prev[s] = -2;
		while(!Q.empty() && prev[t]==-1) {
			u = Q.front();
			Q.pop();
			for(i=0;i<graph[u].size();i++) {
				v = graph[u][i];
				if(prev[v]==-1 && (netFlow[u][v]<cap[u][v] || netFlow[v][u])) {
					prev[v] = u;
					Q.push(v);
				}
			}
		}
		if(prev[t]==-1) break;
		bot = INF;
		for(v=t,u=prev[v]; u>=0; v=u,u=prev[v]) {
			if(netFlow[v][u]) bot = min(bot, netFlow[v][u]);
			else bot = min(bot, cap[u][v]-netFlow[u][v]);
		}
		for(v=t,u=prev[v]; u>=0; v=u,u=prev[v]) {
			if(netFlow[v][u]) netFlow[v][u] -= bot;
			else netFlow[u][v] += bot;
		}
		flow += bot;
	}
	return flow;
}