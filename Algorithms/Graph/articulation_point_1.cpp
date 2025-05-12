#include <iostream>
#include <vector>
#include <set>
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

void dfs(int u, int p);
void find_articulation_points();

int n, m;
vertex V[MAX];
vector<int> graph[MAX];
set<int> articulation_points;

int main() {
    int u, v;
    while (scanf("%d%d", &n, &m) && (n || m)) {
        memset(V, 0, sizeof(V));
        for (int i = 0; i < MAX; i++) graph[i].clear();
        articulation_points.clear();
        for (int i = 0; i < m; i++) {
            scanf("%d%d", &u, &v);
            graph[u].push_back(v);
            graph[v].push_back(u);
        }
        find_articulation_points();
        printf("%d\n", articulation_points.size());
    }
    return 0;
}

void dfs(int u, int p) {
    int children = 0;
    V[u].visited = true;
    V[u].lowest_depth_reachable = V[u].depth;
    for (int v : graph[u]) {
        if (v == p) continue;
        if (V[v].visited) {
            // If v is decendant of u then u's lowest_depth_reachable
            // will be unchanged otherwise when v is an ancestor of u
            // then lowest_depth_reachable will be changed to v's depth.
            V[u].lowest_depth_reachable =
                min(V[u].lowest_depth_reachable, V[v].depth);
        }
        else {
            children++;
            V[v].depth = V[u].depth + 1;
            dfs(v, u);
            V[u].lowest_depth_reachable =
                min(V[u].lowest_depth_reachable, V[v].lowest_depth_reachable);
            // If lowest_depth_reachable for v is equal to u's depth then
            // that using back edge from v or any of its decendants, we can
            // go as deep as u, so u is an articulation point.
            if (V[v].lowest_depth_reachable >= V[u].depth && p != 0) articulation_points.insert(u);
        }
    }
    if (p == 0 && children > 1) articulation_points.insert(u);
    return;
}

void find_articulation_points() {
    for (int i = 1; i <= n; i++) if (!V[i].visited) dfs(i, 0);
}
