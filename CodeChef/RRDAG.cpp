#include <cstdio>
#include <algorithm>
#include <queue>
#include <vector>

#define MAX 1502

using namespace std;

bool visited[MAX];
char adjMat[MAX][MAX];
int outDegree[MAX];
vector<pair<int, int> > edge;

int main()
{
	int i,j,n,v;
	priority_queue<int> Q;
	scanf("%d",&n);
	for(i=0;i<n;i++) scanf("%s",adjMat[i]);
	for(i=0;i<n;i++) {
		for(j=0;j<n;j++) outDegree[i] += adjMat[i][j]-'0';
		if(!outDegree[i]) Q.push(i);
	}
	while(!Q.empty()) {
		v = Q.top();
		Q.pop();
		for(i=0;i<n;i++) {
			if(i==v || visited[i]) continue;
			if(adjMat[i][v] == '1') {
				outDegree[i]--;
				if(!outDegree[i]) Q.push(i);
			}
			else edge.push_back(make_pair(i, v));
		}
		visited[v] = true;
	}
	sort(edge.begin(), edge.end());
	printf("%d\n",edge.size());
	for(i=0;i<edge.size();i++) printf("%d %d\n",edge[i].first+1, edge[i].second+1);	
	return 0;
}