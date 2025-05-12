#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <cstring>

#define MAX 100010

using namespace std;

struct vertex {
    int depth, lowest_depth_reachable, comp_id, degree;
    bool visited;
};

void dfs(int u, int p);
void find_bridges();
void bridge(int u, int v);
void bridge_tree_dfs(int u, int id);
int find_2ecc();
int build_bridge_tree();
pair<int, int> to_edge(int u, int v);

int n, m;
vertex V[MAX];
vector<int> graph[MAX], tree[MAX];
set<pair<int, int>> edges;
map<pair<int, int>, bool> is_bridge;

int main() {
    int u, v, w, bridge_tree_n, is_line = true;
    scanf("%d%d", &n, &m);
    for (int i = 0; i < m; i++) {
        scanf("%d%d", &u, &v);
        graph[u].push_back(v);
        graph[v].push_back(u);
        edges.insert(to_edge(u, v));
    }

    find_bridges();

    memset(V, 0, sizeof(V));
    bridge_tree_n = build_bridge_tree();

    for (int i = 1; i <= bridge_tree_n; i++) {
        if (V[i].degree > 2) {
            is_line = false;
            break;
        }
    }
    if (is_line) printf("YES\n");
    else printf("NO\n");

    return 0;
}

void dfs(int u, int p) {
    bool multiple_edges = false;
    V[u].visited = true;
    V[u].lowest_depth_reachable = V[u].depth;
    for (auto v : graph[u]) {
        if (v == p && !multiple_edges) {
            multiple_edges = true;
            continue;
        }
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
    for (auto e : edges) {
        if (is_bridge[e]) {
            int u = e.first, v = e.second;
            tree[V[u].comp_id].push_back(V[v].comp_id);
            tree[V[v].comp_id].push_back(V[u].comp_id);
            V[V[u].comp_id].degree++;
            V[V[v].comp_id].degree++;
        }
    }
    return bridge_tree_n;
}

pair<int, int> to_edge(int u, int v) {
    if (u < v) return make_pair(u, v);
    else return make_pair(v, u);
}
