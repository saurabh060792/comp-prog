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
int hldChainCount, hldIdx, hldChainLength[MAX], hldChainHead[MAX], hldNodeInChain[MAX], hldNodePosition[MAX], hldArr[MAX], hldNodeArrPosition[MAX], hldArrPositionNode[MAX];
int S[MAXTREE];
pair<int,int> specialChild[MAX];
vector<pair<int, int> > graph[MAX];

int dfs(int u, int p);
void computeLcaDp();
int lca(int u, int v);
void hld(int u, int p, int chain, int cost);
void buildST(int node, int low, int high);
int queryST(int node, int low, int high, int a, int b);
void updateST(int node, int low, int high, int position, int newValue);
int queryHLD1(int u, int v);													//Level[u] >= Level[v]
int queryHLD2(int u, int k);

int main()
{
	int t,i,k,u,v,w,l;
	char query[20];
	scanf("%d",&t);
	while(t--) {
		scanf("%d",&n);
		for(i=0;i<=n;i++) graph[i].clear();
		memset(S, 0, sizeof(S));
		for(i=0;i<n-1;i++) {
			scanf("%d%d%d",&u,&v,&w);
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
			if(!strcmp(query, "DIST")) {
				scanf("%d%d",&u, &v);
				l = lca(u, v);
				printf("%d\n",queryHLD1(u, l) + queryHLD1(v, l));
			}
			else if(!strcmp(query, "KTH")) {
				scanf("%d%d%d",&u, &v, &k);
				l = lca(u, v);
				if(lcaLevel[u] - lcaLevel[l] + 1 >= k) printf("%d\n",queryHLD2(u,k));
				else printf("%d\n", queryHLD2(v,lcaLevel[v]+lcaLevel[u]-2*lcaLevel[l]-k+2));
			}
			else break;
		}
		printf("\n");
	}
	return 0;
}

int queryHLD1(int u, int v)
{
	if(u == v) return 0;
	int headu = hldChainHead[hldNodeInChain[u]];
	if(hldNodeInChain[u] == hldNodeInChain[v]) return queryST(0, 0, hldIdx, hldNodeArrPosition[v]+1, hldNodeArrPosition[u]);
	else return queryHLD1(lcaParent[headu],v) + queryST(0, 0, hldIdx, hldNodeArrPosition[headu], hldNodeArrPosition[u]);
}

int queryHLD2(int u, int k)
{
	if(k==1) return u;
	int headu = hldChainHead[hldNodeInChain[u]];
	if(hldNodeArrPosition[u] - hldNodeArrPosition[headu] + 1 >= k) return hldArrPositionNode[hldNodeArrPosition[u]-k+1];
	else return queryHLD2(lcaParent[headu], k - 1 - hldNodeArrPosition[u] + hldNodeArrPosition[headu]);
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
		hldArrPositionNode[hldIdx] = u;
		hldArr[hldIdx++] = cost;													//Base Array is zero indexed
	}																				//Every other array is one indexed
	else {
		hldChainLength[chain]++;
		hldNodeInChain[u] = chain;
		hldNodePosition[u] = hldChainLength[chain];
		hldNodeArrPosition[u] = hldIdx;
		hldArrPositionNode[hldIdx] = u;
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
	lcaLevel[u] = p==-1?1:lcaLevel[p]+1;
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
	S[node] = S[lNode] + S[rNode];
	return;
}

int queryST(int node, int low, int high, int a, int b)
{
	int mid = (low+high)/2,lNode = 2*node + 1,rNode = 2*node + 2;
	if(a>high || b<low) return 0;
	if(a<=low && high<=b) return S[node];
	return queryST(lNode, low, mid, a, b) + queryST(rNode, mid + 1, high, a, b);
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
	S[node] = S[lNode] + S[rNode];
}