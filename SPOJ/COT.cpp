#include <cstdio>
#include <map>
#include <vector>
#include <cstring>
#include <algorithm>

#define MAX 100005
#define LOGMAX 19

using namespace std;

typedef struct node
{
	int count;
	node *left, *right;
	node(int count, node *left, node *right): count(count), left(left), right(right) {}
}node;

int n,weight[MAX], invcc[MAX], level[MAX], _index, seq[MAX], lcaDp[MAX][LOGMAX], parent[MAX];
vector<int> graph[MAX];
map<int, int> cc;
node *root[MAX], *zero = new node(0, NULL, NULL);

void computeLcaDp();
int lca(int u, int v);
void dfs(int u, int p);
int query(node *a, node *b, node *c, node *d, int left, int right, int k);
node* insert(node *curr, int left, int right, int w);
int read_int();

int main()
{
	int i,u,v,m,k,l,ans;
	n = read_int();
	m = read_int();
	for(i=0;i<n;i++) {
		weight[i] = read_int();
		seq[i] = weight[i];
	}
	//coordinate compression
	_index = 0;
	sort(seq, seq+n);
	cc[seq[0]] = 0;
	invcc[0] = seq[0];
	for(i=1;i<n;i++) 
		if(seq[i] != seq[i-1]) {
			cc[seq[i]] = ++_index;
			invcc[_index] = seq[i];
		}

	for(i=0;i<n-1;i++) {
		u = read_int();
		v = read_int();
		graph[u-1].push_back(v-1);
		graph[v-1].push_back(u-1);
	}

	zero->left = zero->right = zero;
	dfs(0, -1);
	computeLcaDp();

	while(m--)
	{
		u = read_int();
		v = read_int();
		k = read_int();
		u--; v--;
		l = lca(u, v);
		ans = query(root[u], root[v], root[l], (lcaDp[l][0] == -1 ? zero : root[ lcaDp[l][0] ]), 0, _index, k);
		printf("%d\n", invcc[ans]);
	}
}

void computeLcaDp()
{
	int i,j;
	for(i=1;i<=n;i++) lcaDp[i][0] = parent[i];
	for(i=0;i<LOGMAX;i++) lcaDp[0][i] = -1;
	for(j=1;j<LOGMAX;j++)
		for(i=1;i<=n;i++)
			lcaDp[i][j] = lcaDp[i][j-1] == -1?-1:lcaDp[lcaDp[i][j-1]][j-1];
}

int lca(int u, int v)
{
	int logu,i;
	if(level[u]<level[v]) u ^= v ^= u ^= v;
	for(logu = 0;(1<<logu)<=level[u];logu++);
	logu--;
	for(i=logu;i>=0;i--)
		if(level[u] - (1<<i) >= level[v]) 
			u = lcaDp[u][i];
	if(u == v) return u;
	for(i=logu;i>=0;i--)
		if(lcaDp[u][i] != -1 && lcaDp[u][i] != lcaDp[v][i]) {
			u = lcaDp[u][i];
			v = lcaDp[v][i];
		}
	return parent[u];
}

void dfs(int u, int p)
{
	int i;
	level[u] = (p == -1 ? 0 : level[p] + 1);
	parent[u] = p;
	root[u] = insert(p == -1 ? zero : root[p], 0, _index, cc[weight[u]]);
	for(i=0;i<graph[u].size();i++)
		if(graph[u][i] != p)
			dfs(graph[u][i], u);
}

int query(node *a, node *b, node *c, node *d, int left, int right, int k)
{
	int count = a->left->count + b->left->count - c->left->count - d->left->count, mid = (left+right)/2;
	if(left==right) return left;
	if(count >= k) return query(a->left, b->left, c->left, d->left, left, mid, k);
	return query(a->right, b->right, c->right, d->right, mid+1, right, k - count);
}

node* insert(node *curr, int left, int right, int w)
{
	int mid = (left+right)/2;
	if(left<=w && w<=right) {
		if(left == right) return new node(curr->count+1, zero, zero);
		return new node(curr->count+1, insert(curr->left, left, mid, w), insert(curr->right, mid+1, right, w));
	}
	return curr;
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
