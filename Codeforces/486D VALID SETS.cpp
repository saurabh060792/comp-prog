#include <cstdio>
#include <vector>
#include <algorithm>
#include <cstring>

#define MAX 2003
#define MOD 1000000007

using namespace std;

vector<int> graph[MAX];
int a[MAX], f[MAX];
bool visited[MAX];
int d, n;

void dfs(int u, int root) ;

int main()
{
	int i,u,v,result;
	scanf("%d%d",&d,&n);
	for(i=1;i<=n;i++) scanf("%d",&a[i]);
	for(i=1;i<=n-1;i++) {
		scanf("%d%d",&u,&v);
		graph[u].push_back(v);;
		graph[v].push_back(u);
	}
	result = 0;
	for(i=1;i<=n;i++) {
		memset(f, 0, sizeof(f));
		memset(visited, 0, sizeof(visited));
		dfs(i, i);
		result = (result + f[i]) % MOD;
	}
	printf("%d\n",result);
}

void dfs(int u, int root) 
{
	int v,i;
	visited[u] = true;
	f[u] = 1;
	for(i=0;i<graph[u].size();i++) {
		v = graph[u][i];
		if(!visited[v]) {
			if((a[v] < a[root]) || (a[v] > a[root] + d)) continue;
			if((a[v] == a[root]) && (v < root)) continue;
			dfs(v, root);
			f[u] = ((long long)(f[u]) * (f[v] + 1)) % MOD;
		}
	}
}
