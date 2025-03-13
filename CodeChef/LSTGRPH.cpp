#include <cstdio>
#include <algorithm>
#include <stack>
#include <vector>
#include <cstring>

#define MAX 200005

using namespace std;

vector<pair<int, int> > graph[MAX];
bool visited[MAX];
vector<int> result(MAX);

int main()
{
	int n,m,k,i,j,u,v,w,l,start;
	stack<int> s;
	scanf("%d%d%d",&n,&m,&k);
	for(i=0;i<m;i++) {
		scanf("%d%d%d",&u,&v,&w);
		graph[u].push_back(make_pair(v,w));
		graph[v].push_back(make_pair(u,w));
	}

	for(i=1;i<=n;i++) {
		if(!visited[i]) {
			l = i;
			s.push(i);
			while(!s.empty()) {
				u = s.top();
				s.pop();
				for(j=0;j<graph[u].size();j++) {
					v = graph[u][j].first;
					if(!visited[v]) {
						visited[v] = true;
						s.push(v);
					}
				}
			}
		}
	}

	memset(visited, 0, sizeof(visited));

	for(i=1;i<=n;i++) {
		if(!visited[i]) {
			if(i==l) start = k-1;
			else start = 0;
			s.push(i);
			result[i] = start;
			while(!s.empty()) {
				u = s.top();
				s.pop();
				for(j=0;j<graph[u].size();j++) {
					v = graph[u][j].first;
					w = graph[u][j].second;
					if(!visited[v]) {
						visited[v] = true;
						s.push(v);
						result[v] = result[u]^w;
					}
					else {
						if((result[u]^w) != result[v]) {
							printf("-1\n");
							return 0;
						}
					}
				}
			}
		}
	}
	for(i=1;i<=n;i++) printf("%d ",result[i]);
	printf("\n");

	return 0;
}