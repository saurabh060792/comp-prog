#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <cstring>

#define MAX 200010
#define MAXLOG 20
#define MOD 1000000007

using namespace std;

typedef long long int lli;

struct vertex {
    int depth, up_back_edge_vertex, down_back_edge_vertex, cycle_id;
    bool visited;
};

struct tree_vertex {
    int depth, color, parent, colors_till_root;
};

void dfs(int u, int p);
void update_back_edge_map(int u, int v);
int cordinate_compression();
void build_ancestor_table(tree_vertex *V, int n);
int log2_floor(int n);
int lca(tree_vertex *V, int x, int y);
void tree_dfs(int u, int p);
lli pow(lli a, lli exp);

int n, m, id, modified_n, cc_numbers[MAX], ancestor[MAXLOG][MAX];
vertex V[MAX];
tree_vertex tV[MAX];
vector<int> graph[MAX], modified_graph[MAX];
map<pair<int, int>, int> back_edge_vertices_to_id;
map<int, int> cc;

// https://codeforces.com/blog/entry/68138
int main() {
    int q, u, v, tu, tv, tl;
    lli ans, colors_in_path;
    scanf("%d%d", &n, &m);
    id = n + 1;
    for (int i = 0; i < m; i++) {
        scanf("%d%d", &u, &v);
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    dfs(1, 0);

    modified_n = cordinate_compression();

    for (u = 1; u <= n; u++) {
        if (V[u].cycle_id > n) tV[cc[V[u].cycle_id]].color = 1;
        for (auto v : graph[u]) {
            if (V[v].cycle_id == V[u].cycle_id) continue;
            modified_graph[cc[V[u].cycle_id]].push_back(cc[V[v].cycle_id]);
        }
    }

    tree_dfs(1, 0);

    build_ancestor_table(tV, modified_n);

    scanf("%d", &q);
    while (q--) {
        scanf("%d%d", &u, &v);
        tu = cc[V[u].cycle_id];
        tv = cc[V[v].cycle_id];
        tl = lca(tV, tu, tv);
        colors_in_path = tV[tu].colors_till_root
                         + tV[tv].colors_till_root
                         - (2LL * tV[tl].colors_till_root)
                         + tV[tl].color;
        ans = pow(2LL, colors_in_path);
        printf("%lld\n", ans);
    }

    return 0;
}

void dfs(int u, int p) {
    V[u].visited = true;
    for (int v : graph[u]) {
        if (v == p) continue;
        if (V[v].visited) {
            update_back_edge_map(u, v);
            if (V[v].depth > V[u].depth) V[u].down_back_edge_vertex = v;
            else V[u].up_back_edge_vertex = v;
        }
        else {
            V[v].depth = V[u].depth + 1;
            dfs(v, u);
        }
    }

    if (V[u].up_back_edge_vertex) {
        V[u].cycle_id = u < V[u].up_back_edge_vertex ?
                        back_edge_vertices_to_id[ {u, V[u].up_back_edge_vertex}] :
                        back_edge_vertices_to_id[ {V[u].up_back_edge_vertex, u}];
    } else {
        V[u].cycle_id = u;
        for (int v : graph[u]) {
            if (v == p) continue;
            if (V[v].cycle_id != v && V[v].down_back_edge_vertex == 0)
                V[u].cycle_id = V[v].cycle_id;
        }
    }
    return;
}

void update_back_edge_map(int u, int v) {
    if (u > v) swap(u, v);
    if (back_edge_vertices_to_id.find({u, v}) == back_edge_vertices_to_id.end())
        back_edge_vertices_to_id[ {u, v}] = id++;
}

void tree_dfs(int u, int p) {
    for (int v : modified_graph[u]) {
        if (v == p) continue;
        tV[v].depth = tV[u].depth + 1;
        tV[v].parent = u;
        tV[v].colors_till_root = tV[u].colors_till_root + tV[v].color;
        tree_dfs(v, u);
    }
    return;
}

int cordinate_compression() {
    for (int i = 1; i <= n; i++) cc_numbers[i - 1] = V[i].cycle_id;
    sort(cc_numbers, cc_numbers + n);
    cc[cc_numbers[0]] = 1;
    int index = 2;
    for (int i = 1; i < n; i++)
        if (cc_numbers[i] != cc_numbers[i - 1]) cc[cc_numbers[i]] = index++;
    return index - 1;
}

int log2_floor(int n) {
    return n ? __builtin_clzll(1) - __builtin_clzll(n) : -1;
}

void build_ancestor_table(tree_vertex *V, int n) {
    int k = log2_floor(n);
    for (int i = 2; i <= n; i++) ancestor[0][i] = V[i].parent;
    for (int i = 1; i <= k; i++)
        for (int j = 2; j <= n; j++)
            ancestor[i][j] = ancestor[i - 1][ancestor[i - 1][j]];
}

int lca(tree_vertex *V, int x, int y) {
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

lli pow(lli a, lli exp) {
    lli ans = 1;
    while (exp > 0) {
        if (exp & 1) ans = (ans * a) % MOD;
        a = (a * a) % MOD;
        exp >>= 1;
    }
    return ans;
}
