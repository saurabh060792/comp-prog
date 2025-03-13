#include <cstdio>
#include <algorithm>
#include <vector>
#include <cstring>
#include <cstdlib>

#define MAX 100005
#define BLACK 0
#define WHITE 1
#define MAXTREE 400005

using namespace std;

typedef long long int lli;

typedef struct segmentTree1
{
	int black, white;							//maximum length of black/white from R
}segmentTree1;

typedef struct segmentTree2
{
	int black, white, blackLazy, whiteLazy;		//lazy denotes that this node is already updated
}segmentTree2;									//but its children are not

//hldArr is zero indexed
//nodeArrPosition maps from Node to ArrayPosition that is [1..n] -> [0..n-1]
int n, parent[MAX], subTreeSize[MAX];
int chainCount, hldIdx, chainLength[MAX], chainHead[MAX], nodeInChain[MAX], nodePosition[MAX], hldArr[MAX], nodeArrPosition[MAX], arrPositionNode[MAX];
segmentTree1 S1[MAXTREE];
segmentTree2 S2[MAXTREE];
pair<int,int> specialChild[MAX];
vector<pair<int, int> > graph[MAX];

int dfs(int u, int p);
void hld(int u, int p, int chain);
void buildST1(int node, int low, int high);
segmentTree1 queryST1(int node, int low, int high, int a, int b);
void updateST1(int node, int low, int high, int position);
void buildST2(int node, int low, int high);
int queryST2(int node, int low, int high, int a, int b, int type);
void updateST2(int node, int low, int high, int a, int b, int value, int type);
int queryHLD(int u);
void updateHLD(int u, int val, int color);


int main()
{
	int i,u,v,query,q;
	scanf("%d",&n);
	for(i=0;i<n-1;i++) {
		scanf("%d%d",&u,&v);
		graph[u].push_back(make_pair(v,BLACK));
		graph[v].push_back(make_pair(u,BLACK));
	}
	dfs(1, -1);
	chainCount = hldIdx = 0;
	hld(1, -1, -1);
	buildST1(0, 0, hldIdx-1);
	buildST2(0, 0, hldIdx-1);
	scanf("%d",&q);

	while(q--) {
		scanf("%d%d",&query,&u);
		if(query == 0) {
			v = queryHLD(u);
			printf("%d\n",queryST2(0, 0, hldIdx-1, nodeArrPosition[v], nodeArrPosition[v], hldArr[nodeArrPosition[v]]));
		}
		else {
			updateHLD(parent[u], queryST2(0, 0, hldIdx-1, nodeArrPosition[u], nodeArrPosition[u], hldArr[nodeArrPosition[u]]), hldArr[nodeArrPosition[u]]);
			hldArr[nodeArrPosition[u]] = hldArr[nodeArrPosition[u]]==BLACK?WHITE:BLACK;
			updateHLD(parent[u], -queryST2(0, 0, hldIdx-1, nodeArrPosition[u], nodeArrPosition[u], hldArr[nodeArrPosition[u]]), hldArr[nodeArrPosition[u]]);
			updateST1(0, 0, hldIdx-1, nodeArrPosition[u]);
		}
	}
	return 0;
}

int queryHLD(int u)
{
	int headu = chainHead[nodeInChain[u]], l = nodeArrPosition[headu], r = nodeArrPosition[u], temp;
	temp = hldArr[nodeArrPosition[u]] == BLACK?queryST1(0, 0, hldIdx-1, l, r).black:queryST1(0, 0, hldIdx-1, l, r).white;
	if(temp == r - l + 1 && headu != 1 && hldArr[nodeArrPosition[headu]] == hldArr[nodeArrPosition[parent[headu]]]) return queryHLD(parent[headu]);
	else return arrPositionNode[r-temp+1];
}

void updateHLD(int u, int val, int color)
{
	if(u==-1) return;
	int headu = chainHead[nodeInChain[u]], l = nodeArrPosition[headu], r = nodeArrPosition[u], temp;
	temp = color == BLACK?queryST1(0, 0, hldIdx-1, l, r).black:queryST1(0, 0, hldIdx-1, l, r).white;
	if(temp!=0)updateST2(0, 0, hldIdx-1, r-temp+1, r, -val, hldArr[nodeArrPosition[u]]);
	if(temp == r - l + 1) updateHLD(parent[headu], val, color);
	else updateST2(0,0,hldIdx-1,r-temp,r-temp,-val,color);
}

void hld(int u, int p, int chain)
{
	int i,v;
	if(chain == -1) {
		chain = ++chainCount;
		chainLength[chain] = 1;
		chainHead[chain] = u;
		nodeInChain[u] = chain;
		nodePosition[u] = 1;
		nodeArrPosition[u] = hldIdx;
		arrPositionNode[hldIdx++] = u;
	}
	else {
		chainLength[chain]++;
		nodeInChain[u] = chain;
		nodePosition[u] = chainLength[chain];
		nodeArrPosition[u] = hldIdx;
		arrPositionNode[hldIdx++] = u;
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
	parent[u] = p;
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
	subTreeSize[u] = size;
	return size;
}

void buildST1(int node, int low, int high)
{
	int mid = (low+high)/2,lNode = 2*node + 1,rNode = 2*node + 2;
	if(low == high) {
		S1[node].white = 0;
		S1[node].black = 1;
		return;
	}
	buildST1(lNode,low,mid);
	buildST1(rNode,mid+1,high);
	S1[node].white = 0;
	S1[node].black = high - low + 1;
	return;
}

segmentTree1 queryST1(int node, int low, int high, int a, int b)
{
	int mid = (low+high)/2,lNode = 2*node + 1,rNode = 2*node + 2;
	segmentTree1 r1, r2, r;
	if(a<=low && high<=b) return S1[node];
	if(b<=mid) return queryST1(lNode, low, mid, a, b);
	if(a>mid) return queryST1(rNode, mid+1, high, a, b);
	r1 = queryST1(lNode, low, mid, a, b);
	r2 = queryST1(rNode, mid + 1, high, a, b);
	r.black = r2.black == min(b,high)-mid?r1.black+r2.black:r2.black;
	r.white = r2.white == min(b,high)-mid?r1.white+r2.white:r2.white;
	return r;
}

void updateST1(int node, int low, int high, int position)
{
	int mid = (low+high)/2,lNode = 2*node + 1,rNode = 2*node + 2;
	if(low == high) {
		S1[node].black = S1[node].black == 1?0:1;
		S1[node].white = S1[node].white == 1?0:1;
		return;
	}
	else if(position <= mid) updateST1(lNode, low, mid, position);
	else updateST1(rNode, mid+1, high, position);
	S1[node].black = S1[rNode].black == high-mid?S1[rNode].black+S1[lNode].black:S1[rNode].black;
	S1[node].white = S1[rNode].white == high-mid?S1[rNode].white+S1[lNode].white:S1[rNode].white;
}

void buildST2(int node, int low, int high)
{
	int lNode = 2*node + 1, rNode = 2*node + 2, mid = (low + high)/2;
	if(low == high) {
		S2[node].black = subTreeSize[arrPositionNode[low]];
		S2[node].white = 1;
		S2[node].blackLazy = S2[node].whiteLazy = 0;
		return;
	}
	buildST2(lNode, low, mid);
	buildST2(rNode, mid + 1, high);
	S2[node].black = max(S2[lNode].black, S2[rNode].black);
	S2[node].white = 1;
	S2[node].blackLazy = S2[node].whiteLazy = 0;
	return;
}

void updateST2(int node, int low, int high, int a, int b, int value, int type)
{
	int lNode = 2*node + 1, rNode = 2*node + 2, mid = (low + high)/2;
	if(a > high || b < low) return;
	if(low == high){
		if(type == BLACK) S2[node].black += value;
		else S2[node].white += value;
		return;
	}
	if(S2[node].blackLazy != 0) {						//lazy field is set so we need to update this node and push laziness to its children
		S2[lNode].blackLazy += S2[node].blackLazy;
		S2[rNode].blackLazy += S2[node].blackLazy;
		S2[lNode].black += S2[node].blackLazy;
		S2[rNode].black += S2[node].blackLazy;
		S2[node].blackLazy = 0;		
	}
	if(S2[node].whiteLazy != 0) {						//lazy field is set so we need to update this node and push laziness to its children
		S2[lNode].whiteLazy += S2[node].whiteLazy;
		S2[rNode].whiteLazy += S2[node].whiteLazy;
		S2[lNode].white += S2[node].whiteLazy;
		S2[rNode].white += S2[node].whiteLazy;
		S2[node].whiteLazy = 0;
	}
	if(a <= low && b >= high) {
		if(type==BLACK) {
			S2[node].black += value;
			S2[node].blackLazy += value;
		}
		else {
			S2[node].white += value;
			S2[node].whiteLazy += value;
		}
		return;
	}
	updateST2(lNode, low, mid, a, b, value, type);
	updateST2(rNode, mid + 1, high, a, b, value, type);
	if(type == BLACK) S2[node].black = max(S2[lNode].black, S2[rNode].black);
	else S2[node].white = max(S2[lNode].white, S2[rNode].white);
}

int queryST2(int node, int low, int high, int a, int b, int type)
{
	int lNode = 2*node + 1, rNode = 2*node + 2, mid = (low + high)/2;
	if(a > high || b < low) return 0;
	if(low == high) return type==BLACK?S2[node].black:S2[node].white;
	if(S2[node].blackLazy != 0) {
		S2[lNode].blackLazy += S2[node].blackLazy;
		S2[rNode].blackLazy += S2[node].blackLazy;
		S2[lNode].black += S2[node].blackLazy;
		S2[rNode].black += S2[node].blackLazy;
		S2[node].blackLazy = 0;
	}
	if(S2[node].whiteLazy != 0) {
		S2[lNode].whiteLazy += S2[node].whiteLazy;
		S2[rNode].whiteLazy += S2[node].whiteLazy;
		S2[lNode].white += S2[node].whiteLazy;
		S2[rNode].white += S2[node].whiteLazy;
		S2[node].whiteLazy = 0;
	}
	if(a <= low && b >= high) return type==BLACK?S2[node].black:S2[node].white;
	return max(queryST2(lNode, low, mid, a, b, type), queryST2(rNode, mid + 1, high, a, b, type));
}