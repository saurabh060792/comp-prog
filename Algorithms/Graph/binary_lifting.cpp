#include <iostream>
#include <vector>
#include <stack>
#include <cstring>

#define INF 1000000010
#define MAX 300010
#define MAXLOG 20
#define UNEXPLORED 0
#define EXPLORING 1
#define EXPLORED 2
#define INVALID -1

using namespace std;

typedef long long int lli;

struct vertex {
    int status, parent, depth, up_weight;  // weight from this node to is parent.
};

void dfs(int start_vertex);
void build_ancestor_table(vertex *V, int n);
void build_sparse_table(vertex *V, int n);
int log2_floor(int n);
int lca(int x, int y);
int get_min_to_ancestor(int x, int anc);

vertex V[MAX];
int ancestor[MAXLOG][MAX], minimum[MAXLOG][MAX];
vector<pair<int, int>> adjacency_graph[MAX];

int n;

int main() {
    memset(minimum, INF, sizeof(minimum));
    int m, q, u, v, w, l;
    scanf("%d%d", &n, &m);
    for (int i = 1; i < n; i++) {
        scanf("%d%d%d", &u, &v, &w);
        adjacency_graph[u].push_back({v, w});
        adjacency_graph[v].push_back({u, w});
    }

    dfs(1);
    build_ancestor_table(V, n);
    build_sparse_table(V, n);

    scanf("%d", &q);
    while (q--) {
        scanf("%d%d", &u, &v);
        l = lca(u, v);
        printf("%d\n", min(get_min_to_ancestor(u, l), get_min_to_ancestor(v, l)));
    }
}

void dfs(int start_vertex) {
    int u;
    stack<int> S;
    for (int i = 1; i <= n; i++) V[i].status = UNEXPLORED;
    V[start_vertex].parent = 0;
    V[start_vertex].status = EXPLORING;
    V[start_vertex].depth = 0;
    V[start_vertex].up_weight = INF;
    S.push(start_vertex);
    while (!S.empty()) {
        u = S.top();
        S.pop();
        for (pair<int, int> v : adjacency_graph[u]) {
            if (V[v.first].status == UNEXPLORED) {
                V[v.first].parent = u;
                V[v.first].depth = V[u].depth + 1;
                V[v.first].status = EXPLORING;
                V[v.first].up_weight = v.second;
                S.push(v.first);
            }
        }
        V[u].status = EXPLORED;
    }
    return;
}

int log2_floor(int n) {
    return n ? __builtin_clzll(1) - __builtin_clzll(n) : -1;
}

void build_ancestor_table(vertex *V, int n) {
    int k = log2_floor(n);
    for (int i = 2; i <= n; i++) ancestor[0][i] = V[i].parent;
    for (int i = 1; i <= k; i++)
        for (int j = 2; j <= n; j++)
            ancestor[i][j] = ancestor[i - 1][ancestor[i - 1][j]];
}

void build_sparse_table(vertex *V, int n) {
    int k = log2_floor(n);
    for (int i = 2; i <= n; i++) minimum[0][i] = V[i].up_weight;
    for (int i = 1; i <= k; i++)
        for (int j = 2; j <= n; j++)
            minimum[i][j] = min(minimum[i - 1][j], minimum[i - 1][ancestor[i - 1][j]]);
}

// Get the min along the path from x to its ancestor anc.
// This function assumes that anc is an ancestor of x.
int get_min_to_ancestor(int x, int anc) {
    int lg, k, min_weight = INF;
    k = V[x].depth - V[anc].depth;
    lg = log2_floor(k);
    // This loop try to take as large a jump it can
    // without passing anc and take min along the path.
    // In this loop's if condition, we allow x to
    // finally become anc.
    for (int i = lg; i >= 0; i--) {
        if (k >= (1 << i)) {
            min_weight = min(min_weight, minimum[i][x]);
            x = ancestor[i][x];
            k -= (1 << i);
        }
    }
    return min_weight;
}

int lca(int x, int y) {
    int k;
    if (V[x].depth < V[y].depth) swap(x, y);
    k = log2_floor(V[x].depth - V[y].depth);
    for (int i = k; i >= 0; i--)
        if (V[x].depth - (1 << i) >= V[y].depth)
            x = ancestor[i][x];
    if (x == y) return x;
    k = log2_floor(V[x].depth);
    for (int i = k; i >= 0; i--) {
        if (ancestor[i][x] != ancestor[i][y]) {
            x = ancestor[i][x];
            y = ancestor[i][y];
        }
    }
    // This if condition ancestor[i][x] != ancestor[i][y] forces
    // x and y to be never equal. So if they are more than 1 distance
    // farther than lca then if condition will be satisfied and they
    // move up. Hence after the loop they will be only one distance 
    // away from lca.
    //
    // We have to code it that way because ancestor[i][x] == ancestor[i][y]
    // is satisfied by lca and all of lca's ancestors.
    return ancestor[0][x];
}
