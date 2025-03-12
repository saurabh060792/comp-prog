#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstdlib>
#include <cstring>

#define MAX 15004

using namespace std;

typedef long long int lli;

void createSet(lli x);
lli find(lli x);
lli merge(lli x, lli y);

lli parent[MAX], rank[MAX], setSize[MAX];
pair<lli, pair<lli, lli> > edge[MAX];

int main()
{
	lli n,i,v,u,t,w,cost;
	scanf("%lld",&t);
	while(t--) {
		cost = 0;
		scanf("%lld",&n);
		for(i=0;i<n-1;i++) {
			scanf("%lld%lld%lld",&edge[i].second.first, &edge[i].second.second, &edge[i].first);
			createSet(edge[i].second.first);
			createSet(edge[i].second.second);
		}
		sort(edge, edge+n-1);

		//Kruskal Logic
		for(i=0;i<n-1;i++) {
			u = find(edge[i].second.first);
			v = find(edge[i].second.second);
			w = edge[i].first;
			if(u!=v) {
				cost += setSize[u] * setSize[v] * (w+1);
				merge(u,v);
			}
		}
		printf("%lld\n",cost-n+1);
	}

	return 0;
}

void createSet(lli x)
{
	parent[x] = x;
	rank[x] = 1;
	setSize[x] = 1;
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
		setSize[yRep] += setSize[xRep];
		return (parent[xRep] = yRep);
	}
	else if(xRank > yRank) {
		setSize[xRep] += setSize[yRep];
		return (parent[yRep] = xRep);
	}
	else {
		setSize[xRep] += setSize[yRep];
		parent[yRep] = xRep;
		rank[xRep]++;
		return xRep;
	}
}