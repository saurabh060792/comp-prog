#include <cstdio>
#include <algorithm>
#include <vector>
#include <cstring>

#define MAX 10004
#define LOGMAX 15
#define MAXTREE 50005
#define INF 1000000000

using namespace std;

int n,lcaDp[MAX][LOGMAX], lcaParent[MAX], lcaLevel[MAX];
int hldChainCount, hldIdx, hldChainLength[MAX], hldChainHead[MAX], hldNodeInChain[MAX], hldNodePosition[MAX], hldArr[MAX], hldNodeArrPosition[MAX];
int S[MAXTREE];
pair<int,int> specialChild[MAX], edge[MAX];
vector<pair<int, int> > graph[MAX];

int dfs(int u, int p);
void computeLcaDp();
int lca(int u, int v);
void hld(int u, int p, int chain, int cost);
void buildST(int node, int low, int high);
int queryST(int node, int low, int high, int a, int b);
void updateST(int node, int low, int high, int position, int newValue);
int queryHLD(int u, int v);													//Level[u] >= Level[v]

int main()
{
	int t,i,u,v,w,l;
	char query[20];
	scanf("%d",&t);
	while(t--) {
		scanf("%d",&n);
		for(i=0;i<=n;i++) graph[i].clear();
		memset(S, 0, sizeof(S));
		for(i=0;i<n-1;i++) {
			scanf("%d%d%d",&u,&v,&w);
			edge[i+1] = make_pair(u,v);
			graph[u].push_back(make_pair(v,w));
			graph[v].push_back(make_pair(u,w));
		}
		dfs(1, -1);
		computeLcaDp();
		hldChainCount = hldIdx = 0;
		hld(1, -1, -1, 0);
		buildST(0, 0, hldIdx);
		while(1) {
			scanf("%s",query);
			if(!strcmp(query, "QUERY")) {
				scanf("%d%d",&u, &v);
				l = lca(u, v);
				printf("%d\n",max(queryHLD(u, l), queryHLD(v, l)));
			}
			else if(!strcmp(query, "CHANGE")) {
				scanf("%d%d",&i, &w);
				u = edge[i].first;
				v = edge[i].second;
				if(u != lcaParent[v]) u ^= v ^= u ^= v;
				updateST(0, 0, hldIdx, hldNodeArrPosition[v],w);
			}
			else break;
		}
	}
	return 0;
}

int queryHLD(int u, int v)
{
	if(u == v) return 0;
	int headu = hldChainHead[hldNodeInChain[u]];
	if(hldNodeInChain[u] == hldNodeInChain[v]) return queryST(0, 0, hldIdx, hldNodeArrPosition[v]+1, hldNodeArrPosition[u]);
	else return max(queryHLD(lcaParent[headu],v), queryST(0, 0, hldIdx, hldNodeArrPosition[headu], hldNodeArrPosition[u]));
}

void hld(int u, int p, int chain, int cost)
{
	int i,v;
	if(chain == -1) {
		chain = ++hldChainCount;
		hldChainLength[chain] = 1;
		hldChainHead[chain] = u;
		hldNodeInChain[u] = chain;
		hldNodePosition[u] = 1;
		hldNodeArrPosition[u] = hldIdx;
		hldArr[hldIdx++] = cost;
	}
	else {
		hldChainLength[chain]++;
		hldNodeInChain[u] = chain;
		hldNodePosition[u] = hldChainLength[chain];
		hldNodeArrPosition[u] = hldIdx;
		hldArr[hldIdx++] = cost;
	}
	if(specialChild[u].first != -1) hld(specialChild[u].first, u, chain, specialChild[u].second);
	for(i=0;i<graph[u].size();i++) {
		v = graph[u][i].first;
		if(v != p && v != specialChild[u].first) hld(v, u, -1, graph[u][i].second);
	}
}

void computeLcaDp()
{
	int i,j;
	for(i=1;i<=n;i++) lcaDp[i][0] = lcaParent[i];
	for(i=0;i<LOGMAX;i++) lcaDp[0][i] = -1;
	for(j=1;j<LOGMAX;j++)
		for(i=1;i<=n;i++)
			lcaDp[i][j] = lcaDp[i][j-1] == -1?-1:lcaDp[lcaDp[i][j-1]][j-1];
}

int lca(int u, int v)
{
	int logu,i;
	if(lcaLevel[u]<lcaLevel[v]) u ^= v ^= u ^= v;
	for(logu = 0;(1<<logu)<=lcaLevel[u];logu++);
	logu--;
	for(i=logu;i>=0;i--)
		if(lcaLevel[u] - (1<<i) >= lcaLevel[v]) 
			u = lcaDp[u][i];
	if(u == v) return u;
	for(i=logu;i>=0;i--)
		if(lcaDp[u][i] != -1 && lcaDp[u][i] != lcaDp[v][i]) {
			u = lcaDp[u][i];
			v = lcaDp[v][i];
		}
	return lcaParent[u];
}

int dfs(int u, int p)
{
	int i, maximum=0, temp, size=1;
	pair<int, int> special;
	lcaParent[u] = p;
	lcaLevel[u] = p==0?1:lcaLevel[p]+1;
	for(i=0;i<graph[u].size();i++) {
		if(p != graph[u][i].first) {
			temp = dfs(graph[u][i].first, u);
			size += temp;
			if(temp>maximum) {
				maximum = temp;
				special = make_pair(graph[u][i].first, graph[u][i].second);
			}
		}
	}
	if(size!=1) specialChild[u] = special;
	else specialChild[u] = make_pair(-1, -1);
	return size;
}

void buildST(int node, int low, int high)
{
	int mid = (low+high)/2,lNode = 2*node + 1,rNode = 2*node + 2;
	if(low == high) {
		S[node] = hldArr[low];
		return;
	}
	buildST(lNode,low,mid);
	buildST(rNode,mid+1,high);
	S[node] = max(S[lNode], S[rNode]);
	return;
}

int queryST(int node, int low, int high, int a, int b)
{
	int mid = (low+high)/2,lNode = 2*node + 1,rNode = 2*node + 2;
	if(a>high || b<low) return 0;
	if(a<=low && high<=b) return S[node];
	return max(queryST(lNode, low, mid, a, b), queryST(rNode, mid + 1, high, a, b));
}

void updateST(int node, int low, int high, int position, int newValue)
{
	int mid = (low+high)/2,lNode = 2*node + 1,rNode = 2*node + 2;
	if(low == high) {
		S[node] = newValue;
		return;
	}
	else if(position <= mid) updateST(lNode, low, mid, position, newValue);
	else updateST(rNode, mid+1, high, position, newValue);
	S[node] = max(S[lNode], S[rNode]);
}