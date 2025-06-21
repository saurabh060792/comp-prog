#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

#define MAX 400005

typedef long long int lli;
typedef pair<lli, lli> pll;

typedef struct vertex {
    int parent, depth, start_time, end_time;
    bool visited;
} vertex;

int dfs(int u, int time);

int n, m, cycle_s, cycle_t;
vertex V[MAX];
vector<int> graph[MAX];

int main() {
    int u, v;
    scanf("%d%d", &n, &m);
    for (int i = 0; i < m; i++) {
        scanf("%d%d", &u, &v);
        graph[u].push_back(v);
    }

    bool has_cycle = false;
    for (int i = 1; i <= n; i++) {
        if (V[i].visited) continue;
        dfs(i, 1);
        if (cycle_s) {
            has_cycle = true;
            break;
        }
    }

    if (has_cycle) {
        vector<int> cycle;
        cycle.push_back(cycle_s);
        for (int v = cycle_t; v != cycle_s; v = V[v].parent) cycle.push_back(v);
        cycle.push_back(cycle_s);
        reverse(cycle.begin(), cycle.end());
        printf("%d\n", cycle.size());
        for (int v : cycle) printf("%d ", v);
        printf("\n");
    } else {
        printf("IMPOSSIBLE\n");
    }

    return 0;
}

// Directed Graph.
int dfs(int u, int time) {
    V[u].visited = true;
    V[u].start_time = time;
    for (int v : graph[u]) {
        if (V[v].visited) {
            // Back edge
            //     (1)
            //     /  \
            //   (2)  / <---Back Edge if u = 3 v = 1
            //   /   /
            // (3)---
            if (V[v].start_time < V[u].start_time && V[v].end_time == 0) {
                cycle_s = v;
                cycle_t = u;
            }
            // Cross edge
            //     (1)
            //     /  \
            //   (3)  (2)
            //   /    / <----Cross Edge (u = 4 v = 2)
            // (4)---
            if (V[v].start_time < V[u].start_time && V[v].end_time > 0) {
            }
            // Forward Edge.
            //     (1)
            //     /  \
            //   (2)  / <---Back Edge if u = 1 v = 3
            //   /   /
            // (3)---
            if (V[v].start_time > V[u].start_time) {
            }
        } else {
            // Tree Edge.
            V[v].parent = u;
            V[v].depth = V[u].depth + 1;
            time = dfs(v, time + 1);
        }
    }
    V[u].end_time = ++time;
    return time;
}
