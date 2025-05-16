#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <cstring>

#define MAX 100010
#define MAXLOG 20

using namespace std;

struct vertex {
    int depth, lowest_depth_reachable, parent, comp_id;
    bool visited;
};

void dfs(int u, int p);
void tree_dfs(int u, int p);
void find_bcc();
int build_block_cut_tree();
void build_ancestor_table(int n);
int log2_floor(int n);
int lca(int x, int y);
bool on_path(int a, int b, int c);

int n, m, block_cut_tree_n, ancestor[MAXLOG][2 * MAX];
bool is_articulation_point[MAX];
vertex V[2 * MAX];
vector<int> graph[MAX], tree[2 * MAX];
vector<vector<int>> components;
stack<int> stk;

int main() {
    int u, v, q, a, b, c;
    scanf("%d%d%d", &n, &m, &q);
    for (int i = 0; i < m; i++) {
        scanf("%d%d", &u, &v);
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    find_bcc();
    block_cut_tree_n = build_block_cut_tree();

    for (int i = 0; i <= block_cut_tree_n; i++) V[i].visited = false, V[i].depth = 0;
    for (int i = 1; i <= block_cut_tree_n; i++) if (!V[i].visited) tree_dfs(i, 0);
    build_ancestor_table(block_cut_tree_n);

    while (q--) {
        scanf("%d%d%d", &a, &b, &c);
        if (a == c || b == c ||
                (is_articulation_point[c] && on_path(V[a].comp_id, V[b].comp_id, V[c].comp_id)))
            printf("NO\n");
        else printf("YES\n");
    }

    return 0;
}

void dfs(int u, int p) {
    int children = 0;
    stk.push(u);
    V[u].visited = true;
    V[u].lowest_depth_reachable = V[u].depth;
    for (int v : graph[u]) {
        if (v == p) continue;
        if (V[v].visited) V[u].lowest_depth_reachable = min(V[u].lowest_depth_reachable, V[v].depth);
        else {
            children++;
            V[v].depth = V[u].depth + 1;
            dfs(v, u);
            V[u].lowest_depth_reachable = min(V[u].lowest_depth_reachable, V[v].lowest_depth_reachable);
            if (V[v].lowest_depth_reachable >= V[u].depth) {
                is_articulation_point[u] = children > 1 || p != 0;
                components.push_back({u});
                while (components.back().back() != v) {
                    components.back().push_back(stk.top());
                    stk.pop();
                }
            }
        }
    }

    // Isolated single vertex.
    if (p == 0 && children == 0) components.push_back({u});
    return;
}

void find_bcc() {
    for (int i = 1; i <= n; i++) if (!V[i].visited) dfs(i, 0);
}

int build_block_cut_tree() {
    int id = 1;
    for (int u = 1; u <= n; u++) if (is_articulation_point[u]) V[u].comp_id = id++;

    for (auto &comp : components) {
        for (auto u : comp) {
            if (!is_articulation_point[u]) V[u].comp_id = id;
            else {
                tree[id].push_back(V[u].comp_id);
                tree[V[u].comp_id].push_back(id);
            }
        }
        id++;
    }
    return id - 1;
}

void tree_dfs(int u, int p) {
    V[u].visited = true;
    for (int v : tree[u]) {
        if (v == p) continue;
        else {
            V[v].parent = u;
            V[v].depth = V[u].depth + 1;
            tree_dfs(v, u);
        }
    }
    return;
}

int log2_floor(int n) {
    return n ? __builtin_clzll(1) - __builtin_clzll(n) : -1;
}

void build_ancestor_table(int n) {
    int k = log2_floor(n);
    for (int i = 2; i <= n; i++) ancestor[0][i] = V[i].parent;
    for (int i = 1; i <= k; i++)
        for (int j = 2; j <= n; j++)
            ancestor[i][j] = ancestor[i - 1][ancestor[i - 1][j]];
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
    return ancestor[0][x];
}

bool on_path(int a, int b, int c) {
    int lca_ab = lca(a, b), lca_ac = lca(a, c), lca_bc = lca(b, c);
    if (lca_ab == c || (lca_ac == c && lca_ab == lca_bc) || (lca_bc == c && lca_ab == lca_ac))
        return true;
    return false;
}