#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <climits>

using namespace std;

#define MAX 400005
#define MAXLOG 20

typedef long long int lli;
typedef pair<lli, lli> pll;

struct vertex {
    int parent, depth;
    lli up_weight;  // weight from this node to is parent.
};

struct edge {
    lli w;
    int u, v, id;
    bool operator<(const struct edge& e) { return w < e.w; }
};

struct dsu {
    vector<int> parent, size;

    dsu(int n) {
        parent.resize(n);
        for (int i = 0; i < n; i++) parent[i] = i;
        size.resize(n, 0);
    }

    void union_sets(int u, int v) {
        int pu, pv;
        pu = find_set(u);
        pv = find_set(v);
        if (pu == pv) return;
        if (size[pu] < size[pv]) swap(pu, pv);
        parent[pv] = pu;
        size[pu] += size[pv];
        return;
    }

    int find_set(int v) {
        if (v == parent[v]) return v;
        return parent[v] = find_set(parent[v]);
    }
};

lli kruskal();
void dfs(int u, int p);
void build_ancestor_table(vertex *V, int n);
void build_sparse_table(vertex *V, int n);
int log2_floor(int n);
int lca(vertex *V, int x, int y);
int get_max_to_ancestor(vertex *V, int x, int anc);

vertex V[MAX];
edge edges[MAX];
bool present_in_mst[MAX];
int n, m, ancestor[MAXLOG][MAX], maximum[MAXLOG][MAX];
vector<pair<int, lli>> mst[MAX];
lli ans[MAX];

int main() {
    int u, v, l;
    lli w, mst_w;
    scanf("%d%d", &n, &m);
    for (int i = 0; i < m ; i++) {
        scanf("%d%d%lld", &u, &v, &w);
        edges[i] = {w, u, v, i};
    }

    mst_w = kruskal();
    dfs(1, 0);
    build_ancestor_table(V, n);
    build_sparse_table(V, n);

    for (int i = 0; i < m; i++) {
        if (present_in_mst[edges[i].id]) ans[edges[i].id] = mst_w;
        else {
            u = edges[i].u;
            v = edges[i].v;
            l = lca(V, u, v);
            w = max(get_max_to_ancestor(V, u, l), get_max_to_ancestor(V, v, l));
            ans[edges[i].id] =  mst_w + edges[i].w - w;
        }
    }

    // Second best MST will be minimum value in ans array that is not equal to mst_w.
    for (int i = 0; i < m; i++) printf("%lld\n", ans[i]);

    return 0;
}

lli kruskal() {
    lli w = 0;
    int u, v, pu, pv, id;
    sort(edges, edges + m);
    dsu d(n + 10);
    for (int i = 0; i < m; i++) {
        u = edges[i].u;
        v = edges[i].v;
        pu = d.find_set(u);
        pv = d.find_set(v);
        if (pu != pv) {
            d.union_sets(pu, pv);
            w += edges[i].w;
            id = edges[i].id;
            present_in_mst[id] = true;
            mst[u].push_back({v, edges[i].w});
            mst[v].push_back({u, edges[i].w});
        }
    }
    return w;
}

void dfs(int u, int p) {
    int v;
    lli w;
    for (auto i : mst[u]) {
        v = i.first;
        w = i.second;
        if (v == p) continue;
        V[v].depth = V[u].depth + 1;
        V[v].parent = u;
        V[v].up_weight = w;
        dfs(v, u);
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
    for (int i = 2; i <= n; i++) maximum[0][i] = V[i].up_weight;
    for (int i = 1; i <= k; i++)
        for (int j = 2; j <= n; j++)
            maximum[i][j] = max(maximum[i - 1][j], maximum[i - 1][ancestor[i - 1][j]]);
}

int get_max_to_ancestor(vertex *V, int x, int anc) {
    int lg, k, max_weight = -1;
    k = V[x].depth - V[anc].depth;
    lg = log2_floor(k);
    for (int i = lg; i >= 0; i--) {
        if (k >= (1 << i)) {
            max_weight = max(max_weight, maximum[i][x]);
            x = ancestor[i][x];
            k -= (1 << i);
        }
    }
    return max_weight;
}

int lca(vertex *V, int x, int y) {
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
    return ancestor[0][x];
}
