#include <cstdio>
#include <algorithm>
#include <cstring>
#include <functional>

#define MAX 20004
#define INF 1000000000

using namespace std;

typedef long long int lli;

pair<lli, pair<lli, lli> > edge1[MAX], edge2[MAX];
lli parent[MAX],rank[MAX];

void createSet(lli x);
lli find(lli x);
lli merge(lli x, lli y);

int main()
{
	int t,n,i,m1,m2,u,v,count;
	lli w1,w2;
	scanf("%d",&t);
	while(t--) {
		memset(parent, 0, sizeof(parent));
		memset(rank, 0, sizeof(rank));
		scanf("%d%d%d",&n,&m1,&m2);
		for(i=0;i<m1;i++) {
			scanf("%lld%lld%lld",&edge1[i].second.first, &edge1[i].second.second, &edge1[i].first);
			createSet(edge1[i].second.first);
			createSet(edge1[i].second.second);
		}
		for(i=0;i<m2;i++) {
			scanf("%lld%lld%lld",&edge2[i].second.first, &edge2[i].second.second, &edge2[i].first);
			createSet(edge2[i].second.first);
			createSet(edge2[i].second.second);
		}
		sort(edge1, edge1+m1);
		sort(edge2, edge2+m2, greater<pair<lli, pair<lli, lli> > >());
		w1 = w2 = count = 0;
		for(i=0;i<m2;i++) {
			u = find(edge2[i].second.first);
			v = find(edge2[i].second.second);
			if(u != v) {
				merge(u,v);
				w2 += edge2[i].first;
				count++;
			}
		}
		for(i=0;i<m1;i++) {
			u = find(edge1[i].second.first);
			v = find(edge1[i].second.second);
			if(u != v) {
				merge(u,v);
				w1 += edge1[i].first;
				count++;
			}
		}
		if(count==n-1) printf("%lld %lld\n",w2, w1+w2);
		else printf("Impossible\n");
	}
	return 0;
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