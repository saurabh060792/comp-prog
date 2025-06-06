#include <iostream>
#include <vector>
#include <stack>

#define MAX 300010
#define MAXLOG 20
#define UNEXPLORED 0
#define EXPLORING 1
#define EXPLORED 2

using namespace std;

typedef long long int lli;

void dfs(int start_vertex);
void build_ancestor_table(int *a, int n);
int log2_floor(int n);
int lca(int x, int y);
int kth_ancestor(int x, int k);

int ancestor[MAXLOG][MAX], depth[MAX], parent[MAX], status[MAX];
vector<int> adjacency_graph[MAX];

int n;

int main() {
    int q, u, v, a, b, c, l, ab, al, bl;
    scanf("%d", &n);
    for (int i = 1; i < n; i++) {
        scanf("%d%d", &u, &v);
        adjacency_graph[u].push_back(v);
        adjacency_graph[v].push_back(u);
    }

    dfs(1);
    build_ancestor_table(parent, n);

    scanf("%d", &q);
    while (q--) {
        scanf("%d%d%d", &a, &b, &c);
        l = lca(a, b);
        ab = depth[a] + depth[b] - 2 * depth[l];
        if (ab <= c) {
            printf("%d\n", b);
            continue;
        }

        al = depth[a] - depth[l];
        if (al == c) {
            printf("%d\n", l);
            continue;
        } else if (al > c) {
            printf("%d\n", kth_ancestor(a, c));
            continue;
        }

        bl = depth[b] - depth[l];
        printf("%d\n", kth_ancestor(b, ab - c));
    }
}

void dfs(int start_vertex) {
    int u;
    stack<int> S;
    for (int i = 1; i <= n; i++) status[i] = UNEXPLORED;
    parent[start_vertex] = 0;
    status[start_vertex] = EXPLORING;
    depth[start_vertex] = 0;
    S.push(start_vertex);
    while (!S.empty()) {
        u = S.top();
        S.pop();
        for (int v : adjacency_graph[u]) {
            if (status[v] == UNEXPLORED) {
                parent[v] = u;
                depth[v] = depth[u] + 1;
                status[v] = EXPLORING;
                S.push(v);
            }
        }
        status[u] = EXPLORED;
    }
    return;
}

int log2_floor(int n) {
    return n ? __builtin_clzll(1) - __builtin_clzll(n) : -1;
}

void build_ancestor_table(int *a, int n) {
    int k = log2_floor(n);
    for (int i = 2; i <= n; i++) ancestor[0][i] = a[i];
    for (int i = 1; i <= k; i++)
        for (int j = 2; j <= n; j++)
            ancestor[i][j] = ancestor[i - 1][ancestor[i - 1][j]];
}

int lca(int x, int y) {
    int k;
    if (depth[x] < depth[y]) swap(x, y);
    k = log2_floor(depth[x] - depth[y]);
    for (int i = k; i >= 0; i--)
        if (depth[x] - (1 << i) >= depth[y])
            x = ancestor[i][x];
    if (x == y) return x;
    k = log2_floor(depth[x]);
    for (int i = k; i >= 0; i--) {
        if (ancestor[i][x] != ancestor[i][y]) {
            x = ancestor[i][x];
            y = ancestor[i][y];
        }
    }
    return ancestor[0][x];
}

int kth_ancestor(int x, int k) {
    int lg = log2_floor(k);
    for (int i = lg; i >= 0; i--)
        if (k >= (1 << i)) {
            x = ancestor[i][x];
            k -= (1 << i);
        }
    if (x == 0) return -1;
    else return x;
}
