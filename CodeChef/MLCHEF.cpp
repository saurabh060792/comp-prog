#include <iostream>
#include <vector>
#include <cstdlib>
#include <cstdio>

#define MAXARRAY 100005
#define MAXTREE 262160
#define INF 2000000000

using namespace std;


typedef struct segmentTree
{
	int lazy, health, alive;				//lazy will be positive
}segmentTree;

void buildST(int *A, int currentNode, int low, int high);
void updateST(int currentNode, int low, int high, int a, int b, int value);
int queryST(int currentNode, int low, int high, int a, int b);
void dfs(int u);

int visited[MAXARRAY], health[MAXARRAY], dfsOrder[MAXARRAY], timer, end[MAXARRAY], start[MAXARRAY];
vector<int> tree[MAXARRAY];

segmentTree S[MAXTREE];

int main()
{
	int qt,a,x,n,q,i,j,t;
	scanf("%d",&n);
	timer = 0;
	visited[0] = 0;
	health[0] = INF;
	for(i=1;i<=n;i++) {
		scanf("%d%d",&health[i],&t);
		tree[i].push_back(t);
		tree[t].push_back(i);
		visited[i] = 0;
	}

	dfs(0);
	buildST(dfsOrder, 0, 0, n);
	scanf("%d",&q);
	for(i=0;i<q;i++) {
		scanf("%d",&qt);
		if(qt == 1) {
			scanf("%d%d",&a,&x);
			if(start[a]+1<=end[a]) updateST(0, 0, n, start[a]+1, end[a], x);
		}
		else if(qt == 2) {
			scanf("%d",&a);
			if(start[a]+1<=end[a]) printf("%d\n",queryST(0, 0, n, start[a]+1, end[a]));
			else printf("0\n");
		}
	}

	return 0;
}

void dfs(int u)
{
	int i;
	dfsOrder[timer] = u;
	start[u] = timer++;
	visited[u] = 1;
	for(i=0;i<tree[u].size();i++)
		if(!visited[tree[u][i]]) {
			dfs(tree[u][i]);
		}
	end[u] = timer-1;
}

void buildST(int *A, int currentNode, int low, int high)
{
	int leftNode, rightNode, mid;

	leftNode = 2*currentNode + 1;
	rightNode = 2*currentNode + 2;
	mid = (low + high)/2;

	if(low == high) {
		S[currentNode].health = health[A[low]];
		S[currentNode].alive = 1;
		S[currentNode].lazy = 0;
		return;
	}

	buildST(A, leftNode, low, mid);
	buildST(A, rightNode, mid + 1, high);
	S[currentNode].health = min(S[leftNode].health, S[rightNode].health);
	S[currentNode].alive = S[leftNode].alive + S[rightNode].alive;
	S[currentNode].lazy = 0;
	return;
}

void updateST(int currentNode, int low, int high, int a, int b, int value)
{
	int leftNode, rightNode, mid;
	
	leftNode = 2*currentNode + 1;
	rightNode = 2*currentNode + 2;
	mid = (low + high)/2;

	if(S[currentNode].lazy) {							//lazy field is set so we need to update this node and push laziness to its children
		S[currentNode].health -= S[currentNode].lazy;
		if(low != high) {								//if this node is not leaf then push laziness to the children
			S[leftNode].lazy += S[currentNode].lazy;
			S[rightNode].lazy += S[currentNode].lazy;
		}
		S[currentNode].lazy = 0;						//reset lazy field
	}

	if(a > high || b < low) return;
	else if(a <= low && b >= high) {
		S[currentNode].health -= value;
		if(low != high) {								//if this node is not leaf node then update only this node and push laziness to its children
			S[leftNode].lazy += value;
			S[rightNode].lazy += value;
		}
		return;
	}

	updateST(leftNode, low, mid, a, b, value);
	updateST(rightNode, mid + 1, high, a, b, value);
	S[currentNode].health = min(S[leftNode].health, S[rightNode].health);
	return;
}

int queryST(int currentNode, int low, int high, int a, int b)
{
	int leftNode, rightNode, mid, r1, r2;
	
	leftNode = 2*currentNode + 1;
	rightNode = 2*currentNode + 2;
	mid = (low + high)/2;

	if(S[currentNode].lazy) {
		S[currentNode].health -= S[currentNode].lazy;
		if(low != high) {
			S[leftNode].lazy += S[currentNode].lazy;
			S[rightNode].lazy += S[currentNode].lazy;			
		}
		S[currentNode].lazy = 0;
	}

	if(a > high || b < low) return 0;
	else if(low == high) {
		if(S[currentNode].health > 0) return S[currentNode].alive;
		S[currentNode].health = INF;
		S[currentNode].alive = 0;	
		return 0;
	}
	else if(a <= low && b >= high) {
		if(S[currentNode].health <= 0) {
			queryST(leftNode, low, mid, a, b);
			queryST(rightNode, mid + 1, high, a, b);
			S[currentNode].alive = S[leftNode].alive + S[rightNode].alive;
			S[currentNode].health = min(S[leftNode].health, S[rightNode].health);
		}
		return S[currentNode].alive;
	}

	r1 = queryST(leftNode, low, mid, a, b);
	r2 = queryST(rightNode, mid + 1, high, a, b);
	S[currentNode].alive = S[leftNode].alive + S[rightNode].alive;
	S[currentNode].health = min(S[leftNode].health, S[rightNode].health);
	return r1 + r2;
}