#include <cstdio>
#include <algorithm>
#include <cstring>

#define MAX 100005
#define INF 1000000000

using namespace std;

typedef long long int lli;

pair<lli, pair<lli, lli> > edge[MAX];
lli parent[MAX],rank[MAX],n,m;

lli kruskal();
void createSet(lli x);
lli find(lli x);
lli merge(lli x, lli y);

int main()
{
	lli i;
	scanf("%lld%lld",&n,&m);
	for(i=0;i<m;i++){
		scanf("%lld%lld%lld",&edge[i].second.first,&edge[i].second.second,&edge[i].first);
		createSet(edge[i].second.first);
		createSet(edge[i].second.second);
	}
	sort(edge, edge+m);
	printf("%lld\n",kruskal());
	return 0;
}

lli kruskal()
{
	lli i,u,v,w=0;
	for(i=0;i<m;i++) {
		u = find(edge[i].second.first);
		v = find(edge[i].second.second);
		if(u != v) {
			merge(u,v);
			w += edge[i].first;
		}
	}
	return w;
}

void createSet(lli x)
{
	parent[x] = x;
	rank[x] = 1;
	return;
}

lli find(lli x)
{
	if(parent[x] == x) return x;
	else return (parent[x] = find(parent[x]));
}

lli merge(lli x, lli y)
{
	lli xRank, yRank, xRep, yRep;
	xRep = find(x);
	yRep = find(y);
	xRank = rank[xRep];
	yRank = rank[yRep];


	if(xRep == yRep) return xRep;
	else if(xRank < yRank) {
		return (parent[xRep] = yRep);
	}
	else if(xRank > yRank) {
		return (parent[yRep] = xRep);
	}
	else {
		parent[yRep] = xRep;
		rank[xRep]++;
		return xRep;
	}
}