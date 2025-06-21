#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

#define MAX 400005

typedef long long int lli;
typedef pair<lli, lli> pll;

typedef struct vertex {
    int parent, depth;
    bool visited;
} vertex;

bool dfs(int u, int p);

int n, m, cycle_s, cycle_t;
vertex V[MAX];
vector<int> graph[MAX];

int main() {
    int u, v;
    scanf("%d%d", &n, &m);
    for (int i = 0; i < m; i++) {
        scanf("%d%d", &u, &v);
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    bool has_cycle = false;
    for (int i = 1; i <= n; i++) if (!V[i].visited) has_cycle |= dfs(i, 0);

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

bool dfs(int u, int p) {
    bool has_cycle = false;
    V[u].visited = true;
    for (int v : graph[u]) {
        if (v == p) continue;
        if (V[v].visited) {
            if (V[v].depth < V[u].depth) {
                cycle_s = v;
                cycle_t = u;
                has_cycle = true;
            }
        } else {
            V[v].parent = u;
            V[v].depth = V[u].depth + 1;
            has_cycle |= dfs(v, u);
        }
    }
    return has_cycle;
}
