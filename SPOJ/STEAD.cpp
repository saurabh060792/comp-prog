#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <vector>
#include <algorithm>

#define INF (1<<28)
#define NCOWS 1500
#define NBARN 30

using namespace std;


vector<int> edges[NCOWS];
int L[NCOWS], R[NCOWS];
bool visited[NCOWS];
int pref[NCOWS][NBARN], cap[NBARN];
int ncows, nbarn;

bool dfs(int u)
{
	if(visited[u]) return false;
	visited[u] = true;
	int len = edges[u].size(), i, v;
	for(i=0; i<len; i++) {
		v = edges[u][i];
		if(R[v]==-1) {
			R[v] = u, L[u] = v;
			return true;
		}
	}
	for(i=0; i<len; i++) {
		v = edges[u][i];
		if(dfs(R[v])) {
			R[v] = u, L[u] = v;
			return true;
		}
	}
	return false;
}


bool match()
{
	memset(L, -1, sizeof(L));
	memset(R, -1, sizeof(R));
	bool done;
	int i, ret = 0;
	do {
		done = true;
		memset(visited, 0, sizeof(visited));
		for(i=0; i<ncows; i++) {
			if(L[i]==-1 && dfs(i)) {
				done = false;
			}
		}
	} while(!done);
	for(i=0; i<ncows; i++) ret += (L[i]!=-1);
	return (ret == ncows);
}

bool isok(int rng)
{
	int i, j, c, p, b, ii, jj, k;
	for(i=0; i<nbarn; i++) {
		j = i+rng-1;
		//i denotes the highest ranked barn and j denotes
		//lowest ranked barn. Now we build a bipartite
		//graph with n cows in one set and barns on another.
		//Note that a barn with capacity c will come c number
		//of times
		if(j>=nbarn) break;
		for(c=0; c<ncows; c++) {
			edges[c].clear();
			for(p=i; p<=j; p++) {
				b = pref[c][p] - 1;
				ii = (b? cap[b-1] : 0);
				jj = cap[b]-1;
				for(k=ii; k<=jj; k++) {
					edges[c].push_back(k);
				}
			}
		}
		if(match()) return true;
	}
	return false;
}

int main()
{
	int i, j, l, r, m;
	scanf("%d %d", &ncows, &nbarn);
	for(i=0; i<ncows; i++)
		for(j=0; j<nbarn; j++)
			scanf("%d", &pref[i][j]);
	for(i=0; i<nbarn; i++) {
		scanf("%d",&cap[i]);
		if(i) cap[i] += cap[i-1];
	}

	l = 1; r = nbarn;
	while(l <= r) {
		m = (l+r)>>1;
		if(isok(m)) r = m-1;
		else l = m+1;
	}

	printf("%d\n", r+1);
	return 0;
}