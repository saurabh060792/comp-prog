#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cstring>

#define MAX 100010

using namespace std;

struct vertex {
    // Lowest depth vertex (ie highest vertex in a tree) reachable
    // using back edge by this vertex or its decendants in a DFS tree.
    int depth, lowest_depth_reachable;
    bool visited;
};

void bridge(int u, int v);
int dfs(int u, int p, int time);
void find_bridges();

int n, m;
vertex V[MAX];
vector<int> graph[MAX];
vector<pair<int, int>> critical_edges;

int main() {
    int t, u, v;
    scanf("%d", &t);
    for (int test_case = 1; test_case <= t; test_case++) {
        scanf("%d%d", &n, &m);
        for (int i = 0; i <= n; i++) graph[i].clear();
        critical_edges.clear();
        memset(V, 0, sizeof(V));
        for (int i = 0; i < m; i++) {
            scanf("%d%d", &u, &v);
            graph[u].push_back(v);
            graph[v].push_back(u);
        }
        find_bridges();
        sort(critical_edges.begin(), critical_edges.end());
        printf("Caso #%d\n", test_case);
        if (critical_edges.size() > 0) printf("%d\n", critical_edges.size());
        else printf("Sin bloqueos\n");
        for (int i = 0; i < critical_edges.size(); i++)
            printf("%d %d\n", critical_edges[i].first, critical_edges[i].second);
    }
    return 0;
}

void dfs(int u, int p) {
    V[u].visited = true;
    V[u].lowest_depth_reachable = V[u].depth;
    for (int v : graph[u]) {
        if (v == p) continue;
        if (V[v].visited) {
            // If v is decendant of u then u's lowest_depth_reachable
            // will be unchanged otherwise when v is an ancestor of u
            // then lowest_depth_reachable might change to v's depth 
            // based on values.
            V[u].lowest_depth_reachable = min(V[u].lowest_depth_reachable, V[v].depth);
        }
        else {
            V[v].depth = V[u].depth + 1;
            dfs(v, u);
            V[u].lowest_depth_reachable = min(V[u].lowest_depth_reachable, V[v].lowest_depth_reachable);
            // If lowest_depth_reachable for v is below u's depth then
            // that mean there is no back edge from v or any of its decendants
            // that goes over edge (v, u) so this edge is a bridge.
            if (V[v].lowest_depth_reachable > V[u].depth) bridge(u, v);
        }
    }
    return;
}

void find_bridges() {
    for (int i = 1; i <= n; i++) if (!V[i].visited) dfs(i, -1);
}

void bridge(int u, int v) {
    if (u > v) swap(u, v);
    critical_edges.push_back({u, v});
}
