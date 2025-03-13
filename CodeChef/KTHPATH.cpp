#include <iostream>
#include <cassert>
#include <vector>
#include <cstdio>
#include <algorithm>

#define MAXN 100005

using namespace std;

vector<int> v[MAXN];
int path[MAXN],sp,visited[MAXN],N,i,j,x,y;
long long K;

bool dfs(int k)
{
	path[++sp] = k;
	visited[k] = 1;
	K--;
	if(!K) {
		for(int i=1;i<sp;i++) printf("%d ",path[i]);
		printf("%d\n",path[sp]);
		return true;
	}
	else
		for(int j=0;j<v[k].size();j++)
			if(!visited[v[k][j]] && dfs(v[k][j])) break;
	sp--;
	return false;
}

int main()
{
	int t;
	cin>>t;
	while(t--) {
		for(i=1;i<=N;i++) { 
			visited[i] = 0;
			v[i].clear();
		}
		cin>>N>>K;
		for(i=1;i<N;i++) {
			cin>>x>>y;
			v[x].push_back(y);
			v[y].push_back(x);
		}

		for(i=1;i<=N;i++) sort(v[i].begin(),v[i].end());

		for(i=1;i<=N;i++)
			if(K>N)K-=N;
			else {
				dfs(i);
				break;
			}
		sp=0;
	}
    return 0;
}
