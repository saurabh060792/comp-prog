#include <cstdio>
#include <algorithm>
#include <queue>
#include <cstring>

#define MAX 55
#define MAXVERTEX 1000006
#define INF 1000000000
using namespace std;

int bucket[MAX], dist[MAXVERTEX];
bool visited[MAXVERTEX];

void dijkstra(int b, int a);

int main()
{
	int c,b,q,i,a;
	scanf("%d%d",&b,&q);
	for(i=0;i<b;i++) scanf("%d",&bucket[i]);
	a = *min_element(bucket, bucket+b);
	dijkstra(b,a);

	for(i=0;i<q;i++) {
		scanf("%d",&c);
		printf("%s\n",dist[c%a]>c?"no":"yes");
	}
	return 0;
}

void dijkstra(int b, int a)
{
	int u,v,i,w;
	priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > Q;
	for(i=0;i<a;i++) dist[i] = INF; 
	for(i=0;i<a;i++) visited[i] = false; 
	dist[0] = 0;
	for(Q.push(make_pair(0,0)); !Q.empty(); Q.pop()) {
		u = Q.top().second;
		if(visited[u]) continue;
		for(i=0;i<b;i++) {
			v = (u + bucket[i])%a;
			w = bucket[i];
			if(!visited[v] && dist[v] > dist[u] + w) {
				dist[v] = dist[u] + w;
				Q.push(make_pair(dist[v], v));
			}
		}
		visited[u] = true;
	}
}