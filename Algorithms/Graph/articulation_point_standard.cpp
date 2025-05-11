#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <cstring>

#define MAX 10010

using namespace std;

struct vertex {
    int entry_time, lowest_entry_time;
    bool visited;
};

int dfs(int u, int p, int time);
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

// See comments in bridge.cpp
int dfs(int u, int p, int time) {
    V[u].visited = true;
    V[u].entry_time = time;
    V[u].lowest_entry_time = time;
    int children = 0;
    for (int v : graph[u]) {
        if (v == p) continue;
        if (V[v].visited) V[u].lowest_entry_time = min(V[u].lowest_entry_time, V[v].entry_time);
        else {
            time = dfs(v, u, time + 1);
            children++;
            V[u].lowest_entry_time = min(V[u].lowest_entry_time, V[v].lowest_entry_time);
            // Couple of changes from detecting bridge:
            // 1. Ignore root of DFS as we are special casing it at the end.
            // 2. u will be articulation point if (u, v) is a bridge. However it is also an
            //    articulation point if lowest_entry_point[v] == entry_time[u] because
            //    u and all of its children and decendants can reach at most as high as exactly u
            //    so if we remove u then it will disconnect the graph. In finding bridges, the
            //    same logic doesn't work because if we remove edge (u, v) then we can still reach
            //    u and all other vertics from u.
            if (V[v].lowest_entry_time >= V[u].entry_time && p != -1)
              // We have to use set becuase u can be a part of multiple bridges lets say v1 and v2.
              // So we will get in this if condition for both edges (u, v1) and (u, v2). Both times
              // we will dectect u as articulation point. So to remove duplicates we use set here.
              // Eg:
              // (2)----(3)--(4)
              //  |    / |
              //  |  /   |
              // (1)    (5)
              // In this graph 3 will be detected as articulation point twice. One for bridge (3,4)
              // and one for bridge (3, 5).
              articulation_points.insert(u);
        }
    }

    // Special case for root of DFS. If it has more than 1 children
    // it is an articulation point.
    if (p == -1 && children > 1) articulation_points.insert(u);
    return time;
}

void find_articulation_points() {
    for (int u = 1; u <= n; u++) if (!V[u].visited) dfs(u, -1, 0);
}
