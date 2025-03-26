#include <cstdio>
#include <algorithm>
#include <vector>
#include <queue>

#define MAX 1003
#define MAXVERTEX 1000006
using namespace std;

vector<int> graph[MAXVERTEX];
int a[MAX], indegree[MAXVERTEX];
priority_queue<int, vector<int>, greater<int> > Q;

int main()
{
	int u,v,n,i,j,m;
	scanf("%d",&n);
	for(i=0;i<n;i++) {
		scanf("%d",&m);
		for(j=0;j<m;j++){
			scanf("%d",&a[j]);
		}
		for(j=0;j<m-1;j++) {
			graph[a[j]].push_back(a[j+1]);
			indegree[a[j+1]]++;
		}
	}
	for(i=1;i<MAXVERTEX;i++) if(!indegree[i] && graph[i].size()) Q.push(i);

	while(!Q.empty()) {
		u = Q.top();
		Q.pop();
		printf("%d ",u);
		for(i=0;i<graph[u].size();i++) {
			v = graph[u][i];
			indegree[v]--;
			if(indegree[v]==0) Q.push(v);
		}
	}	

	return 0;
}