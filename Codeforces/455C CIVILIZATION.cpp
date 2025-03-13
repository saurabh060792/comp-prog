#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstdlib>
#include <queue>
#include <vector>
#include <cstring>

#define MAX 300005
#define UNEXPLORED (0)
#define EXPLORED (-2)
#define EXPLORING (-3)
#define INF (1<<30)

using namespace std;

typedef struct vertex
{
	int distance, status;
}vertex;

vector<int> graph[MAX];
int diameter[MAX]={}, n, parent[MAX], rank[MAX], maxi, maxiV;
bool visited[MAX] = {false};

int nextInt();
void createSet(int x);
int find(int x);
int merge(int x, int y);
int findDiameter(int start);
int ceiling(int p, int q);
void dfs(int v, int depth, int p);

int main()
{
	int i, m, q, u, v, qType, x, y, maximum,fx,fy;

	n = nextInt();
	m = nextInt();
	q = nextInt();

	for(i=0;i<n;i++) createSet(i);
	for(i=0;i<m;i++) {
		u = nextInt();
		v = nextInt();
		v--,u--;
		graph[u].push_back(v);
		graph[v].push_back(u);
		merge(u, v);
	}

	for(i=0;i<n;i++) {
		fx = find(i);
		if(!visited[fx]){
			visited[fx] = true;
			diameter[find(i)] = findDiameter(i);
		}
	}

	for(i=0;i<q;i++) {
		qType = nextInt();
		if(qType == 1) {
			x = nextInt();
			x--;
			printf("%d\n",diameter[find(x)]);
		}
		else {
			x = nextInt();
			y = nextInt();
			x--,y--;
			fx = find(x);
			fy = find(y);
			if(fx == fy) continue;
			maximum = -INF;
			maximum = max(diameter[fx], max(diameter[fy], max(ceiling(diameter[fx],2) + ceiling(diameter[fy],2) + 1, maximum)));
			merge(x, y);
			diameter[find(x)] = maximum;
		}
	}

	return 0;
}

int nextInt()
{
    int x = 0, p = 1;
    char c;
    do {
        c = getchar();
    } while (c <= 32);
    if (c == '-') {
        p = -1;
        c = getchar();
    }
    while (c >= '0' && c <= '9') {
        x = x * 10 + c - '0';
        c = getchar();
    }
    return x * p;
}

int ceiling(int p, int q)
{
	return (p+1)/q;
}


void dfs(int v, int depth, int p)
{
	int i, to;
    if (depth > maxi) {
        maxi = depth;
        maxiV = v;
    }
    for (i = 0; i < graph[v].size(); i++) {
        to = graph[v][i];
        if (to != p) dfs(to, depth + 1, v);
    }
}

int findDiameter(int v) {
    maxi = -1;
    dfs(v, 0, -1);
    maxi = -1;
    dfs(maxiV, 0, -1);
    return maxi;
}

void createSet(int x)
{
	parent[x] = x;
	rank[x] = 1;
	return;
}

int find(int x)
{
	if(parent[x] == x) return x;
	else return (parent[x] = find(parent[x]));
}

int merge(int x, int y)
{
	int xRank, yRank, xRep, yRep;
	xRep = find(x);
	yRep = find(y);
	xRank = rank[xRep];
	yRank = rank[yRep];


	if(xRep == yRep) return xRep;
	else if(xRank < yRank) return (parent[xRep] = yRep);
	else if(xRank > yRank) return (parent[yRep] = xRep);
	else {
		parent[yRep] = xRep;
		rank[xRep]++;
		return xRep;
	}
}