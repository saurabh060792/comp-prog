#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <cstring>

#define MAX 300010

using namespace std;

struct vertex {
    int depth, lowest_depth_reachable, comp_id;
    bool visited;
};

void dfs(int u, int p);
void find_bridges();
void bridge(int u, int v);
void bridge_tree_dfs(int u, int id);
int find_2ecc();
int build_bridge_tree();
void path(int u, bool ans);
pair<int, int> to_edge(int u, int v);

int n, m;
vertex V[MAX];
vector<int> graph[MAX], tree[MAX];
map<pair<int, int>, bool> is_bridge, graph_edge_artifact, tree_edge_artifact;
map<int, bool> component_artifact;
bool res[MAX];

int main() {
    int u, v, w, bridge_tree_n;
    scanf("%d%d", &n, &m);
    for (int i = 0; i < m; i++) {
        scanf("%d%d%d", &u, &v, &w);
        graph[u].push_back(v);
        graph[v].push_back(u);
        graph_edge_artifact[to_edge(u, v)] = w ? true : false;
    }

    find_bridges();

    memset(V, 0, sizeof(V));
    bridge_tree_n = build_bridge_tree();

    for (int i = 0; i <= n; i++) V[i].visited = false;
    scanf("%d%d", &u, &v);
    path(V[u].comp_id, false);
    if (res[V[v].comp_id] && V[V[v].comp_id].visited) printf("YES\n");
    else printf("NO\n");
    return 0;
}

void dfs(int u, int p) {
    V[u].visited = true;
    V[u].lowest_depth_reachable = V[u].depth;
    for (auto v : graph[u]) {
        if (v == p) continue;
        if (V[v].visited) V[u].lowest_depth_reachable = min(V[u].lowest_depth_reachable, V[v].depth);
        else {
            V[v].depth = V[u].depth + 1;
            dfs(v, u);
            V[u].lowest_depth_reachable = min(V[u].lowest_depth_reachable, V[v].lowest_depth_reachable);
            if (V[v].lowest_depth_reachable > V[u].depth) bridge(u, v);
        }
    }
    return;
}

void find_bridges() {
    for (int i = 1; i <= n; i++) if (!V[i].visited) dfs(i, 0);
}

void bridge(int u, int v) {
    if (u > v) swap(u, v);
    is_bridge[ {u, v}] = true;
}

void bridge_tree_dfs(int u, int id) {
    V[u].visited = true;
    V[u].comp_id = id;
    for (auto v : graph[u]) {
        if (is_bridge[to_edge(u, v)]) continue;
        if (graph_edge_artifact[to_edge(u, v)]) component_artifact[id] = true;
        if (V[v].visited) continue;
        else bridge_tree_dfs(v, id);
    }
    return;
}

int find_2ecc() {
    int id = 1;
    for (int i = 1; i <= n; i++) if (!V[i].visited) bridge_tree_dfs(i, id++);
    return id - 1;
}

int build_bridge_tree() {
    int bridge_tree_n = find_2ecc(), u, v;
    for (auto i : graph_edge_artifact) {
        pair<int, int> edge = i.first;
        if (is_bridge[edge]) {
            int u = edge.first, v = edge.second;
            tree[V[u].comp_id].push_back(V[v].comp_id);
            tree[V[v].comp_id].push_back(V[u].comp_id);
            tree_edge_artifact[to_edge(V[u].comp_id, V[v].comp_id)] = graph_edge_artifact[edge];
        }
    }
    return bridge_tree_n;
}

// Aggregates answer along the path from u.
void path(int u, bool ans) {
    V[u].visited = true;
    ans |= component_artifact[u];
    for (auto v : tree[u]) {
        if (V[v].visited) continue;
        else path(v, ans | tree_edge_artifact[to_edge(u, v)]);
    }
    res[u] = ans;
    return;
}

pair<int, int> to_edge(int u, int v) {
    if (u < v) return make_pair(u, v);
    else return make_pair(v, u);
}
