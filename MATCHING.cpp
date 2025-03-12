#include <stdio.h>
#include <vector>
#include <queue>
using namespace std;

#define MAX_N 100009
#define NIL 0
#define INF 1000000001

vector<int> tab[MAX_N];
int para[MAX_N], odl[MAX_N], n, m;

bool bfs()
{
	queue<int> kol;
	int u;
	for(int i=1;i<=n;++i)
		if(para[i]==NIL)
			odl[i]=0,
			kol.push(i);
		else
			odl[i]=INF;
	odl[NIL]=INF;
	while(!kol.empty()) {
		u=kol.front(); kol.pop();
		if(u!=NIL)
			for(int i=0;i<tab[u].size();++i)
				if(odl[para[tab[u][i]]]==INF)
					odl[para[tab[u][i]]]=odl[u]+1, kol.push(para[tab[u][i]]);
	}
	return odl[NIL]!=INF;
}

bool dfs(int u)
{
	if(u!=NIL) {
		for(int i=0;i<tab[u].size();++i)
			if(odl[para[tab[u][i]]]==odl[u]+1)
				if(dfs(para[tab[u][i]])) {
					para[tab[u][i]]=u;
					para[u]=tab[u][i];
					return 1;
				}
		odl[u]=INF;
		return 0;
	}
	return 1;
}

int hopcroft_karp()
{
	int pary=0;
	while(bfs())
		for(int i=1;i<=n;++i)
			if(para[i]==NIL && dfs(i))
				++pary;
	return pary;
}

int main()
{
	int a, b, t;
	scanf("%d%d%d",&n,&m,&t);
	while(t--) {
		scanf("%d%d",&a,&b);
		tab[a].push_back(b+n);
	}
	printf("%d\n",hopcroft_karp());
	return 0;
}
