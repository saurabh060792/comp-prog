#include <cstdio>
#include <algorithm>
#include <vector>
#include <cstring>

#define MAX 100005
#define LOGMAX 17
#define MAXTREE 500005
#define INF 1000000000

using namespace std;

int n, lcaParent[MAX], lcaLevel[MAX];
int hldChainCount, hldIdx, hldChainLength[MAX], hldChainHead[MAX], hldNodeInChain[MAX], hldNodePosition[MAX], hldArr[MAX], hldNodeArrPosition[MAX], hldArrPositionNode[MAX];
int S[MAXTREE];
pair<int,int> specialChild[MAX];
vector<pair<int, int> > graph[MAX];

int dfs(int u, int p);
void hld(int u, int p, int chain);
void buildST(int node, int low, int high);
int queryST(int node, int low, int high, int a, int b);
void updateST(int node, int low, int high, int position);
int queryHLD(int u);													//Level[u] >= Level[v]
int read_int();

int main()
{
	int i,u,v,q,temp,query;
	n = read_int();
	q = read_int();
	for(i=0;i<n-1;i++) {
		u = read_int();
		v = read_int();
		graph[u].push_back(make_pair(v,0));
		graph[v].push_back(make_pair(u,0));
	}
	dfs(1, -1);
	hldChainCount = hldIdx = 0;
	hld(1, -1, -1);
	buildST(0, 0, hldIdx);
	while(q--) {
		query = read_int();
		if(query == 0) {
			u = read_int();
			updateST(0, 0, hldIdx, hldNodeArrPosition[u]);
		}
		else {
			u = read_int();
			temp = queryHLD(u);
			printf("%d\n",temp==INF?-1:temp);
		}
	}
	return 0;
}

int queryHLD(int u)
{
	int headu = hldChainHead[hldNodeInChain[u]], temp;
	if(hldNodeInChain[1] == hldNodeInChain[u]) return queryST(0, 0, hldIdx, hldNodeArrPosition[1], hldNodeArrPosition[u]);
	else { 
		temp = queryHLD(lcaParent[headu]);
		return temp!=INF?temp:queryST(0, 0, hldIdx, hldNodeArrPosition[headu], hldNodeArrPosition[u]);
	}
}

void hld(int u, int p, int chain)
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
		hldArr[hldIdx++] = lcaLevel[u];												//Base Array is zero indexed
	}																				//Every other array is one indexed
	else {
		hldChainLength[chain]++;
		hldNodeInChain[u] = chain;
		hldNodePosition[u] = hldChainLength[chain];
		hldNodeArrPosition[u] = hldIdx;
		hldArrPositionNode[hldIdx] = u;
		hldArr[hldIdx++] = lcaLevel[u];
	}
	if(specialChild[u].first != -1) hld(specialChild[u].first, u, chain);
	for(i=0;i<graph[u].size();i++) {
		v = graph[u][i].first;
		if(v != p && v != specialChild[u].first) hld(v, u, -1);
	}
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
		S[node] = INF;
		return;
	}
	buildST(lNode,low,mid);
	buildST(rNode,mid+1,high);
	S[node] = INF;
	return;
}

int queryST(int node, int low, int high, int a, int b)
{
	int mid = (low+high)/2,lNode = 2*node + 1,rNode = 2*node + 2,temp;
	if(a>high || b<low) return INF;
	if(a<=low && high<=b) return S[node];
	temp = queryST(lNode, low, mid, a, b);
	return temp!=INF?temp:queryST(rNode, mid + 1, high, a, b);
}

void updateST(int node, int low, int high, int position)
{
	int mid = (low+high)/2,lNode = 2*node + 1,rNode = 2*node + 2;
	if(low == high) {
		S[node] = S[node]==INF?hldArrPositionNode[low]:INF;
		return;
	}
	else if(position <= mid) updateST(lNode, low, mid, position);
	else updateST(rNode, mid+1, high, position);
	S[node] = S[lNode]!=INF?S[lNode]:S[rNode];
}

int read_int()
{
	register int x = 0, c = getchar_unlocked();
	int sign = 1;
	while(c!='-' && (c<48 || c>57) ) c = getchar_unlocked();
	if(c=='-') sign = -1, c = getchar_unlocked();
	while(c>=48 && c<=57) x = (x<<1) + (x<<3) + c - 48, c = getchar_unlocked();
	return sign*x;
}
