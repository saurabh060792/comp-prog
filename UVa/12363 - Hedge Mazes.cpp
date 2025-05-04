#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cstring>

#define MAX 100010

using namespace std;

struct vertex {
    int entry_time, lowest_entry_time;
    bool visited;
};

int dfs(int u, int p, int time);
void find_bridges();
void make_dsu_set(int u);
int find_dsu_set(int u);
void union_dsu_sets(int a, int b);

int n, m, dsu_parent[MAX], dsu_size[MAX];
vertex V[MAX];
vector<int> graph[MAX];
vector<pair<int, int>> bridges;

int main() {
    int u, v, q;
    while (scanf("%d%d%d", &n, &m, &q) && (n || m || q)) {
        memset(dsu_parent, 0, sizeof(dsu_parent));
        memset(dsu_size, 0, sizeof(dsu_size));
        memset(V, 0, sizeof(V));
        for (int i = 0; i < MAX; i++) graph[i].clear();
        bridges.clear();
        for (int i = 0; i < m; i++) {
            scanf("%d%d", &u, &v);
            graph[u].push_back(v);
            graph[v].push_back(u);
        }

        find_bridges();

        for (int i = 1; i <= n; i++) make_dsu_set(i);
        for (auto e : bridges) union_dsu_sets(e.first, e.second);

        for (int i = 0; i < q; i++) {
            scanf("%d%d", &u, &v);
            printf("%c\n", find_dsu_set(u) == find_dsu_set(v) ? 'Y' : 'N');
        }
        printf("-\n");
    }
    return 0;
}

int dfs(int u, int p, int time) {
    V[u].visited = true;
    V[u].entry_time = time;
    V[u].lowest_entry_time = time;
    for (int v : graph[u]) {
        if (v == p) continue;
        // Back edge
        if (V[v].visited) V[u].lowest_entry_time = min(V[u].lowest_entry_time, V[v].entry_time);
        // Tree edge
        else {
            time = dfs(v, u, time + 1);
            V[u].lowest_entry_time = min(V[u].lowest_entry_time, V[v].lowest_entry_time);
            if (V[v].lowest_entry_time > V[u].entry_time) bridges.push_back({u, v});
        }
    }
    return time;
}

void find_bridges() {
    for (int u = 1; u <= n; u++) if (!V[u].visited) dfs(u, -1, 0);
}

void make_dsu_set(int u) {
    dsu_parent[u] = u;
    dsu_size[u] = 1;
}

int find_dsu_set(int u) {
    if (u == dsu_parent[u]) return u;
    return dsu_parent[u] = find_dsu_set(dsu_parent[u]);
}

void union_dsu_sets(int u, int v) {
    u = find_dsu_set(u);
    v = find_dsu_set(v);
    if (u != v) {
        if (dsu_size[u] < dsu_size[v]) swap(u, v);
        dsu_parent[v] = u;
        dsu_size[u] += dsu_size[v];
    }
}
